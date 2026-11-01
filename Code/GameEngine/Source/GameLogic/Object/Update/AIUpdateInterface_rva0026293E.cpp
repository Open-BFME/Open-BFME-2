// cl: /DNDEBUG /MD
//
// ?rva0026293E@AIUpdateInterface@@QAEXXZ, retail 0x0026293E, 32 bytes.
// Sibling conditional setter in the AIUpdateInterface +0x134 cluster beside
// clearer 0x0026295E: when the byte at +0x3BD is already zero and the int at
// +0x134 is positive zeroes the int at +0x138 and sets the byte at +0x3BF.
// Layout follows the landed wakeUpNow (+0x3C2) and setQueue (+0x17C) TUs.
// Leaf with no callees.

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::rva0026293E()
{
	if (m_field3BD == false && m_waypointCount > 0)
	{
		m_waypointIndex = 0;
		m_field3BF = true;
	}
}
