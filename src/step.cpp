#include "hola.hpp"


extern "C" SEXP hola_step(SEXP r_Robj)
{
  SEXP ret;
  PROTECT(ret = allocVector(REALSXP, 1));
  
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  
  try {
    REAL(ret)[0] = (double) r->CurrentStep();
  } catch(const std::exception& e) { error(e.what()); }
  
  UNPROTECT(1);
  return ret;
}
