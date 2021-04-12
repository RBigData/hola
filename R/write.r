#' @useDynLib hola hola_write
adios_write = function(af, variable, x)
{
  if (!is.atomic(x) && !is.vector(x) && !is.matrix(x) && !is.array(x))
    stop("object 'x' must be a vector, matrix, or n-dimensional array")
  
  .Call(hola_write, variable, af[[1]], af[[2]], x)
}
