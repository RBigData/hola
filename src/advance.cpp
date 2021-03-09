#include "hola.hpp"
#include "step.hpp"


extern "C" SEXP hola_begin_step(SEXP r_Robj, SEXP timeout_)
{
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  begin_step(r, (float) REAL(timeout_)[0]);
  
  return R_NilValue;
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
  
  try {
    if (status != adios2::StepStatus::OK)
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
