#include "../include/binomial.h"

uint factorial(uint n)
{
    uint o = 1;
    for(int i=2; i<=n; ++i) {
        o *= i;
    }
    return o;
}

uint nCr(uint n, uint r)
{

    if(n == 0) return 1;

    // n!/( (n-r)! r! )
    uint a, b;
    if(n-r >= r) {
        a = n-r; b=r;
    } else {
        b = n-r; a=r;
    }

    uint numer = 1;
    for(int i=n; i>a ; --i) {
        numer *= i;
    }

    uint denom = factorial(b);

    return numer / denom;
}

fraction_t binomial_simple_n(fraction_t a, fraction_t b, uint p, uint n)
{
    //Assuming that p >= n
    fraction_t pa = fraction_pow(a, p - n);
    fraction_t pb = fraction_pow(b, n);
    fraction_t o = fraction_mult(pa, pb, false);
    o.numer *= nCr(p, n);
    return fraction_simplify(o);
}

fraction_t binomial_complex_n(fraction_t a, fraction_t b, fraction_t p, uint n)
{
    // a(1+bx)^p
    if(n == 0) return fraction_simplify(a);
    
    // [n(n-1)(n-2)...]/d! * (bx)^d
    // n -> (j/k)
    // n(n-1)(n-2)... = (j/k)(j-k / k)(j-2k / k)...
    int j = 1;
    uint k = 1;
    for(int i=0; i<n; ++i) {
        if(p.positive) {
            j *=  ((int)p.numer - (int)i*p.denom);
        } else {
            j *= ((int)-p.numer - (int)i*p.denom);
        }
        k *= p.denom;
    }
    k *= factorial(n);
    fraction_t l = {j > 0, abs(j), k};
    fraction_t r = fraction_mult(fraction_pow(b, n), a, false);
    return fraction_mult(l, r, true);
}

fraction_t *binomial_expansion(binomial_type_t expansion_type, fraction_t a, fraction_t b, fraction_t p, int n_start, int n_incr, int n_count)
{
    fraction_t *coefs = malloc(sizeof(fraction_t) * n_count);
    for(int i=0; i<n_count; i++) {
        int n = n_start + i*n_incr;
        switch(expansion_type) {
        case BINOMIAL_SIMPLE:
            coefs[i] = binomial_simple_n(a, b, p.numer, n);
            break;
        case BINOMIAL_COMPLEX:
            coefs[i] = binomial_complex_n(a, b, p, n);
            break;
        }
    }
    return coefs;
}

void format_simple_expansion(fraction_t *coefs, char *out, uint p, int n_start, int n_incr, int n_count)
{
    int offset = 0;
    for(int i=0; i<n_count; i++) {
        int n = n_start + i*n_incr;
        int pow = p - n;
        fraction_t f = coefs[i];
        char *prefix = (f.positive) ? "+" : "-";
        char *fraction = format_fraction(f);
        // sprintf IS FUCKING BROKEN. IT ONLY RETURNS THE NON-FORMATTED CHARACTERS IN THE FORMAT STRING
        // WHY AM I SO SMART HOW DID I FIGURE THIS OUT????????????????????
        // WHY AM I SO SMART HOW DID I FIGURE THIS OUT????????????????????
        sprintf(out+offset, "%s%sx^%i", prefix, fraction, pow);
        offset += strlen(out+offset);
    }
}

void format_complex_expansion(fraction_t *coefs, char *out, int n_start, int n_incr, int n_count)
{
    int offset = 0;
    for(int i=0; i<n_count; i++) {
        int n = n_start + i*n_incr;
        fraction_t f = coefs[i];
        char *prefix = (f.positive) ? "+" : "-";
        char *fraction = format_fraction(f);
        sprintf(out+offset, "%s%sx^%i", prefix, fraction, n);
        offset += strlen(out+offset);
    }
}
