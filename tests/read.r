suppressMessages(library(hola))

truth = matrix(1:30, 3)

dataset = system.file("datasets/example_int.h5", package="hola")
af = adios_open(dataset)
test = adios_read(af, "/data")
adios_close(af)

stopifnot(all.equal(test, truth))
