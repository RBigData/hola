#include "hola.hpp"
#include "mpi_utils.hpp"

#include <adios2.h>


template <typename T>
static inline void check_variable(adios2::Variable<T> &variable,
  const std::string &name, const size_t step)
{
  if (!variable)
    error("variable \"%s\" not found in step %d\n", name.c_str(), step);
}



template <typename T>
static inline SEXP read_slice(const std::string &varname, const size_t step,
  adios2::IO *io, adios2::Engine *r, SEXPTYPE R_alloc_type)
{
  SEXP ret;
  SEXP dim_robj;
  
  adios2::Variable<T> variable = io->InquireVariable<T>(varname);
  check_variable(variable, varname, step);
  
  auto blocks_info = r->BlocksInfo(variable, step);
  
  // get array dims
  const auto dims = blocks_info[0].Count;
  
  R_xlen_t n = 1.0;
  for (unsigned int i=0; i<dims.size(); i++)
    n *= (R_xlen_t) dims[i];
  PROTECT(ret = allocVector(R_alloc_type, n));
  
  PROTECT(dim_robj = allocVector(REALSXP, dims.size()));
  for (unsigned int i=0; i<dims.size(); i++)
    REAL(dim_robj)[i] = (double)dims[dims.size() - 1 - i];
  const char *dim_attr = CHAR(mkChar("dim"));
  setAttrib(ret, install(dim_attr), dim_robj);
  
  // read the data
  // for (auto &info : blocks_info)
  // {
    auto info = blocks_info[0];
    variable.SetBlockSelection(info.BlockID);
    r->Get<T>(variable, (T*)DATAPTR(ret), adios2::Mode::Deferred);
  // }
  
  r->PerformGets();
  
  UNPROTECT(2);
  return ret;
}



extern "C" SEXP hola_read(SEXP vn, SEXP io_Robj, SEXP r_Robj)
{
  SEXP ret;
  
  adios2::IO *io = (adios2::IO *) getRptr(io_Robj);
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  std::string varname = CHARPT(vn, 0);
  
  auto read_status = r->BeginStep(adios2::StepMode::Read, 10.0f);
  
  size_t step = r->CurrentStep();
  
  auto type = io->VariableType(varname);
  if (type == "int32_t")
    PROTECT(ret = read_slice<int>(varname, step, io, r, INTSXP));
  else if (type == "double")
    PROTECT(ret = read_slice<double>(varname, step, io, r, REALSXP));
  else if (type == "float")
    PROTECT(ret = read_slice<float>(varname, step, io, r, INTSXP));
  else
    error("variable has unsupported type");
  
  r->EndStep();
  
  
  UNPROTECT(1);
  return ret;
}
