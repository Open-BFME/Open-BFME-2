// ?rva00496D43@Rva00496D43@@QAEPAXPAXABVAsciiString@@@Z
// partial score=0.94 date=2026-10-03
// ?rva00496D43@Rva00496D43@@QAEPAXPAXABVAsciiString@@@Z
// partial score=0.94 date=2026-10-02
// cl: /Ireference/shims/bfme2_ascii /EHs-c- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// ?rva00496D43@Rva00496D43@@QAEPAXPAXABVAsciiString@@@Z, retail 0x00496D43 96B.
// Leaf: vector at this+0x18/0x1c of Elem* (AsciiString at +0, Weapon set at +8);
// linear compareNoCase vs key; on hit copy-constructs WeaponTemplateSetHead from
// elem+8 into out, else constructs Rva0028F59A(0,0xb8) into out; returns out.
// Evidence: callees compareNoCase 0x00006A00 Rva0028F59A ctor 0x0028F59A
// WeaponTemplateSetHead copy 0x00045455, caller 0x00496E2B.
#include "ascii_string.h"
#include <new>

struct Rva0028F59A
{
	unsigned m_bits[19];
	Rva0028F59A(int unused, int bit);
};

class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
	char m_data[0x4C];
};

struct Rva00496D43Elem : public AsciiString
{
	char m_pad04[4];
	WeaponTemplateSetHead m_set08;
};

class Rva00496D43
{
public:
	void *rva00496D43(void *out, const AsciiString &key);
private:
	char m_pad00[0x18];
	Rva00496D43Elem **m_begin18;
	Rva00496D43Elem **m_end1C;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void *Rva00496D43::rva00496D43(void *out, const AsciiString &key)
{
	for (unsigned i = 0; i < (unsigned)(m_end1C - m_begin18); ++i) {
		_ReadWriteBarrier();
		if (((const StringBase<char> &)*m_begin18[i]).compareNoCase((const StringBase<char> &)key) == 0) {
			__assume(out != 0);
			new (out) WeaponTemplateSetHead(m_begin18[i]->m_set08);
			return out;
		}
	}
	__assume(out != 0);
	new (out) Rva0028F59A(0, 0xb8);
	return out;
}
