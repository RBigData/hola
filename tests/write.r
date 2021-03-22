suppressMessages(library(hola))

f = tempdir()
var = "/mydata"

# --------------------------------------------------------------
w = adios(f, mode="write")

x1w = matrix(1:8, 4)
w$write(var, x1w)
w$advance()

x2w = matrix(8:1, 4)
w$write(var, x2w)
w$advance()

w$close()

# --------------------------------------------------------------
r = adios(f, mode="read")
x1r = r$read(var)

r$advance()
x2r = r$read(var)

r$close()

unlink(f, recursive=TRUE)

# --------------------------------------------------------------
stopifnot(all.equal(x1w, x1r))
stopifnot(all.equal(x2w, x2r))
