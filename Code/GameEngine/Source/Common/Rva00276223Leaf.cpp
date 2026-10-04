// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?rva00276223@Rva00276223@@QAEXVAsciiString@@_NH@Z @0x00276223 107B: __thiscall leaf iterating null-terminated Element* array at +0x14C via vtable+0xA8 then StringBase-sliced forward to vtable+0x8C.
// The flag argument is a bool: its only caller, AttachedModelFXNugget::doFXObj 0x001E0878, pushes the byte member at +0x14C unextended.
// Evidence: callers 0x001E08C5 unclaimed; callees rowed StringBase copy 0x000365F0 and releaseBuffer 0x00036410; neighbours Rva00275D9FGet /O1 and BFMERopeDrawableGetPosition /O1 /EHsc.
#include "ascii_string.h"

class Rva00276223Result
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void v35(AsciiString s, bool a, int b);
};

class Rva00276223Element
{
public:
	virtual void e00();
	virtual void e01();
	virtual void e02();
	virtual void e03();
	virtual void e04();
	virtual void e05();
	virtual void e06();
	virtual void e07();
	virtual void e08();
	virtual void e09();
	virtual void e10();
	virtual void e11();
	virtual void e12();
	virtual void e13();
	virtual void e14();
	virtual void e15();
	virtual void e16();
	virtual void e17();
	virtual void e18();
	virtual void e19();
	virtual void e20();
	virtual void e21();
	virtual void e22();
	virtual void e23();
	virtual void e24();
	virtual void e25();
	virtual void e26();
	virtual void e27();
	virtual void e28();
	virtual void e29();
	virtual void e30();
	virtual void e31();
	virtual void e32();
	virtual void e33();
	virtual void e34();
	virtual void e35();
	virtual void e36();
	virtual void e37();
	virtual void e38();
	virtual void e39();
	virtual void e40();
	virtual void e41();
	virtual Rva00276223Result *v42();
};

class Rva00276223
{
public:
	void rva00276223(AsciiString s, bool a, int b);

private:
	char m_pad[0x14C];
	Rva00276223Element **m_items;
};

void Rva00276223::rva00276223(AsciiString s, bool a, int b)
{
	Rva00276223Element **arr = m_items;
	for (Rva00276223Element **p = arr; *p != 0; ++p) {
		Rva00276223Element *e = *p;
		Rva00276223Result *r = e->v42();
		if (r == 0)
			continue;
		r->v35(s, a, b);
	}
}
