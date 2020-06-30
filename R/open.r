#' @useDynLib hola hola_open
adios_open = function(adios_obj, filename, engine, io_name)
{
  if (is.null(engine))
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
  
  .Call(hola_open, adios_obj, filename, engine, io_name)
}
