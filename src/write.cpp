#include "hola.hpp"


static inline adios2::Dims get_dims(SEXP x)
{
  SEXP Rdims = getAttrib(x, R_DimSymbol);
  adios2::Dims dims;
  
  if (Rdims == R_NilValue)
  {
    dims.resize(1);
    dims[0] = LENGTH(x);
  }
  else
  {
    int n = LENGTH(Rdims);
    dims.resize(n);
    for (int i=0; i<n; i++)
      dims[i] = INTEGER(Rdims)[i];
  }
  
  return dims;
}



template <typename T>
void write(const std::string &varname, const adios2::Dims &dims, const T *x,
  adios2::IO *io, adios2::Engine *r)
{
  adios2::Variable<T> var = io->InquireVariable<T>(varname);
  if (!var)
    var = io->DefineVariable<T>(varname, dims);
  
  adios2::Dims start(dims.size());
  for (unsigned int i=0; i<dims.size(); i++)
    start[i] = 0;
  
  var.SetShape(dims);
  var.SetSelection({start, dims});
  r->Put(var, x, adios2::Mode::Sync);
}



extern "C" SEXP hola_write(SEXP vn, SEXP io_Robj, SEXP r_Robj, SEXP x)
{
  adios2::IO *io = (adios2::IO *) getRptr(io_Robj);
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  std::string varname = CHARPT(vn, 0);
  
  try {
    auto dims = get_dims(x);
    const std::string varname = CHARPT(vn, 0);
    
    if (TYPEOF(x) == REALSXP)
      write(varname, dims, REAL(x), io, r);
    else if (TYPEOF(x) == INTSXP)
      write(varname, dims, INTEGER(x), io, r);
    else
      error("unspported R type on object 'x' for writing");
    
  } catch(const std::exception& e) { error(e.what()); }
  
  return R_NilValue;
}
