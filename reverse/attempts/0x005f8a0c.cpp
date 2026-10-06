// ?Rva005F8A0C@@YA?AU__m128@@HHH@Z
// partial score=0.65 date=2026-10-06
// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?Rva005F8A0C@@YA?AU__m128@@HHH@Z @0x005F8A0C 114B evidence: __cdecl search QED
// returning __m128 in xmm0 (no x87 anywhere in retail: xorps/movss/cvtsi2ss/
// divss only, so the float spelling cannot match and intrinsics are the
// honest source): res = just-landed ?Rva005F88F4Get@@YAHH@Z @0x005F88F4(a);
// null res returns _mm_load_ss of shared 1.0f g_Va00BBB8D8; else vec = res
// virtual slot 13 (+0x34), dword count = (end-begin)/4 from its +0/+4,
// pointer-bump search of b with break-via-goto (exhaust and empty share or
// -1); idx>0 returns _mm_setzero_ps, idx<0 returns 1.0, idx==0 with b>0
// returns _mm_div_ss(_mm_cvt_si2ss(count), _mm_cvt_si2ss(b)) else zero.
// Result-view classes are TU-local (slots honest, dummies structural).
#include <xmmintrin.h>

class Rva005F8A0CVec
{
public:
	int m_begin;
	int m_end;
};

class Rva005F8A0CRes
{
public:
	virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
	virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
	virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
	virtual int rva005F8A0CCount();			// slot 12 (+0x30)
	virtual Rva005F8A0CVec *rva005F8A0CGetVec();	// slot 13 (+0x34)
};

extern float g_Va00BBB8D8;	// shared 1.0f at VA 0x00BBB8D8

int __cdecl Rva005F88F4Get(int arg);

// ?Rva005F8A0C@@YA?AU__m128@@HHH@Z present-unmatched
__m128 __cdecl Rva005F8A0C(int a, int b, int c)
{
	Rva005F8A0CRes *res = (Rva005F8A0CRes *)Rva005F88F4Get(a);
	__m128 r;
	if (!res)
	{
		r = _mm_load_ss(&g_Va00BBB8D8);
		return r;
	}
	Rva005F8A0CVec *vec = res->rva005F8A0CGetVec();
	int n = (vec->m_end - vec->m_begin) >> 2;
	int *p = (int *)vec->m_begin;
	int idx = 0;
	if (n > 0)
	{
		do
		{
			if (*p == b)
				goto done;
			++idx;
			++p;
		} while (idx < n);
		idx = -1;
	done:;
	}
	else
	{
		idx = -1;
	}
	if (idx != 0)
	{
		if (idx < 0)
		{
			r = _mm_load_ss(&g_Va00BBB8D8);
			return r;
		}
		r = _mm_setzero_ps();
		return r;
	}
	if (c <= 0)
	{
		r = _mm_setzero_ps();
		return r;
	}
	int count = res->rva005F8A0CCount();
	__m128 fb;
	__m128 fc;
	fb = _mm_cvt_si2ss(fb, c);
	fc = _mm_cvt_si2ss(fc, count);
	r = _mm_div_ss(fc, fb);
	return r;
}
