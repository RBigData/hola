#' @useDynLib hola hola_init
adios_init = function(config, comm)
{
  if (has_mpi())
  {
    if (is.null(comm))
      comm = 0L
    
    comm_ptr = pbdMPI::get.mpi.comm.ptr(comm)
  }
  else
    comm_ptr = NULL
  
  .Call(hola_init, config, comm_ptr)
}
