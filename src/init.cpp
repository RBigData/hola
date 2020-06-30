#include "hola.hpp"

#include <adios2.h>


extern "C" SEXP hola_init(SEXP config)
{
  SEXP ad_Robj;
  
  adios2::ADIOS *ad;
  
  try {
    if (config == R_NilValue)
      ad = new adios2::ADIOS;
    else
      ad = new adios2::ADIOS(CHARPT(config, 0));
  } catch(const std::exception& e) { error(e.what()); }
  
  newRptr(ad, ad_Robj, adios_object_finalizer<adios2::ADIOS>);
  
  UNPROTECT(1);
  return ad_Robj;
}
