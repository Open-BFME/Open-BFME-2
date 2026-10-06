// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00434CF4@@QAE@PAI0@Z @0x00434CF4 134B: stack-object ctor calls rowed 0x00434995 for seeds then imul-xor chain over 8 dwords; sibling of 0x00434C67 with m3=m1=0x0C281240; caller 0x0043541B.
void __cdecl Rva00434995Get(unsigned *a, unsigned *b);
class Rva00434CF4
{
public:
	Rva00434CF4(unsigned *a, unsigned *b);
private:
	unsigned m0, m1, m2, m3, m4, m5, m6, m7;
};
Rva00434CF4::Rva00434CF4(unsigned *a, unsigned *b)
{
	unsigned t1, t2;
	Rva00434995Get(&t1, &t2);
	m0 = t1;
	unsigned c = t2;
	unsigned k = 0x0C281240;
	m1 = k;
	m2 = 0x48000A06;
	m3 = k;
	m4 = *a;
	m5 = *b;
	unsigned e = c * c;
	e ^= k;
	m1 = e;
	e *= c;
	e ^= 0x48000A06;
	m2 = e;
	e *= c;
	e ^= k;
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
