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
    // b <= a <= n
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
    fraction_t o = fraction_mult(pa, pb);
    o.numer *= nCr(p, n);
    return fraction_simplify(o);
}

fraction_t binomial_complex_n(fraction_t a, fraction_t b, fraction_t p, uint n)
{
    // a(1+bx)^p
    if(n == 0) return fraction_simplify(a);
    
    // [p(p-1)(p-2)...]/n! * (bx)^n
    // p -> (j/k) or (-j/k)
    // p(p-1)(p-2)... = (j/k)(j-k / k)(j-2k / k)... = (j(j-k)(j-2k)...)/(k^...)
    int j = 1;
    uint k = 1;
    p = fraction_simplify(p);
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
    fraction_t r = fraction_mult(fraction_pow(b, n), a);
    return fraction_simplify(fraction_mult(l, r));
}

fraction_t *binomial_expansion(binomial_info_t *info)
{
    fraction_t *coefs = malloc(sizeof(fraction_t) * info->n_count);
    for(int i=0; i<info->n_count; i++) {
        int n = info->n_start + i*info->n_incr;
        switch(info->type) {
        case BINOMIAL_SIMPLE:
            coefs[i] = binomial_simple_n(info->a, info->b, info->p.numer, n);
            break;
        case BINOMIAL_COMPLEX:
            coefs[i] = binomial_complex_n(info->a, info->b, info->p, n);
            break;
        }
    }
    return coefs;
}

void format_expansion(char *out, fraction_t *coefs, binomial_info_t *info)
{
    int offset = 0;
    for(int i=0; i<info->n_count; i++) {
        int n = info->n_start + i*info->n_count;

        int pow;
        switch(info->type) {
        case BINOMIAL_SIMPLE:
            pow = info.p.numer - n;
        case BINOMIAL_COMPLEX:
            pow = n;
        }

        fraction_t f = coefs[i];
        char *prefix = (f.positive) ? "+" : "-";
        char *fraction = format_fraction(f);
        // sprintf IS FUCKING BROKEN. IT ONLY RETURNS THE LENGTH OF THE NON-FORMATTED CHARACTERS IN THE FORMAT STRING
        sprintf(out+offset, "%s%sx^%i", prefix, fraction, pow);
        offset += strlen(out+offset);
    }
}
