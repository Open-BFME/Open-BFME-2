// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00434E07@@QAE@PAI0@Z @0x00434E07 141B: stack-object ctor calls rowed 0x004349EF for seeds then imul-xor chain over 8 dwords; sibling of 0x00434D7A with c3=0x1800024C; caller 0x004354CD.
void __cdecl Rva004349EFGet(unsigned *a, unsigned *b);
class Rva00434E07
{
public:
	Rva00434E07(unsigned *a, unsigned *b);
private:
	unsigned m0, m1, m2, m3, m4, m5, m6, m7;
};
Rva00434E07::Rva00434E07(unsigned *a, unsigned *b)
{
	unsigned t1, t2;
	Rva004349EFGet(&t1, &t2);
	m0 = t1;
	m1 = 0x0C281240;
	m2 = 0x48000A06;
	unsigned c3 = 0x1800024C;
	m3 = c3;
	m4 = *a;
	m5 = *b;
	unsigned c = t2;
	unsigned e = c * c;
	e ^= 0x0C281240;
	m1 = e;
	e *= c;
	e ^= 0x48000A06;
	m2 = e;
	e *= c;
	e ^= c3;
	m3 = e;
	e *= c;
	m4 ^= e;
	e = m4;
	e *= c;
	m5 ^= e;
	e = m5;
	e *= c;
	m6 ^= e;
	e = m6;
	e *= c;
	m7 ^= e;
}
