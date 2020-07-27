#include "hola.hpp"

#ifdef MPI_VERSION
#include "mpi_utils.hpp"
#endif


extern "C" SEXP hola_init(SEXP config, SEXP comm_ptr)
{
  SEXP ad_Robj;
  
  adios2::ADIOS *ad;
  
#ifdef MPI_VERSION
  MPI_Comm comm = get_mpi_comm_from_Robj(comm_ptr);
  try {
    if (config == R_NilValue)
      ad = new adios2::ADIOS(comm);
    else
      ad = new adios2::ADIOS(CHARPT(config, 0), comm);
  } catch(const std::exception& e) { error(e.what()); }
#else
  (void)comm_ptr;
  try {
    if (config == R_NilValue)
      ad = new adios2::ADIOS;
    else
      ad = new adios2::ADIOS(CHARPT(config, 0));
  } catch(const std::exception& e) { error(e.what()); }
#endif
  
  newRptr(ad, ad_Robj, adios_object_finalizer<adios2::ADIOS>);
  
  UNPROTECT(1);
  return ad_Robj;
}
