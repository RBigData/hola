#' adios_open
#' 
#' Open a file.
#' 
#' @param filename
#' TODO
#' @param engine
#' Either left blank/missing, or one of "bpfile", "dataman", "hdf5",
#' "insitumpi", or "sst", corresponding to the input. If missing, then we try
#' to intuit the engine based on the extension in \code{filename}.
#' 
#' @return An object of class "adios_file".
#' 
#' @useDynLib hola hola_open
#' @export
adios_open = function(filename, engine)
{
  if (missing(engine))
  {
    extension = tolower(last_elt(strsplit(basename(filename), split="\\.")[[1]]))
    if (extension == "hdf5" || extension == "h5")
      engine = "hdf5"
    else if (extension == "bp")
      engine = "bpfile"
    else
      stop("unable to determine engine type; please manually specify it")
  }
  else
    engine = match.arg(engine, c("bpfile", "dataman", "hdf5", "insitumpi", "sst"))
  
  af = .Call(hola_open, filename, engine)
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
