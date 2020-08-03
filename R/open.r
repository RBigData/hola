guess_engine = function(filename)
{
  extension = tolower(last_elt(strsplit(basename(filename), split="\\.")[[1]]))
  if (extension == "hdf5" || extension == "h5")
    engine = "hdf5"
  else if (extension == "bp")
    engine = "bpfile"
  else
    stop("unable to determine engine type; please manually specify it")
  
  engine
}



#' @useDynLib hola hola_open
adios_open = function(adios_obj, path, engine, io_name)
{
  .Call(hola_open, adios_obj, path, engine, io_name)
}
