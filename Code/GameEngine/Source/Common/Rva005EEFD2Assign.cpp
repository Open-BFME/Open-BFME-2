// cl: /MD
// ??4Rva005EEFD2@@QAEAAV0@ABV0@@Z, retail 0x005EEFD2, 46 bytes.
// Ref-counted holder assignment: if (this != &other) { if (other.m_ptr)
// inc ref at +8; if (m_ptr) Release(m_ptr+4); m_ptr = other.m_ptr; }
// return *this. Release is rowed fastcall 0x0007DEEF. Callers at
// 0x005EF021 0x005EF495 0x005EF4D9 copy arrays of holders.

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

#include "../../Include/Common/Rva005EEFD2Target.h"

#include "../../Include/Common/Rva005EEFD2.h"

Rva005EEFD2 &Rva005EEFD2::operator=(const Rva005EEFD2 &other)
{
	if (this != &other) {
		if (other.m_ptr)
			++other.m_ptr->m_04.references;
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_04);
		m_ptr = other.m_ptr;
	}
	return *this;
}
