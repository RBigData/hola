#include "hola.hpp"
#include "mpi_utils.hpp"

#include <adios2.h>


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
