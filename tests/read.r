suppressMessages(library(hola))

truth = matrix(1:30, 10)

dataset = system.file("datasets/example_int.h5", package="hola")
ad = adios(dataset)
test = ad$read("/data")
ad$close()

stopifnot(all.equal(test, truth))
