#' @useDynLib hola hola_read
adios_read = function(af, variable)
{
  .Call(hola_read, variable, af[[1]], af[[2]])
}



#' @useDynLib hola hola_read_to_buf
adios_read_to_buf = function(af, variable, buf)
{
  .Call(hola_read_to_buf, variable, af[[1]], af[[2]], buf)
}
