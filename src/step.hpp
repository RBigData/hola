#ifndef HOLA_STEP_H
#define HOLA_STEP_H
#pragma once


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
        Rprintf("Stream not ready yet. Waiting...\n");
        continue;
      }
      else
        break;
    }
  } catch(const std::exception& e) { error(e.what()); }
  
  return status;
}


#endif
