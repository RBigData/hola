check_is_adios_file = function(af)
{
  if (!inherits(af, "adios_file"))
    stop("object is not a valid adios file")
  
  invisible(TRUE)
}
