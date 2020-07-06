#' adios_file_R6
#' 
#' R6 classes and methods for ADIOS2 file operations.
#' 
#' @examples
#' \dontrun{
#' suppressMessages(library(hola))
#' 
#' ad = adios()
#' ad$open("/path/to/my/dataset")
#' myvar_step_0 = ad$read("my_variable")
#' f$advance()
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
    #' @param config An optional ADIOS2 config file.
    initialize = function(config=NULL)
    {
      private$config = config
      private$adios_obj = adios_init(config)
      
      invisible(self)
    },
    
    #' @details Open the file.
    #' @param path File path.
    #' @param engine Either left blank/missing, or one of "bpfile", "dataman",
    #' "hdf5", "insitumpi", or "sst", corresponding to the input. If missing,
    #' then we try to intuit the engine based on the extension in
    #' \code{path}.
    #' @param io_name The IO configuration ("io name" key) to use if using a
    #' config file.
    open = function(path, engine=NULL, io_name=NULL)
    {
      if (is.null(io_name))
      {
        if (!is.null(private$config))
          stop("must provide an 'io_name' argument when using config file")
        
        io_name = "R_ADIOS_READER"
      }
      # TODO
      # else
      #   check_is_string(io_name)
      
      
      if (!is.null(private$file))
        self$close()
      
      private$path = path
      private$file = adios_open(private$adios_obj, path, engine, io_name)
      private$var = adios_available_variables(private$file)
      
      invisible(self)
    },
    
    #' @details List available variables in a file.
    available_variables = function()
    {
      if (is.null(private$var))
        stop("must open a file first")
      
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
      adios_read(private$file, var)
    }
  ),
  
  # ---------------------------------------------------------------------------
  private = list(
    finalize = function()
    {
      self$close()
    },
    
    config = NULL,
    path = NULL,
    adios_obj = NULL,
    file = NULL,
    var = NULL
  )
)



#' @param config An optional ADIOS2 config file.
#' @rdname adios
#' @export
adios = function(config=NULL)
{
  adios_R6$new(config)
}
