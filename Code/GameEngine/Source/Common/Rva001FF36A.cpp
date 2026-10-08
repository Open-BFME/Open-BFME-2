// cl: /MD
//
// ?rva001FF36A@Rva001FF36A@@QAE_NHHHHHH@Z @0x001FF36A 63B
// Leaf with conditional stores to +0 +0x0C +0x10 plus unconditional +0x14
// then verified pool grow 0x002E8548 when +4 is zero else false.
// Shared grow bytes prove callback fields at +0x0C/+0x10 and context+0x14.
// Evidence: address-derived name; caller 0x002EBABF in
// Rva002EBA88; prev ReloadIniFileNotices and next VtableVirtualForwarders.
#include "../../Include/Common/Rva002E8548Pool.h"

class Rva001FF36A : public Rva002E8548
{
public:
	bool rva001FF36A(int a1, int a2, int a3, int a4, int a5, int a6);
};

bool Rva001FF36A::rva001FF36A(int a1, int a2, int a3, int a4, int a5, int a6)
{
	if (a1)
		m_00 = a1;
	if (a4)
		m_alloc = reinterpret_cast<void *(__cdecl *)(int, int)>(a4);
	if (a5)
		m_free = reinterpret_cast<void (__cdecl *)(void *, int)>(a5);
	m_14 = a6;
	if (m_04 == 0)
		return rva002E8548(a2, a3);
	return false;
}
