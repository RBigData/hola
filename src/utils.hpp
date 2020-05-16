#ifndef UTILS_H
#define UTILS_H
#pragma once


#include <Rinternals.h>
#include <Rdefines.h>

#define OMPI_SKIP_MPICXX 1
#include <mpi.h>


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



static inline MPI_Comm get_mpi_comm_from_Robj(SEXP comm_ptr)
{
  MPI_Comm *comm = (MPI_Comm*) R_ExternalPtrAddr(comm_ptr);
  return *comm;
}

static inline void check_MPI_ret(int ret)
{
  if (ret != MPI_SUCCESS)
  {
    int slen;
    char s[MPI_MAX_ERROR_STRING];
    
    MPI_Error_string(ret, s, &slen);
    error(s);
  }
}


#endif
