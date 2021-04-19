#include "hola.hpp"


static inline adios2::StepStatus begin_step(adios2::Engine *r, float timeout=10.0f)
{
  adios2::StepStatus status;
  
  try {
    while (true)
    {
      status = r->BeginStep(adios2::StepMode::Read, timeout);
      if (status == adios2::StepStatus::NotReady)
      {
        // Rprintf("Stream not ready yet. Waiting...\n");
        continue;
      }
      else
        break;
    }
  } catch(const std::exception& e) { error(e.what()); }
  
  return status;
}



extern "C" SEXP hola_begin_step(SEXP r_Robj, SEXP timeout_)
{
  SEXP ret;
  PROTECT(ret = allocVector(LGLSXP, 1));
  
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  
  adios2::StepStatus status = begin_step(r, (float) REAL(timeout_)[0]);
  LOGICAL(ret)[0] = (status == adios2::StepStatus::OK);
  
  UNPROTECT(1);
  return ret;
}



extern "C" SEXP hola_advance(SEXP r_Robj, SEXP step_begun, SEXP timeout_)
{
  SEXP ret;
  PROTECT(ret = allocVector(LGLSXP, 1));
  
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  
  adios2::StepStatus status;
  if (!LOGICAL(step_begun)[0])
    status = begin_step(r, (float) REAL(timeout_)[0]);
  else
    status = adios2::StepStatus::OK;
  
  
  if (status != adios2::StepStatus::OK)
    LOGICAL(ret)[0] = 0;
  else
  {
    LOGICAL(ret)[0] = 1;
    r->EndStep();
  }
  
  UNPROTECT(1);
  return ret;
}



extern "C" SEXP hola_step(SEXP r_Robj)
{
  SEXP ret;
  PROTECT(ret = allocVector(REALSXP, 1));
  
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  
  try {
    REAL(ret)[0] = (double) r->CurrentStep();
  } catch(const std::exception& e) { error(e.what()); }
  
  UNPROTECT(1);
  return ret;
}
