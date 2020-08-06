#include "hola.hpp"


static inline adios2::StepStatus begin_step(adios2::Engine *r,
  float timeout=10.0f)
{
  adios2::StepStatus read_status;
  
  while (true)
  {
    read_status = r->BeginStep(adios2::StepMode::Read, timeout);
    if (read_status == adios2::StepStatus::NotReady)
    {
      Rprintf("Stream not ready yet. Waiting...\n");
      continue;
    }
    else
      break;
  }
  
  return read_status;
}



template <typename T>
adios2::Variable<T> get_var(adios2::IO *io, const std::string &varname,
  const size_t step)
{
  adios2::Variable<T> variable = io->InquireVariable<T>(varname);
  if (!variable)
    error("variable \"%s\" not found in step %d\n", varname.c_str(), step);
  
  return variable;
}

template <typename T>
SEXP get_dims(adios2::Engine *r, const size_t step,
  adios2::Variable<T> &variable)
{
  SEXP dims_robj;
  
  auto blocks_info = r->BlocksInfo(variable, step);
  const auto dims = blocks_info[0].Count;
  
  PROTECT(dims_robj = allocVector(REALSXP, dims.size()));
  for (unsigned int i=0; i<dims.size(); i++)
    REAL(dims_robj)[i] = (double)dims[i];
    // REAL(dims_robj)[i] = (double)dims[dims.size() - 1 - i];
  
  UNPROTECT(1);
  return dims_robj;
}

template <typename T>
void read_var(adios2::Engine *r, adios2::Variable<T> &variable, T *data)
{
  r->Get<T>(variable, data, adios2::Mode::Deferred);
  r->PerformGets();
}



template <typename T>
SEXP read_with_alloc(const std::string &varname, const size_t step,
  adios2::IO *io, adios2::Engine *r, SEXPTYPE R_alloc_type)
{
  SEXP ret;
  SEXP dims;
  
  auto variable = get_var<T>(io, varname, step);
  PROTECT(dims = get_dims(r, step, variable));
  
  R_xlen_t n = 1.0;
  for (int i=0; i<LENGTH(dims); i++)
    n *= (R_xlen_t) REAL(dims)[i];
    
  PROTECT(ret = allocVector(R_alloc_type, n));
  
  const char *dim_attr = CHAR(mkChar("dim"));
  setAttrib(ret, install(dim_attr), dims);
  
  read_var(r, variable, (T*)DATAPTR(ret));
  
  UNPROTECT(2);
  return ret;
}



template <typename T>
static inline void read_no_alloc(const std::string &varname,
  const size_t step, adios2::IO *io, adios2::Engine *r, T *data)
{
  auto variable = get_var<T>(io, varname, step);
  read_var(r, variable, data);
}



extern "C" SEXP hola_read(SEXP vn, SEXP io_Robj, SEXP r_Robj)
{
  SEXP ret;
  
  adios2::IO *io = (adios2::IO *) getRptr(io_Robj);
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  std::string varname = CHARPT(vn, 0);
  
  
  try {
    float timeout = 10.0f;
    adios2::StepStatus read_status;
    while (true)
    {
      read_status = r->BeginStep(adios2::StepMode::Read, timeout);
      if (read_status == adios2::StepStatus::NotReady)
      {
        Rprintf("Stream not ready yet. Waiting...\n");
        continue;
      }
      else
        break;
    }
    
    if (read_status != adios2::StepStatus::OK)
      return R_NilValue;
    
    size_t step = r->CurrentStep();
    
    auto type = io->VariableType(varname);
    if (type == "")
      error("variable \"%s\" not found in step %d\n", varname.c_str(), step);
    else if (type == "int32_t")
      PROTECT(ret = read_with_alloc<int>(varname, step, io, r, INTSXP));
    else if (type == "double")
      PROTECT(ret = read_with_alloc<double>(varname, step, io, r, REALSXP));
    else if (type == "float")
    {
      SEXP ret_data;
      PROTECT(ret_data = read_with_alloc<float>(varname, step, io, r, INTSXP));
      
      SEXP ret_s4_class;
      PROTECT(ret_s4_class = MAKE_CLASS("float32"));
      PROTECT(ret = NEW_OBJECT(ret_s4_class));
      SET_SLOT(ret, install("Data"), ret_data);
      UNPROTECT(2);
    }
    else
      error("variable has unsupported type \"%s\"\n", type.c_str());
    
    r->EndStep();
  } catch(const std::exception& e) { error(e.what()); }
  
  UNPROTECT(1);
  return ret;
}




extern "C" SEXP hola_read_to_buf(SEXP vn, SEXP io_Robj, SEXP r_Robj, SEXP buf)
{
  adios2::IO *io = (adios2::IO *) getRptr(io_Robj);
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  std::string varname = CHARPT(vn, 0);
  
  
  try {
    auto read_status = begin_step(r);
    if (read_status != adios2::StepStatus::OK)
      return R_NilValue;
    
    size_t step = r->CurrentStep();
    
    auto type = io->VariableType(varname);
    if (type == "")
      error("variable \"%s\" not found in step %d\n", varname.c_str(), step);
    else if (type == "int32_t")
      read_no_alloc<int>(varname, step, io, r, INTEGER(buf));
    else if (type == "double")
      read_no_alloc<double>(varname, step, io, r, REAL(buf));
    else if (type == "float")
      read_no_alloc<float>(varname, step, io, r, (float*) DATAPTR(buf));
    else
      error("variable has unsupported type \"%s\"\n", type.c_str());
    
    r->EndStep();
  } catch(const std::exception& e) { error(e.what()); }
  
  return R_NilValue;
}
