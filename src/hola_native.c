#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP hola_advance(SEXP, SEXP, SEXP);
extern SEXP hola_begin_step(SEXP, SEXP);
extern SEXP hola_available_variables(SEXP);
extern SEXP hola_close(SEXP);
extern SEXP hola_init(SEXP, SEXP);
extern SEXP hola_open(SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP hola_read(SEXP, SEXP, SEXP);
extern SEXP hola_read_to_buf(SEXP, SEXP, SEXP, SEXP);
extern SEXP hola_write(SEXP, SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"hola_advance",              (DL_FUNC) &hola_advance,              3},
  {"hola_begin_step",           (DL_FUNC) &hola_begin_step,           2},
  {"hola_available_variables",  (DL_FUNC) &hola_available_variables,  1},
  {"hola_close",                (DL_FUNC) &hola_close,                1},
  {"hola_init",                 (DL_FUNC) &hola_init,                 2},
  {"hola_open",                 (DL_FUNC) &hola_open,                 5},
  {"hola_read",                 (DL_FUNC) &hola_read,                 3},
  {"hola_read_to_buf",          (DL_FUNC) &hola_read_to_buf,          4},
  {"hola_write",                (DL_FUNC) &hola_write,                4},
  {NULL, NULL, 0}
};

void R_init_hola(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
