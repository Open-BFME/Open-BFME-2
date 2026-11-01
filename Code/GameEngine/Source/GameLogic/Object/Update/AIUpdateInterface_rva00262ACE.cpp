// cl: /DNDEBUG /MD
//
// ?rva00262ACE@AIUpdateInterface@@QAEXXZ, retail 0x00262ACE, 28 bytes.
// Sibling multi-field setter in the AIUpdateInterface +0x3B6 cluster beside
// 0x00262AEA: clears the byte at +0x3B6 and the dword at +0x16C and the byte
// at +0x3B8 while setting the byte at +0x3B7. Layout follows the landed
// wakeUpNow (+0x3C2) and 0x134-cluster TUs. Leaf with no callees.

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::rva00262ACE()
{
	m_field3B6 = false;
	m_field3B7 = true;
	m_blockedFrames = 0;
	m_field3B8 = false;
}
