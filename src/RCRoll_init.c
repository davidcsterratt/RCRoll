#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP C_rollmin(SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"C_rollmin", (DL_FUNC) &C_rollmin, 2},
    {NULL, NULL, 0}
};

void R_init_RCRoll(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
