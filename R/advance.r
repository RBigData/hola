#' @useDynLib hola hola_advance
adios_advance = function(af, timeout=10)
{
  .Call(hola_advance, af[[2]], as.double(timeout))
}
