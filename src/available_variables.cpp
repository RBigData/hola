#include "hola.hpp"


extern "C" SEXP hola_available_variables(SEXP io_Robj)
{
  SEXP ret;
  adios2::IO *io = (adios2::IO *) getRptr(io_Robj);
  
  try {
    const auto vars = io->AvailableVariables();
    
    PROTECT(ret = allocVector(STRSXP, vars.size()));
    
    unsigned int i = 0;
    for (const auto var : vars)
    {
      SET_STRING_ELT(ret, i, mkCharLen(var.first.data(), var.first.size()));
      i++;
    }
  } catch(const std::exception& e) { error(e.what()); }
  
  UNPROTECT(1);
  return ret;
}
