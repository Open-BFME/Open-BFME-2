// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00434C67@@QAE@PAI0@Z @0x00434C67 141B: stack-object ctor calls rowed 0x00434969 for seeds then imul-xor chain over 8 dwords; caller 0x0043538F lea ecx ebp-20; prev 0x00434C3D same cl.
void __cdecl Rva00434969Get(unsigned *a, unsigned *b);
class Rva00434C67
{
public:
	Rva00434C67(unsigned *a, unsigned *b);
private:
	unsigned m0, m1, m2, m3, m4, m5, m6, m7;
};
Rva00434C67::Rva00434C67(unsigned *a, unsigned *b)
{
	unsigned t1, t2;
	Rva00434969Get(&t1, &t2);
	m0 = t1;
	m1 = 0x0C281240;
	m2 = 0x48000A06;
	unsigned c3 = 0x14A8024B;
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
