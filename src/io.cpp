#include "utils.hpp"

#include <adios2.h>

#include <iostream>


extern "C" SEXP hola_open(SEXP f)//, SEXP mode, SEXP comm_ptr)
{
  SEXP ret;
  SEXP ad_Robj, io_Robj, r_Robj;
  // MPI_Comm comm = get_mpi_comm_from_Robj(comm_ptr);
  
  // int rank, size;
  // MPI_Comm_rank(comm, &rank);
  // MPI_Comm_size(comm, &size);
  
  adios2::ADIOS *ad = new adios2::ADIOS;
  adios2::IO *io = new adios2::IO;
  *io = ad->DeclareIO("ReadHDF5");
  io->SetEngine("HDF5");
  
  adios2::Engine *r = new adios2::Engine;
  *r = io->Open(CHARPT(f, 0), adios2::Mode::Read);
  
  newRptr(ad, ad_Robj, adios_object_finalizer<adios2::ADIOS>);
  newRptr(io, io_Robj, adios_object_finalizer<adios2::IO>);
  newRptr(r, r_Robj, adios_object_finalizer<adios2::Engine>);
  
  PROTECT(ret = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(ret, 0, ad_Robj);
  SET_VECTOR_ELT(ret, 1, io_Robj);
  SET_VECTOR_ELT(ret, 2, r_Robj);
  
  UNPROTECT(4);
  return ret;
}



extern "C" SEXP hola_available_variables(SEXP io_Robj)
{
  SEXP ret;
  adios2::IO *io = (adios2::IO *) getRptr(io_Robj);
  
  const auto vars = io->AvailableVariables();
  
  PROTECT(ret = allocVector(STRSXP, vars.size()));
  
  unsigned int i = 0;
  for (const auto var : vars)
  {
    SET_STRING_ELT(ret, i, mkCharLen(var.first.data(), var.first.size()));
    i++;
  }
  
  UNPROTECT(1);
  return ret;
}



extern "C" SEXP hola_close(SEXP r_Robj)
{
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  r->Close();
  
  return R_NilValue;
}



template <typename T>
static inline void check_variable(adios2::Variable<T> &variable,
  const std::string &name, const size_t step)
{
  if (!variable)
    error("variable \"%s\" not found in step %d\n", name.c_str(), step);
}

template <typename T>
static inline long unsigned int get_array_len(std::vector<typename adios2::Variable<T>::Info> &blocks_info)
{
  long unsigned int n = 1;
  const auto dims = blocks_info[0].Count;
  for (unsigned int i=0; i<dims.size(); i++)
    n *= dims[i];
  
  return n;
}

extern "C" SEXP hola_read(SEXP vn, SEXP io_Robj, SEXP r_Robj)
{
  SEXP ret;
  SEXP dim_robj;
  adios2::IO *io = (adios2::IO *) getRptr(io_Robj);
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  std::string varname = CHARPT(vn, 0);
  
  auto read_status = r->BeginStep(adios2::StepMode::Read, 10.0f);
  
  size_t step = r->CurrentStep();
  
  auto type = io->VariableType(varname);
  if (type == "int32_t")
  {
    adios2::Variable<int> variable = io->InquireVariable<int>(varname);
    check_variable(variable, varname, step);
    
    auto blocks_info = r->BlocksInfo(variable, step);
    
    // get array dims
    const auto dims = blocks_info[0].Count;
    
    R_xlen_t n = 1.0;
    for (unsigned int i=0; i<dims.size(); i++)
      n *= (R_xlen_t) dims[i];
    PROTECT(ret = allocVector(INTSXP, n));
    
    PROTECT(dim_robj = allocVector(REALSXP, dims.size()));
    for (unsigned int i=0; i<dims.size(); i++)
      REAL(dim_robj)[i] = (double)dims[dims.size() - 1 - i];
    const char *dim_attr = CHAR(mkChar("dim"));
    setAttrib(ret, install(dim_attr), dim_robj);
    
    // read the data
    for (auto &info : blocks_info)
    {
      variable.SetBlockSelection(info.BlockID);
      r->Get<int>(variable, INTEGER(ret), adios2::Mode::Deferred);
    }
    
    r->PerformGets();
  }
  // else if (type == "double")
  // {
  // ...
  // }
  else
    error("variable has unsupported type");
  
  r->EndStep();
  
  
  UNPROTECT(2);
  return ret;
}
