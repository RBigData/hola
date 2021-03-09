#' adios_file_R6
#' 
#' R6 classes and methods for ADIOS2 file operations.
#' 
#' @examples
#' \dontrun{
#' suppressMessages(library(hola))
#' 
#' ad = adios("/path/to/my/dataset")
#' myvar_step_0 = ad$read("my_variable")
#' ad$advance()
#' myvar_step_2 = ad$read("my_variable")
#' }
#' 
#' @rdname adios
#' @name adios
NULL



#' @rdname adios
adios_R6 = R6::R6Class("adios_R6",
  public = list(
    #' @details Open the file.
    #' @param path File path.
    #' @param config An ADIOS2 config file.
    #' @param io_name The IO configuration ("io name" key) to use.
    #' @param comm A communicator number from pbdMPI if the package is installed
    #' with MPI support; will use \code{MPI_COMM_WORLD} by default. Otherwise
    #' the param is ignored.
    #' @param mode \code{"read"} or \code{"write"}.
    initialize = function(path, config, io_name, comm=NULL, mode="read")
    {
      mode = match.arg(tolower(mode), c("read", "write"))
      
      if ((missing(config) && !missing(io_name)) || !missing(config) && missing(io_name))
        stop("must supply both 'config' and 'io_name' if using either")
      
      if (missing(config))
      {
        config = NULL
        if (mode == "read")
          io_name = "R_ADIOS_READER"
        else
          io_name = "R_ADIOS_WRITER"
      }
      
      
      engine = NULL
      private$init(config=config, comm=comm)
      private$open(path=path, engine=engine, io_name=io_name, mode=mode)
      
      invisible(self)
    },
    
    
    
    #' @details List available variables in a file.
    available_variables = function()
    {
      private$var
    },
    
    
    
    #' @details Close the file.
    close = function()
    {
      if (!is.null(private$file))
        adios_close(private$file)
      
      private$file = NULL
      private$var = NULL
      
      invisible(self)
    },
    
    
    
    #' @details Returns basic file info.
    fileinfo = function()
    {
      l = list(
        config = private$config,
        path = private$path,
        mode = private$mode
      )
      
      l
    },
    
    
    
    #' @details Print some basic file information.
    print = function()
    {
      if (is.null(private$file))
        cat("## ADIOS2 file: NULL\n")
      else
      {
        cat("## An ADIOS2 file: ")
        cat(private$path)
        cat("\n")
      }
      
      invisible(self)
    },
    
    
    
    #' @details Advance the step.
    #' @param timeout Timeout in seconds between trying to advance the step in
    #' the case data is being streamed.
    advance = function(timeout=10)
    {
      adios_advance(private$file, timeout=timeout)
      
      invisible(self)
    },
    
    
    
    #' @details Reads the array of a variable into R memory.
    #' @param var String name of the desired variable.
    read = function(var)
    {
      if (private$mode != "read")
        stop("file not opened for reading")
      
      adios_read(private$file, var)
    },
    
    
    
    #' @details Reads the array of a variable into pre-allocated R memory. If
    #' the buffer is inappropriately sized, terrible things may happen.
    #' @param var String name of the desired variable.
    #' @param buf Buffer space.
    read_to_buf = function(var, buf)
    {
      adios_read_to_buf(private$file, var, buf)
      invisible(self)
    },
    
    
    
    #' @details Write the R vector/matrix to a file.
    #' @param var String name of the desired variable.
    #' @param x R vector/matrix object.
    write = function(var, x)
    {
      if (private$mode != "write")
        stop("file not opened for writing")
      
      adios_write(private$file, var, x)
      invisible(self)
    }
  ),
  
  
  
  # ---------------------------------------------------------------------------
  private = list(
    finalize = function()
    {
      self$close()
    },
    
    init = function(config, comm)
    {
      private$comm = comm
      private$config = config
      private$adios_obj = adios_init(config, comm)
    },
    
    open = function(path, engine, io_name, mode)
    {
      private$mode = mode
      
      private$path = path
      private$file = adios_open(private$adios_obj, path, engine, io_name, mode)
      private$var = adios_available_variables(private$file)
    },
    
    comm = NULL,
    config = NULL,
    path = NULL,
    mode = NULL,
    adios_obj = NULL,
    file = NULL,
    var = NULL
  )
)



#' @param path File path.
#' @param config An ADIOS2 config file.
#' @param io_name The IO configuration ("io name" key) to use.
#' @param comm A communicator number from pbdMPI if the package is installed
#' with MPI support; will use \code{MPI_COMM_WORLD} by default. Otherwise
#' the param is ignored.
#' @param mode \code{"read"} or \code{"write"}.
#' @rdname adios
#' @export
adios = function(path, config, io_name, comm=NULL, mode="read")
{
  adios_R6$new(path, config, io_name, comm, mode)
}
