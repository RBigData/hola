#' @useDynLib hola hola_write
adios_write = function(af, variable, x)
{
  if (!is.vector(x) && !is.matrix(x))
    stop("object 'x' must be a vector or matrix")
  
  .Call(hola_write, variable, af[[1]], af[[2]], x)
}
