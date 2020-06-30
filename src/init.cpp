#include "hola.hpp"

#include <adios2.h>


extern "C" SEXP hola_init(SEXP config)
{
  SEXP ad_Robj;
  
  adios2::ADIOS *ad;
  
  if (config == R_NilValue)
    ad = new adios2::ADIOS;
  else
    ad = new adios2::ADIOS(CHARPT(config, 0));
  
  newRptr(ad, ad_Robj, adios_object_finalizer<adios2::ADIOS>);
  
  UNPROTECT(1);
  return ad_Robj;
}
