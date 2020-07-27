#ifndef HOLA_H
#define HOLA_H
#pragma once


#include <adios2.h>

#include <Rinternals.h>
#include <Rdefines.h>


#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))
#define INT(x) INTEGER(x)[0]

#define newRptr(ptr,Rptr,fin) PROTECT(Rptr = R_MakeExternalPtr(ptr, R_NilValue, R_NilValue));R_RegisterCFinalizerEx(Rptr, fin, TRUE)
#define getRptr(ptr) R_ExternalPtrAddr(ptr)

template <typename T>
static inline void adios_object_finalizer(SEXP Rptr)
{
  if (NULL == getRptr(Rptr))
    return;
  
  T *x = (T*) getRptr(Rptr);
  delete x;
  R_ClearExternalPtr(Rptr);
}


#endif
