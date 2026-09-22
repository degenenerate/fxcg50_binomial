#include "../include/fraction.h"

fraction_t fraction_create(int n, int d)
{
    bool sign = (n > 0) == (d > 0);
    return (fraction_t){sign, abs(n), abs(d)};
}

fraction_t fraction_mult(fraction_t a, fraction_t b) 
{
     return (fraction_t){a.positive == b.positive, 
                         a.numer * b.numer, 
                         a.denom * b.denom
                        };
}

fraction_t fraction_pow(fraction_t a, int p)
{
    if(p == 0) return FRACTION_ONE;
    if(p < 0) {
        uint d = a.denom;
        a.denom = a.numer;
        a.numer = d;
        p = -p;
    }

    a = fraction_simplify(a);
    fraction_t o = a;
    for(int i=0; i<p-1; ++i) {
        o.positive = o.positive == a.positive;
        o.numer *= a.numer;
        o.denom *= a.denom;
    }
    return o;
}

fraction_t fraction_simplify(fraction_t a) 
{
    uint g = gcd(a.numer, a.denom);
    return (fraction_t){a.positive, a.numer / g, a.denom / g};
}

uint gcd(uint a, uint b)
{
    if( (a < 2) || (b < 2) ) return 1;
    if( a == b ) return a;
    uint m = 1;
    uint ha = a / 2; uint hb = b / 2;
    for(int i=2; (i<=ha) || (i<=hb); ++i) {
        if((a % i == 0) && (b % i == 0)) {
            m *= i;
            a /= i; b /= i;
            ha = a / 2; hb = b / 2;

            //So next loop starts with i = 2
            i = 1;
        }
    }
    return m;
}

char *format_fraction(fraction_t a)
{
    static char buffer[32];
    if(a.numer == 0) {
        sprintf(buffer, "0");
    }
    else if(a.denom == 1) {
        sprintf(buffer, "%u", a.numer);
    }
    else {
        sprintf(buffer, "(%u/%u)", a.numer, a.denom);
    }

    return buffer; 
}
