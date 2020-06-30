#' @useDynLib hola hola_init
adios_init = function(config)
{
  .Call(hola_init, config)
}
