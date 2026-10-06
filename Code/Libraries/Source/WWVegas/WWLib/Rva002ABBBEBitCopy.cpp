// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002ABBBE@Rva002ABBBE@@QAEXPAX@Z, RVA 0x002ABBBE, size 100: dword-bitset to byte-bitset then virtual call.
// Evidence: memset 28B via ji_006291ae row; 218-iter bit loop; virtual call +0x24; callers 0x002AC09F 0x0039D6EC.

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class Other002ABBBE
{
public:
	virtual void _f0();
	virtual void _f1();
	virtual void _f2();
	virtual void _f3();
	virtual void _f4();
	virtual void _f5();
	virtual void _f6();
	virtual void _f7();
	virtual void _f8();
	virtual void func(unsigned char *p, int n);
};

class Rva002ABBBE
{
public:
	unsigned int m_bits[7];
	void rva002ABBBE(void *other);
};

void Rva002ABBBE::rva002ABBBE(void *other)
{
	unsigned char dest[28];
	ji_006291ae(dest, 0, 28);
	for (int i = 0; i < 0xDA; ++i) {
		if (m_bits[((unsigned int)i >> 5)] & (1 << (i & 31))) {
			dest[i / 8] |= (unsigned char)(1 << (i % 8));
		}
	}
	Other002ABBBE *o = (Other002ABBBE *)other;
	o->func(dest, 28);
}
