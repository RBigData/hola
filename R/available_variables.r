#' available_variables
#' 
#' Show available variables in ADIOS2-managed file.
#' 
#' @param af
#' An ADIOS2 file; the return of the \code{adios_open()} function.
#' 
#' @return TODO
#' 
#' @useDynLib hola hola_available_variables
#' @export
adios_available_variables = function(af)
{
  check_is_adios_file(af)
  .Call(hola_available_variables, af[[2]])
}
