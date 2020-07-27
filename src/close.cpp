#include "hola.hpp"


extern "C" SEXP hola_close(SEXP r_Robj)
{
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  
  try {
    r->Close();
  } catch(const std::exception& e) { error(e.what()); }
  
  return R_NilValue;
}
