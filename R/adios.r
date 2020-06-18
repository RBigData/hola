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
adios_file_R6 = R6::R6Class("adios_file_R6",
  public = list(
    #' @details Open the file.
    #' @param path File path.
    initialize = function(path)
    {
      private$file = adios_open(path)
      private$var = adios_available_variables(private$file)
    },
    
    #' @details Close the file.
    close = function()
    {
      adios_close(private$file)
      private$file = NULL
      private$var = NULL
    },
    
    #' @details Print some basic file information.
    print = function()
    {
      print(private$file)
    },
    
    #' @details Advance the step.
    #' @param timeout Timeout in seconds between trying to advance the step in
    #' the case data is being streamed.
    advance = function(timeout=10)
    {
      adios_advance(af, timeout=10)
    },
    
    #' @details Reads the array of a variable into R memory.
    #' @param var String name of the desired variable.
    read = function(var)
    {
      adios_read(private$file, var)
    }
  ),
  
  private = list(
    finalize = function()
    {
      if (!is.null(private$file))
        self$close()
    },
    
    file = NULL,
    var = NULL
  )
)



adios_R6 = R6::R6Class("adios_R6",
  public = list(
    file = function(path)
    {
      adios_file_R6$new(path=path)
    }
  )
)



#' @rdname adios
#' @export
adios = adios_R6$new()
