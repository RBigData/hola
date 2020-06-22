AC_PREREQ([2.69])
AC_INIT()
AC_CONFIG_SRCDIR()

# Determine R_HOME.
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi

R_SCMD="${R_HOME}/bin/Rscript -e"

# SPMD_CPPFLAGS=`${R_SCMD} "source('./R/conf/get_conf.r');get.conf('PKG_CPPFLAGS','"${R_ARCH}"')"`
# SPMD_LDFLAGS=`${R_SCMD} "source('./R/conf/get_conf.r');get.conf('PKG_LIBS','"${R_ARCH}"')"`

AC_ARG_WITH([adios2-home],
  AC_HELP_STRING(
    [--with-adios2-home=ADIOS_PATH],
    [location of ADIOS2 installation]
  ),
  [ADIOS_PATH=$withval]
)

AC_CHECK_PROG([ADIOS2_CONFIG], [adios2-config], yes, [no])
if test x"${ADIOS2_CONFIG}" == x"yes"; then
  ADIOS_CPPFLAGS=`adios2-config --cxx-flags -s`
  ADIOS_LDFLAGS=`adios2-config --cxx-libs -s`
  ADIOS_VERSION=`adios2-config -v | head -n 1 | sed -e 's/ADIOS //'`
else
  if test -z "${ADIOS_PATH}"; then
    AC_MSG_ERROR([ERROR: could not determine ADIOS_PATH; please set --with-adios2-home])
  fi
  
  AC_CHECK_PROG([CUSTOM_ADIOS2_CONFIG], [adios2-config], yes, [no], [${ADIOS_PATH}/bin])
  
  if test x"${CUSTOM_ADIOS2_CONFIG}" == x"yes"; then
    ADIOS_CPPFLAGS=`${ADIOS_PATH}/bin/adios2-config --cxx-flags -s`
    ADIOS_LDFLAGS=`${ADIOS_PATH}/bin/adios2-config --cxx-libs -s`
    ADIOS_VERSION=`${ADIOS_PATH}/bin/adios2-config -v | head -n 1 | sed -e 's/ADIOS //'`
  else
    AC_MSG_ERROR([could not find adios2-config either in \$PATH or the specified adios2-home])
  fi
fi



echo " "
echo "******************** Results of hola package configure *******************"
echo " "
# echo "* MPI report:"
# echo "    >> SPMD_CPPFLAGS = ${SPMD_CPPFLAGS}"
# echo "    >> SPMD_LDFLAGS = ${SPMD_LDFLAGS}"
echo "* ADIOS2 report:"
echo "    >> ADIOS_VERSION = ${ADIOS_VERSION}"
echo "    >> ADIOS_CPPFLAGS = ${ADIOS_CPPFLAGS}"
echo "    >> ADIOS_LDFLAGS = ${ADIOS_LDFLAGS}"
echo " "
echo "**************************************************************************"
echo " "


AC_SUBST(SPMD_CPPFLAGS)
AC_SUBST(SPMD_LDFLAGS)

AC_SUBST(ADIOS_CPPFLAGS)
AC_SUBST(ADIOS_LDFLAGS)

AC_OUTPUT(src/Makevars)
