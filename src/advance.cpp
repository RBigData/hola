#include "hola.hpp"


extern "C" SEXP hola_advance(SEXP r_Robj, SEXP timeout_)
{
  SEXP ret;
  PROTECT(ret = allocVector(LGLSXP, 1));
  
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  float timeout = (float) REAL(timeout_)[0];
  
  try {
    adios2::StepStatus read_status;
    while (true)
    {
      read_status = r->BeginStep(adios2::StepMode::Read, timeout);
      if (read_status == adios2::StepStatus::NotReady)
        continue;
      else
        break;
    }
    
    if (read_status != adios2::StepStatus::OK)
      LOGICAL(ret)[0] = 0;
    else
    {
      LOGICAL(ret)[0] = 1;
      r->CurrentStep();
      r->EndStep();
    }
  } catch(const std::exception& e) { error(e.what()); }
  
  UNPROTECT(1);
  return ret;
}
