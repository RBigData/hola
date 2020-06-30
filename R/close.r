#' @useDynLib hola hola_close
adios_close = function(af)
{
  .Call(hola_close, af[[2]])
  invisible(TRUE)
}
