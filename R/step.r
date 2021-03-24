#' @useDynLib hola hola_begin_step
adios_begin_step = function(af, timeout=10)
{
  .Call(hola_begin_step, af[[2]], as.double(timeout))
}



#' @useDynLib hola hola_advance
adios_advance = function(af, step_begun, timeout=10)
{
  .Call(hola_advance, af[[2]], step_begun, as.double(timeout))
}



#' @useDynLib hola hola_step
adios_step = function(af)
{
  .Call(hola_step, af[[2]])
}
