FROM ubuntu:20.04

ENV MAKE="make -j 4"
ENV TZ=America/Bahia
ENV DEBIAN_FRONTEND=noninteractive


RUN apt-get update && apt-get install -y --no-install-recommends \
  wget cmake python \
  libopenmpi-dev openmpi-bin libhdf5-dev libopenblas-dev \
  r-base-dev


ENV ADIOS_VERSION="2.7.1.436"
RUN wget https://github.com/ornladios/ADIOS2/archive/refs/tags/v${ADIOS_VERSION}.tar.gz
RUN tar -zxf v${ADIOS_VERSION}.tar.gz
RUN cd ADIOS2-${ADIOS_VERSION} && \
  mkdir -p install && \
  mkdir -p build && \
  cd build && \
  cmake \
  -DCMAKE_INSTALL_PREFIX=${ADIOS2_SRC}/install \
  -DCMAKE_CXX_COMPILER=g++ \
  -DCMAKE_C_COMPILER=gcc \
  -DCMAKE_Fortran_COMPILER=gfortran \
  -DBUILD_SHARED_LIBS=ON \
  -DADIOS2_USE_MPI=ON \
  -DADIOS2_USE_Fortran=OFF \
  -DADIOS2_USE_Python=OFF \
  -DADIOS2_USE_SST=ON \
  -DADIOS2_BUILD_EXAMPLES_EXPERIMENTAL=OFF \
  -DCMAKE_BUILD_TYPE=Release \
  -DADIOS2_BUILD_TESTING=OFF \
  -DADIOS2_USE_DataMan=OFF \
  -DADIOS2_USE_HDF5=ON \
  .. && \
    make && \
    make install



RUN Rscript -e "install.packages('remotes')"
RUN Rscript -e "install.packages('float')"
RUN Rscript -e "install.packages('R6')"
RUN Rscript -e "remotes::install_github('RBigData/hola', configure.args='--with-adios2-home=/install/')"

CMD ["/bin/bash"]
