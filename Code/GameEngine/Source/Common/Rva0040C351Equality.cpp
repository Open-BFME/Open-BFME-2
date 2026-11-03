// cl: /DNDEBUG /MD
// ?rva0040C3BB@ArmySummaryEntry@@QAE_NPBV1@@Z @0x0040C3BB (117B):
// ArmySummaryEntry equality: first the rowed base Equal at 0x0037E0EC over this
// and other, then the six tail fields at +0xB4 +0xB8 +0xBC +0xC0 +0xC4 +0xC5.
// Layout and // cl: from neighbours Rva0040C351Dtor.cpp (0x0040C39E) and
// Rva0040C351Ctor.cpp (0x0040C430). Unblocks 0x0040CB79. Evidence: single
// caller at 0x0040CB95, callee Equal rowed, ret 4 single pointer arg.
bool __cdecl Rva0037E0ECEqual(const void *a, const void *b);

#include "../../Include/GameLogic/CarryoverUnit.h"

struct MemberAC
{
	void *m_vtable;
	int m_04;
};

#include "../../Include/Common/ArmySummaryEntry.h"

bool ArmySummaryEntry::rva0040C3BB(const ArmySummaryEntry *other)
{
	return Rva0037E0ECEqual(this, other)
		&& m_c5 == other->m_c5
		&& m_b4 == other->m_b4
		&& m_b8 == other->m_b8
		&& m_bc == other->m_bc
		&& m_c0 == other->m_c0
		&& m_c4 == other->m_c4;
}
