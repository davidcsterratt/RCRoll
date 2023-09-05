#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* Code adapted from https://richardhartersworld.com/slidingmin/ */
struct pairs {
    double value;
    int death;
};

void minwindow(double *in, double *out, int n, int k)
{
    int i;
    struct pairs * ring;
    struct pairs * minpair;
    struct pairs * end;
    struct pairs * last;
    ring = (struct pairs *)R_alloc(k, sizeof(*ring));
    end  = ring + k;
    last = ring;
    minpair = ring;
    minpair->value = in[0];
    minpair->death = k;
    out[0] = in[0];
    for (i=1;i<n;i++) {
        if (minpair->death == i) {
            minpair++;
            if (minpair >= end) minpair = ring;
        }
        if (in[i] <= minpair->value) {
            minpair->value = in[i];
            minpair->death = i+k;
            last = minpair;
        } else {
            while (last->value >= in[i]) {
                if (last == ring) last = end;
                --last;
            }
            ++last;
            if (last == end) last = ring;
            last->value = in[i];
            last->death = i+k;
        }
        /* Rprintf("i = %2d:", i); */
        /* for (int j=0;j<k;j++) { */
        /*   Rprintf(" j=%d: v:%2.0f d:%d", j, (ring+j)->value, (ring+j)->death); */
        /* } */
        /* Rprintf("\n"); */
        out[i] = minpair->value;
    }
}

SEXP C_rollmin(const SEXP in, const SEXP k) {
  int n = length(in);
  SEXP out = PROTECT(allocVector(REALSXP, n)); /*  - *INTEGER(k) + 1)); */
  minwindow(REAL(in), REAL(out), n, *INTEGER(k));
  UNPROTECT(1);
  return(out);
}
