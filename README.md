# hola

* **Version:** 0.1-0
* **License:** [BSL-1.0](http://opensource.org/licenses/BSL-1.0)
* **Project home**: https://github.com/RBigData/hola
* **Bug reports**: https://github.com/RBigData/hola/issues


**hola** is the Helpful Operating Link to ADIOS, an interface to the [ADIOS2](https://csmd.ornl.gov/software/adios2) library.



## Installation

The development version is maintained on GitHub:

```r
remotes::install_github("RBigData/hola")
```

You will need a system installation of ADIOS2. Then have your `adios2/install/path/bin` in your `$PATH`, or set `configure.args` e.g.

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
