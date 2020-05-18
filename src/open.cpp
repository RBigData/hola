#include "hola.hpp"
#include "mpi_utils.hpp"

#include <adios2.h>


extern "C" SEXP hola_open(SEXP f, SEXP engine_type)//, SEXP mode, SEXP comm_ptr)
{
  SEXP ret;
  SEXP ad_Robj, io_Robj, r_Robj;
  // MPI_Comm comm = get_mpi_comm_from_Robj(comm_ptr);
  
  // int rank, size;
  // MPI_Comm_rank(comm, &rank);
  // MPI_Comm_size(comm, &size);
  
  adios2::ADIOS *ad = new adios2::ADIOS;
  adios2::IO *io = new adios2::IO;
  *io = ad->DeclareIO("R_ADIOS_READER");
  io->SetEngine(CHARPT(engine_type, 0));
  
  adios2::Engine *r = new adios2::Engine;
  *r = io->Open(CHARPT(f, 0), adios2::Mode::Read);
  
  newRptr(ad, ad_Robj, adios_object_finalizer<adios2::ADIOS>);
  newRptr(io, io_Robj, adios_object_finalizer<adios2::IO>);
  newRptr(r, r_Robj, adios_object_finalizer<adios2::Engine>);
  
  PROTECT(ret = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(ret, 0, ad_Robj);
  SET_VECTOR_ELT(ret, 1, io_Robj);
  SET_VECTOR_ELT(ret, 2, r_Robj);
  
  UNPROTECT(4);
  return ret;
}
