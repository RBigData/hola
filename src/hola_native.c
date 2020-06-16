#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP hola_advance(SEXP, SEXP);
extern SEXP hola_available_variables(SEXP);
extern SEXP hola_close(SEXP);
extern SEXP hola_open(SEXP, SEXP);
extern SEXP hola_read(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"hola_advance",              (DL_FUNC) &hola_advance,              2},
  {"hola_available_variables",  (DL_FUNC) &hola_available_variables,  1},
  {"hola_close",                (DL_FUNC) &hola_close,                1},
  {"hola_open",                 (DL_FUNC) &hola_open,                 2},
  {"hola_read",                 (DL_FUNC) &hola_read,                 3},
  {NULL, NULL, 0}
};

void R_init_hola(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
