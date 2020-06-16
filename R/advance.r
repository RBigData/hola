#' advance
#' 
#' Advance the current step.
#' 
#' @param af
#' An ADIOS2 file; the return of the \code{adios_open()} function.
#' @param timeout
#' TODO
#' 
#' @return TODO
#' 
#' @useDynLib hola hola_advance
#' @export
adios_advance = function(af, timeout=10)
{
  check_is_adios_file(af)
  .Call(hola_advance, af[[3]])
}
