#ifndef BINOMIAL_H
#define BINOMIAL_H

#include <string.h>
#include "fraction.h"

typedef enum {
    BINOMIAL_SIMPLE,     //  (ax+b)^p
    BINOMIAL_COMPLEX,    // a(1+bx)^p
} binomial_type_t;

typedef struct {
    binomial_type_t type;
    fraction_t a;
    fraction_t b;
    fraction_t p;
    int n_start;
    int n_incr;
    int n_count;
} binomial_info_t;

uint factorial(uint n);
uint nCr(uint n, uint r);

fraction_t binomial_simple_n(fraction_t a, fraction_t b, uint p, uint n);
fraction_t binomial_complex_n(fraction_t a, fraction_t b, fraction_t p, uint n);
fraction_t *binomial_expansion(binomial_info_t *info);

// 10 comes from ceil(log10(1 << 30))
//+(%u/%u)x^%u -> 2+10+1+10+3+10 -> 36
#define MAX_BINOMIAL_TERM_SIZE 36
#define MAX_BINOMIAL_OUTPUT 512
void format_expansion(char *out, fraction_t *coefs, binomial_info_t *info);

#endif
