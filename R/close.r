#' @useDynLib hola hola_close
#' @export
adios_close = function(af)
{
  check_is_adios_file(af)
  .Call(hola_close, af[[3]])
  invisible(TRUE)
}
