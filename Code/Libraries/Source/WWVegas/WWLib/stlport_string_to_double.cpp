// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Dedicated TU for STLport _Stl_string_to_double. The wrapper unit
// stlport_string_to_float.cpp already holds the three __string_to_float
// bodies and only declares this helper.

#include <limits>
#include <locale>

_STLP_BEGIN_NAMESPACE

double __cdecl _Stl_atod(char *buffer, int ndigit, int dexp);

double __cdecl _Stl_string_to_double(const char *s)
{
	const int max_digits = 17;
	unsigned c;
	unsigned Negate, decimal_point;
	char *d;
	int exp;
	double x;
	int dpchar;
	char digits[max_digits];

	const ctype<char> &ct = use_facet<ctype<char> >(locale::classic());
	while (c = *s++, ct.is(ctype_base::space, char(c)))
		;

	Negate = 0;
	if (c == '+') {
		c = *s++;
	} else if (c == '-') {
		Negate = 1;
		c = *s++;
	}
	d = digits;
	dpchar = '.' - '0';
	decimal_point = 0;
	exp = 0;
	for (;;) {
		c -= '0';
		if (c < 10) {
			if (d == digits + max_digits) {
				exp += (decimal_point ^ 1);
			} else {
				if (c == 0 && d == digits) {
				} else {
					*d++ = (char)c;
				}
				exp -= decimal_point;
			}
		} else if (c == (unsigned int)dpchar && !decimal_point) {
			decimal_point = 1;
		} else {
			break;
		}
		c = *s++;
	}
	if (d == digits) {
		return 0.0;
	}
	if (c == 'e' - '0' || c == 'E' - '0') {
		register unsigned negate_exp = 0;
		register int e = 0;
		c = *s++;
		if (c == '+' || c == ' ') {
			c = *s++;
		} else if (c == '-') {
			negate_exp = 1;
			c = *s++;
		}
		if (c -= '0', c < 10) {
			do {
				if (e <= 340)
					e = e * 10 + (int)c;
				else
					break;
				c = *s++;
			} while (c -= '0', c < 10);
			if (negate_exp) {
				e = -e;
			}
			if (e < -340 || e > 340)
				exp = e;
			else
				exp += e;
		}
	}

	if (exp < -340) {
		x = 0;
	} else if (exp > 308) {
		x = numeric_limits<double>::infinity();
	} else {
		x = _Stl_atod(digits, (int)(d - digits), exp);
	}
	if (Negate) {
		x = -x;
	}
	return x;
}

_STLP_END_NAMESPACE
