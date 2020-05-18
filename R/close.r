#' adios_close
#' 
#' Close an open ADIOS2 file.
#' 
#' @param af
#' An ADIOS2 file; the return of the \code{adios_open()} function.
#' 
#' @return Invisibly returns \code{TRUE}.
#' 
#' @useDynLib hola hola_close
#' @export
adios_close = function(af)
{
  check_is_adios_file(af)
  .Call(hola_close, af[[3]])
  invisible(TRUE)
}
