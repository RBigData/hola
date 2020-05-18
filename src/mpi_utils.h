#ifndef MPI_UTILS_H
#define MPI_UTILS_H
#pragma once


#include <Rinternals.h>
#include <Rdefines.h>

#define OMPI_SKIP_MPICXX 1
#include <mpi.h>


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
