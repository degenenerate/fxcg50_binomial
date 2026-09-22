#ifndef FRACTION_H
#define FRACTION_H

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"

typedef struct {
    bool positive;
    uint numer;
    uint denom;
} fraction_t;

static const fraction_t FRACTION_ONE   = {true, 1, 1};
static const fraction_t FRACTION_ZERO  = {true, 0, 1};

fraction_t fraction_create(int n, int d);
fraction_t fraction_mult(fraction_t a, fraction_t b);
fraction_t fraction_pow(fraction_t a, int p);
fraction_t fraction_simplify(fraction_t a);
uint gcd(uint a, uint b);

char *format_fraction(fraction_t a);

#endif
