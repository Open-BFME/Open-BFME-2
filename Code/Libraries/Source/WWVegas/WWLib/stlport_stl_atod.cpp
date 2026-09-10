// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Dedicated TU for STLport _Stl_atod. Do not add this to
// stlport_string_to_double.cpp; that would inline into the landed wrappers.

#include <limits>

_STLP_BEGIN_NAMESPACE

typedef unsigned int uint32;
typedef unsigned __int64 uint64;
#define ULL(x) x##Ui64

template <class T>
inline const T &(min)(const T &a, const T &b)
{
	return a < b ? a : b;
}

void _Stl_mult64(const uint64 u, const uint64 v, uint64 &high, uint64 &low)
{
	const uint64 low_mask = ULL(0xffffffff);
	const uint64 u0 = u & low_mask;
	const uint64 u1 = u >> 32;
	const uint64 v0 = v & low_mask;
	const uint64 v1 = v >> 32;

	uint64 t = u0 * v0;
	low = t & low_mask;

	t = u1 * v0 + (t >> 32);
	uint64 w1 = t & low_mask;
	uint64 w2 = t >> 32;

	uint64 x = u0 * v1 + w1;
	low += (x & low_mask) << 32;
	high = u1 * v1 + w2 + (x >> 32);
}

#define bit11 ULL(0x7ff)
#define exponent_mask (bit11 << 52)

inline void _Stl_set_exponent(uint64 &val, uint64 exp)
{
	val = (val & ~exponent_mask) | ((exp & bit11) << 52);
}

static const uint64 _Stl_tenpow[80] = {
	ULL(0xa000000000000000),
	ULL(0xc800000000000000),
	ULL(0xfa00000000000000),
	ULL(0x9c40000000000000),
	ULL(0xc350000000000000),
	ULL(0xf424000000000000),
	ULL(0x9896800000000000),
	ULL(0xbebc200000000000),
	ULL(0xee6b280000000000),
	ULL(0x9502f90000000000),
	ULL(0xba43b74000000000),
	ULL(0xe8d4a51000000000),
	ULL(0x9184e72a00000000),
	ULL(0xb5e620f480000000),
	ULL(0xe35fa931a0000000),
	ULL(0x8e1bc9bf04000000),
	ULL(0xb1a2bc2ec5000000),
	ULL(0xde0b6b3a76400000),
	ULL(0x8ac7230489e80000),
	ULL(0xad78ebc5ac620000),
	ULL(0xd8d726b7177a8000),
	ULL(0x878678326eac9000),
	ULL(0xa968163f0a57b400),
	ULL(0xd3c21bcecceda100),
	ULL(0x84595161401484a0),
	ULL(0xa56fa5b99019a5c8),
	ULL(0xcecb8f27f4200f3a),
	ULL(0xd0cf4b50cfe20766),
	ULL(0xd2d80db02aabd62c),
	ULL(0xd4e5e2cdc1d1ea96),
	ULL(0xd6f8d7509292d603),
	ULL(0xd910f7ff28069da4),
	ULL(0xdb2e51bfe9d0696a),
	ULL(0xdd50f1996b947519),
	ULL(0xdf78e4b2bd342cf7),
	ULL(0xe1a63853bbd26451),
	ULL(0xe3d8f9e563a198e5),
	ULL(0xfd87b5f28300ca0e),
	ULL(0xfb158592be068d2f),
	ULL(0xf8a95fcf88747d94),
	ULL(0xf64335bcf065d37d),
	ULL(0xf3e2f893dec3f126),
	ULL(0xf18899b1bc3f8ca2),
	ULL(0xef340a98172aace5),
	ULL(0xece53cec4a314ebe),
	ULL(0xea9c227723ee8bcb),
	ULL(0xe858ad248f5c22ca),
	ULL(0xe61acf033d1a45df),
	ULL(0xe3e27a444d8d98b8),
	ULL(0xe1afa13afbd14d6e)
};

static const short _Stl_twoexp[80] = {
	4, 7, 10, 14, 17, 20, 24, 27, 30, 34, 37, 40, 44, 47, 50, 54, 57, 60, 64, 67, 70, 74, 77, 80, 84, 87, 90,
	183, 276, 369, 462, 555, 648, 741, 834, 927, 1020,
	-93, -186, -279, -372, -465, -558, -651, -744, -837, -930, -1023, -1116, -1209
};

#define TEN_1 0
#define TEN_27 26
#define TEN_M28 37
#define NUM_HI_P 11
#define NUM_HI_N 13
#define _Stl_HIBITULL (ULL(1) << 63)

void _Stl_norm_and_round(uint64 &p, int &norm, uint64 prodhi, uint64 prodlo)
{
	norm = 0;
	if (!(prodhi & _Stl_HIBITULL)) {
		if ((prodhi == ~_Stl_HIBITULL) && ((prodlo >> 62) == 0x3)) {
			p = _Stl_HIBITULL;
			return;
		}
		p = (prodhi << 1) | (prodlo >> 63);
		norm = 1;
		prodlo <<= 1;
	} else {
		p = prodhi;
	}

	if ((prodlo & _Stl_HIBITULL) != 0) {
		if (((p & 0x1) != 0) || prodlo != _Stl_HIBITULL) {
			p++;
			if (p == 0)
				p++;
		}
	}
}

void _Stl_tenscale(uint64 &p, int exp, int &bexp)
{
	uint64 prodhi, prodlo;
	int exp_hi, exp_lo;
	int hi, lo, tlo, thi;
	int norm;
	int num_hi;

	bexp = 0;
	if (exp > 0) {
		exp_lo = exp;
		exp_hi = 0;
		if (exp_lo > 27) {
			exp_lo++;
			while (exp_lo > 27) {
				exp_hi++;
				exp_lo -= 28;
			}
		}
		tlo = TEN_1;
		thi = TEN_27;
		num_hi = NUM_HI_P;
	} else if (exp < 0) {
		exp_lo = exp;
		exp_hi = 0;
		while (exp_lo < 0) {
			exp_hi++;
			exp_lo += 28;
		}
		tlo = TEN_1;
		thi = TEN_M28;
		num_hi = NUM_HI_N;
	} else {
		return;
	}
	while (exp_hi) {
		hi = (min)(exp_hi, num_hi);
		exp_hi -= hi;
		hi += thi - 1;
		_Stl_mult64(p, _Stl_tenpow[hi], prodhi, prodlo);
		_Stl_norm_and_round(p, norm, prodhi, prodlo);
		bexp += _Stl_twoexp[hi] - norm;
	}
	if (exp_lo) {
		lo = tlo + exp_lo - 1;
		_Stl_mult64(p, _Stl_tenpow[lo], prodhi, prodlo);
		_Stl_norm_and_round(p, norm, prodhi, prodlo);
		bexp += _Stl_twoexp[lo] - norm;
	}
}

double __cdecl _Stl_atod(char *buffer, int ndigit, int dexp)
{
	uint64 value;
	uint32 guard;
	uint64 rest;
	int bexp;
	int nzero;
	int sexp;
	char *bufferend;

	if (buffer == 0) {
		return 0.0;
	}

	bufferend = buffer + ndigit;
	value = 0;

	while (buffer < bufferend) {
		value *= 10;
		value += *buffer++;
	}

	if (value == 0) {
		return 0.0;
	}

	bexp = 64;

	nzero = 0;
	if ((value >> 32) != 0) {
		nzero = 32;
	}
	if ((value >> (16 + nzero)) != 0) {
		nzero += 16;
	}
	if ((value >> (8 + nzero)) != 0) {
		nzero += 8;
	}
	if ((value >> (4 + nzero)) != 0) {
		nzero += 4;
	}
	if ((value >> (2 + nzero)) != 0) {
		nzero += 2;
	}
	if ((value >> (1 + nzero)) != 0) {
		nzero += 1;
	}
	if ((value >> (nzero)) != 0) {
		nzero += 1;
	}

	value <<= (64 - nzero);
	bexp -= 64 - nzero;

	_Stl_tenscale(value, dexp, sexp);
	bexp += sexp;

	if (bexp <= -1022) {
		bexp += 1022;
		if (bexp < -53) {
			value = 0;
		} else {
			int lead0;

			lead0 = 12 - bexp;

			if (lead0 > 64) {
				rest = value;
				guard = 0;
				value = 0;
			} else if (lead0 == 64) {
				rest = value & ((ULL(1) << 63) - 1);
				guard = (uint32)((value >> 63) & 1);
				value = 0;
			} else {
				rest = value & (((ULL(1) << lead0) - 1) - 1);
				guard = (uint32)(((value >> lead0) - 1) & 1);
				value >>= lead0;
			}

			if (guard && ((value & 1) || rest)) {
				value++;
				if (value == (ULL(1) << 52)) {
					value = 0;
					_Stl_set_exponent(value, 1);
				}
			}
		}
	} else {
		rest = value & (1 << 10) - 1;
		value >>= 10;
		guard = (uint32)value & 1;
		value >>= 1;

		if (guard) {
			if (((value & 1) != 0) || (rest != 0)) {
				value++;
				if ((value >> 53) != 0) {
					value >>= 1;
					bexp++;
				}
			}
		}

		if (bexp > 1024) {
			return numeric_limits<double>::infinity();
		} else {
			value &= ~(ULL(1) << 52);
			_Stl_set_exponent(value, bexp + 1022);
		}
	}

	return *((double *)&value);
}

_STLP_END_NAMESPACE
