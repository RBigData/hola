#' @useDynLib hola hola_available_variables
adios_available_variables = function(af)
{
  .Call(hola_available_variables, af[[1]])
}
