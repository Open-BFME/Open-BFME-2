// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB

// ?rva005DDC6B@Rva005DDC6B@@QAEMII@Z, RVA 0x005DDC6B, 58B. Unlock lane: float
// range-sum method over 8-byte elements; base pointer at +4 has a 4-byte
// header, elements hold the summed float at +0. Unsigned lo/hi give the jae
// early-out; do-while with dec/jne; x87 fld return. One caller at 0x005DDE60
// in 0x005DDE33. Owner unknown so honest address-derived method name. Flags
// copy the prev neighbour Rva005DD772Ctor.cpp for the SSE float idioms.
// ?rva005DDCA5@Rva005DDC6B@@QAEMII@Z @0x005DDCA5 64B. Float range-max with
// init from 0x00BBB8DC, comiss/jbe keep-largest, same stride. Caller 0x005DDE96.
// ?rva005DDCE5@Rva005DDC6B@@QAEMII@Z @0x005DDCE5 91B. Float range-min over
// the non-zero entries (FLT_MAX from 0x00BBB8E0 as the empty marker, 0 when
// nothing qualified or the range is empty), same stride. Caller 0x005DDECC.
// Structural inference: both zero results reach one shared store, which
// retail gets by hoisting xorps before the range test; written as a goto to
// that store.

class Rva005DDC6B
{
public:
	float rva005DDC6B(unsigned lo, unsigned hi);
	float rva005DDCA5(unsigned lo, unsigned hi);
	float rva005DDCE5(unsigned lo, unsigned hi);
private:
	int m_00;
	char *m_04;
};

float Rva005DDC6B::rva005DDC6B(unsigned lo, unsigned hi)
{
	float sum = 0.0f;
	if (lo < hi) {
		float *p = (float *)(m_04 + lo * 8 + 4);
		unsigned n = hi - lo;
		do {
			sum += *p;
			p = (float *)((char *)p + 8);
		} while (--n != 0);
	}
	return sum;
}

float Rva005DDC6B::rva005DDCA5(unsigned lo, unsigned hi)
{
	float cur = (-3.4028235e+38f);
	if (lo < hi) {
		float *p = (float *)(m_04 + lo * 8 + 4);
		unsigned n = hi - lo;
		do {
			float v = *p;
			if (v > cur)
				cur = v;
			p = (float *)((char *)p + 8);
		} while (--n != 0);
	}
	return cur;
}

float Rva005DDC6B::rva005DDCE5(unsigned lo, unsigned hi)
{
	float best = 3.4028235e+38f;
	float ret;
	if (lo < hi) {
		float *p = (float *)(m_04 + lo * 8 + 4);
		unsigned n = hi - lo;
		do {
			float v = *p;
			if (v != 0.0f) {
				if (v < best)
					best = v;
			}
			p = (float *)((char *)p + 8);
		} while (--n != 0);
		ret = best;
		if (ret != 3.4028235e+38f)
			goto done;
	}
	ret = 0.0f;
done:
	return ret;
}
