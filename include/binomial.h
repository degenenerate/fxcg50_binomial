#ifndef BINOMIAL_H
#define BINOMIAL_H

#include <string.h>
#include "fraction.h"

typedef enum {
    BINOMIAL_SIMPLE,     //  (ax+b)^p
    BINOMIAL_COMPLEX,    // a(1+bx)^p
} binomial_type_t;

uint factorial(uint n);
uint nCr(uint n, uint r);

fraction_t binomial_simple_n(fraction_t a, fraction_t b, uint p, uint n);
fraction_t binomial_complex_n(fraction_t a, fraction_t b, fraction_t p, uint n);
fraction_t *binomial_expansion(binomial_type_t expansion_type, fraction_t a, fraction_t b, fraction_t p, int n_start, int n_incr, int n_count);

void format_simple_expansion(fraction_t *coefs, char *out, uint p, int n_start, int n_incr, int n_count);
void format_complex_expansion(fraction_t *coefs, char *out, int n_start, int n_incr, int n_count);

#endif
