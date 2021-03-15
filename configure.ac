AC_PREREQ([2.69])
AC_INIT()
AC_CONFIG_SRCDIR()
AC_CONFIG_MACRO_DIR([tools/])

# Determine R_HOME.
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi

R_SCMD="${R_HOME}/bin/Rscript -e"

FLOAT_LIBS=`${R_SCMD} "float:::ldflags()"`
FLOAT_INCL=`${R_SCMD} "float:::cppflags()"`



# ------------------------------------------------------------------------------
# MPI
# ------------------------------------------------------------------------------

AC_ARG_ENABLE(mpi,
  AC_HELP_STRING(
    [--enable-mpi], 
    [Enable MPI bindings.]
  ),
  [USE_MPI="TRUE"],
  [USE_MPI="FALSE"]
)

if test "X${USE_MPI}" = "XTRUE"; then
  AC_MSG_NOTICE([using MPI])
  HAS_PACKAGES=`${R_SCMD} "cat(all(c('pbdMPI') %in% installed.packages()))"`
  if test "X${HAS_PACKAGES}" = "XFALSE"; then
    AC_MSG_FAILURE([pbdMPI and must be installed when using MPI backend])
  fi
  
  SPMD_CPPFLAGS=`${R_SCMD} "source('./R/conf/get_conf.r');get.conf('PKG_CPPFLAGS','"${R_ARCH}"')"`
  SPMD_LDFLAGS=`${R_SCMD} "source('./R/conf/get_conf.r');get.conf('PKG_LIBS','"${R_ARCH}"')"`
  ADIOS_MPI_FLAG=""
else
  ADIOS_MPI_FLAG=" -s"
  AC_MSG_NOTICE([not using MPI])
fi



# ------------------------------------------------------------------------------
# ADIOS
# ------------------------------------------------------------------------------

AC_ARG_WITH([adios2-home],
  AC_HELP_STRING(
    [--with-adios2-home=ADIOS_PATH],
    [location of ADIOS2 installation]
  ),
  [ADIOS_PATH=$withval]
)

AC_CHECK_PROG([ADIOS2_CONFIG], [adios2-config], yes, [no])
if test x"${ADIOS2_CONFIG}" == x"yes"; then
  ADIOS_CPPFLAGS=`adios2-config --cxx-flags ${ADIOS_MPI_FLAG}`
  ADIOS_LDFLAGS=`adios2-config --cxx-libs ${ADIOS_MPI_FLAG}`
  ADIOS_VERSION=`adios2-config -v | head -n 1 | sed -e 's/ADIOS //'`
else
  if test -z "${ADIOS_PATH}"; then
    AC_MSG_ERROR([ERROR: could not determine ADIOS_PATH; please set --with-adios2-home])
  fi
  
  AC_CHECK_PROG([CUSTOM_ADIOS2_CONFIG], [adios2-config], yes, [no], [${ADIOS_PATH}/bin])
  
  if test x"${CUSTOM_ADIOS2_CONFIG}" == x"yes"; then
    ADIOS_CPPFLAGS=`${ADIOS_PATH}/bin/adios2-config --cxx-flags ${ADIOS_MPI_FLAG}`
    ADIOS_LDFLAGS=`${ADIOS_PATH}/bin/adios2-config --cxx-libs ${ADIOS_MPI_FLAG}`
    ADIOS_VERSION=`${ADIOS_PATH}/bin/adios2-config -v | head -n 1 | sed -e 's/ADIOS //'`
  else
    AC_MSG_ERROR([could not find adios2-config either in \$PATH or the specified adios2-home])
  fi
fi


ADIOS_VERSION_MINIMUM="2.7.1"
AC_MSG_NOTICE([checking for suitable ADIOS2 version])
AX_COMPARE_VERSION([${ADIOS_VERSION}], [ge], [${ADIOS_VERSION_MINIMUM}], [],
   [AC_MSG_ERROR([Requires ADIOS2 >= $ADIOS_VERSION_MINIMUM (found $ADIOS_VERSION).])])



# ------------------------------------------------------------------------------
# report
# ------------------------------------------------------------------------------

echo " "
echo "******************** Results of hola package configure *******************"
echo " "
echo "* R Report:"
echo "    >> FLOAT_LIBS=${FLOAT_LIBS}"
echo "    >> FLOAT_INCL=${FLOAT_INCL}"
echo "* MPI report:"
if test "X${USE_MPI}" = "XTRUE"; then
  echo "    >> SPMD_CPPFLAGS = ${SPMD_CPPFLAGS}"
  echo "    >> SPMD_LDFLAGS = ${SPMD_LDFLAGS}"
else
  echo "    >> not used"
fi
echo "* ADIOS2 report:"
echo "    >> ADIOS_VERSION = ${ADIOS_VERSION}"
echo "    >> ADIOS_CPPFLAGS = ${ADIOS_CPPFLAGS}"
echo "    >> ADIOS_LDFLAGS = ${ADIOS_LDFLAGS}"
echo " "
echo "**************************************************************************"
echo " "


AC_SUBST(FLOAT_LIBS)
AC_SUBST(FLOAT_INCL)

AC_SUBST(USE_MPI)
AC_SUBST(SPMD_CPPFLAGS)
AC_SUBST(SPMD_LDFLAGS)

AC_SUBST(ADIOS_CPPFLAGS)
AC_SUBST(ADIOS_LDFLAGS)

AC_OUTPUT(src/Makevars)
AC_OUTPUT(R/features.r)
