#' adios_read
#' 
#' Read a file opened by \code{adios_open()}.
#' 
#' @param af
#' An ADIOS2 file; the return of the \code{adios_open()} function.
#' @param variable
#' The variable to read.
#' 
#' @return Returns the data: a numeric vector, matrix, or multi-way array.
#' 
#' @useDynLib hola hola_read
#' @export
adios_read = function(af, variable)
{
  check_is_adios_file(af)
  .Call(hola_read, variable, af[[2]], af[[3]])
}
