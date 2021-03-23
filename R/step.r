#' @useDynLib hola hola_step
adios_step = function(af)
{
  .Call(hola_step, af[[2]])
}
