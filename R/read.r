#' @useDynLib hola hola_read
adios_read = function(af, variable)
{
  .Call(hola_read, variable, af[[1]], af[[2]])
}
