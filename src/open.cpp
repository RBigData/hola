#include "hola.hpp"


extern "C" SEXP hola_open(SEXP ad_Robj, SEXP path, SEXP engine, SEXP io_name,
  SEXP mode)
{
  SEXP ret;
  SEXP io_Robj, r_Robj;
  
  try {
    adios2::ADIOS *ad = (adios2::ADIOS *) getRptr(ad_Robj);
    
    adios2::IO *io = new adios2::IO;
    *io = ad->DeclareIO(CHARPT(io_name, 0));
    
    if (engine != R_NilValue)
      io->SetEngine(CHARPT(engine, 0));
    
    adios2::Engine *r = new adios2::Engine;
    if (CHARPT(mode, 0)[0] == 'r')
      *r = io->Open(CHARPT(path, 0), adios2::Mode::Read);
    else
      *r = io->Open(CHARPT(path, 0), adios2::Mode::Write);
    
    newRptr(io, io_Robj, adios_object_finalizer<adios2::IO>);
    newRptr(r, r_Robj, adios_object_finalizer<adios2::Engine>);
    
    PROTECT(ret = allocVector(VECSXP, 2));
    SET_VECTOR_ELT(ret, 0, io_Robj);
    SET_VECTOR_ELT(ret, 1, r_Robj);
  } catch(const std::exception& e) { error(e.what()); }
  
  UNPROTECT(3);
  return ret;
}
