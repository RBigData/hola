#include "hola.hpp"

#ifdef MPI_VERSION
#include "mpi_utils.hpp"
#endif


extern "C" SEXP hola_init(SEXP config, SEXP comm_ptr)
{
  SEXP ad_Robj;
  
  std::string config_string;
  if (config == R_NilValue)
    config_string = "";
  else
    config_string = CHARPT(config, 0);
  
  adios2::ADIOS *ad;
  try {
#ifdef MPI_VERSION
    MPI_Comm comm = get_mpi_comm_from_Robj(comm_ptr);
    ad = new adios2::ADIOS(config_string, comm, "R", false);
#else
    (void)comm_ptr;
    ad = new adios2::ADIOS(config_string, "R", false);
#endif
  } catch(const std::exception& e) { error(e.what()); }
  
  newRptr(ad, ad_Robj, adios_object_finalizer<adios2::ADIOS>);
  
  UNPROTECT(1);
  return ad_Robj;
}
