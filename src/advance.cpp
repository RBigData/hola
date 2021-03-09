#include "hola.hpp"
#include "step.hpp"


extern "C" SEXP hola_advance(SEXP r_Robj, SEXP timeout_)
{
  SEXP ret;
  PROTECT(ret = allocVector(LGLSXP, 1));
  
  adios2::Engine *r = (adios2::Engine *) getRptr(r_Robj);
  
  auto read_status = begin_step(r, (float) REAL(timeout_)[0]);
  
  try {
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
