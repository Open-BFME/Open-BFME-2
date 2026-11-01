// cl: /DNDEBUG /MD
//
// ?rva0026295E@AIUpdateInterface@@QAEXXZ, retail 0x0026295E, 15 bytes.
// Sibling clearer in the AIUpdateInterface +0x134/+0x3BF cluster beside
// 0x0026293E: zeroes the int at +0x134 via the /O1 and-idiom then clears the
// byte at +0x3BF. Layout follows the landed wakeUpNow 0x00262871 (+0x3C2)
// and setQueue 0x0026282A (+0x17C) TUs with m_turretAI at +0x20C bounding the
// tail. Leaf with no callees.

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::rva0026295E()
{
	m_waypointCount = 0;
	m_field3BF = false;
}
