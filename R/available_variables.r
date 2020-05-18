#' @useDynLib hola hola_available_variables
#' @export
adios_available_variables = function(af)
{
  check_is_adios_file(af)
  .Call(hola_available_variables, af[[2]])
}
