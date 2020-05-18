#' @useDynLib hola hola_read
#' @export
adios_read = function(af, variable)
{
  check_is_adios_file(af)
  .Call(hola_read, variable, af[[2]], af[[3]])
}
