#' @useDynLib hola hola_open
#' @export
adios_open = function(filename, engine_type)
{
  if (missing(engine_type))
  {
    extension = tolower(tail(strsplit(basename(filename), split="\\.")[[1]], 1))
    if (extension == "hdf5" || extension == "h5")
      engine_type = "hdf5"
    else if (extension == "bp")
      engine_type = "bpfile"
  }
  else
    engine_type = match.arg(engine_type, c("bpfile", "dataman", "hdf5", "insitumpi", "sst"))
  
  af = .Call(hola_open, filename, engine_type)
  class(af) = "adios_file"
  attr(af, "filename") = filename
  af
}

#' @export
print.adios_file = function(x, ...)
{
  cat("## An ADIOS2 file: ")
  cat(attr(x, "filename"))
  cat("\n")
  invisible()
}



#' @useDynLib hola hola_available_variables
#' @export
adios_available_variables = function(af)
{
  check_is_adios_file(af)
  .Call(hola_available_variables, af[[2]])
}



#' @useDynLib hola hola_close
#' @export
adios_close = function(af)
{
  check_is_adios_file(af)
  .Call(hola_close, af[[3]])
  invisible(TRUE)
}



#' @useDynLib hola hola_read
#' @export
adios_read = function(af, variable)
{
  check_is_adios_file(af)
  .Call(hola_read, variable, af[[2]], af[[3]])
}
