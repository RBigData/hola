# hola

* **Version:** 0.1-0
* **License:** [BSL-1.0](http://opensource.org/licenses/BSL-1.0)
* **Project home**: https://github.com/RBigData/hola
* **Bug reports**: https://github.com/RBigData/hola/issues


**hola** is the Helpful Operating Link to ADIOS, an interface to the [ADIOS2](https://csmd.ornl.gov/software/adios2) library. ADIOS2 is an I/O middleware used in some of the largest supercomputing simulations in the world. It supports several formats, including HDF5 and its native BP, as well as streaming data.

Currently we have implemented a single process (no MPI) reader and writer.



## Installation

The development version is maintained on GitHub:

```r
remotes::install_github("RBigData/hola")
```

You will need a system installation of [ADIOS2](https://csmd.ornl.gov/software/adios2); there is an example build script in [`hola/tools/build_adios.sh`](https://github.com/RBigData/hola/blob/master/tools/build_adios.sh). At build time, hola needs to be able to find the file `adios2/install/path/bin/adios2-config`. So to build hola, you either need to add `adios2/install/path/bin` to your `$PATH`, or set `configure.args` e.g.

```r
remotes::install_github("RBigData/hola", configure.args="--with-adios2-home=adios2/install/path/")
```



## Example

```r
suppressMessages(library(hola))

ad = adios()

dataset = system.file("datasets/example_int.h5", package="hola")
ad$open(dataset)

ad$available_variables()
## [1] "/data"

ad$close()
```
