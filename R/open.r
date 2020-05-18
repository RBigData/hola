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
