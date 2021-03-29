suppressMessages(library(hola))

f = tempdir()
var = "/x"

# --------------------------------------------------------------
w = adios(f, mode="write")

x1w = matrix(1:8, 4)
w$write(var, x1w)
w$advance()

x2w = matrix(1L, 1, 1)
w$write(var, x2w)
w$advance()

x3w = matrix(1:15, 3)
w$write(var, x3w)
w$advance()

w$close()

# --------------------------------------------------------------
r = adios(f, mode="read")

x1r = r$read(var)
r$advance()

x2r = r$read(var)
r$advance()

x3r = r$read(var)
r$close()

# --------------------------------------------------------------
stopifnot(all.equal(x1w, x1r))
stopifnot(all.equal(x2w, x2r))
stopifnot(all.equal(x3w, x3r))
