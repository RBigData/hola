#' adios_file_R6
#' 
#' R6 classes and methods for ADIOS2 file operations.
#' 
#' @examples
#' \dontrun{
#' suppressMessages(library(hola))
#' 
#' f = adios$file("/path/to/my/dataset")
#' myvar_step_0 = f$read("my_variable")
#' f$advance()
#' myvar_step_2 = f$read("my_variable")
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
      return(self)
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
      return(self)
    },
    
    #' @details Close the file.
    close = function()
    {
      adios_close(private$file)
      private$file = NULL
      private$var = NULL
      return(self)
    },
    
    #' @details Print some basic file information.
    print = function()
    {
      # cat("## An ADIOS2 file: ")
      # cat(attr(private$path, "filename"))
      # cat("\n")
      return(self)
    },
    
    #' @details Advance the step.
    #' @param timeout Timeout in seconds between trying to advance the step in
    #' the case data is being streamed.
    advance = function(timeout=10)
    {
      adios_advance(private$file, timeout=timeout)
      return(self)
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
      if (!is.null(private$file))
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
