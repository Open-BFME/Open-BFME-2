// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0037DF2C@@QAE@ABV0@@Z @0x001EB79E 119B: copy ctor of CarryoverUnit.
// Same vtable 0x00BDF158 at +0 and layout as default ctor 0x0037DF2C:
// AsciiString at +4 via rowed 0x000365F0, float at +8 int at +C, 128B block
// at +0x10 via rowed 0x0004548B, int at +0x90, tail at +0x94 via rowed
// 0x001EB15A. Callers at 0x001EBA02 0x001EBEEC 0x0040D691. Empty base with
// inline ctor plus declared-only dtor arms EH state 0 per ModuleData precedent.
#include "ascii_string.h"
#include "unicode_string.h"
extern "C" const void *const __identifier("??_7CarryoverUnit@@6B@")[];
#include "../../Include/Common/EmptyBase.h"
struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128 &o);
	unsigned char bytes[128];
};
#include "../../Include/Common/Rva001EB15A.h"
class CarryoverUnit : public EmptyBase
{
public:
	CarryoverUnit(const CarryoverUnit &o);
private:
	unsigned int m_vtable;
	AsciiString m_s04;
	float m_f08;
	int m_c0C;
	BfmeFixedStorage128 m_h10;
	int m_90;
	Rva001EB15A m_94;
};
CarryoverUnit::CarryoverUnit(const CarryoverUnit &carryoverUnit)
	: m_vtable((unsigned int)__identifier("??_7CarryoverUnit@@6B@"))
	, m_s04(carryoverUnit.m_s04)
	, m_f08(carryoverUnit.m_f08)
	, m_c0C(carryoverUnit.m_c0C)
	, m_h10(carryoverUnit.m_h10)
	, m_90(carryoverUnit.m_90)
	, m_94(carryoverUnit.m_94)
{
}
