// cl: /DNDEBUG /MD
//
// ?rva00262AEA@AIUpdateInterface@@QAEXXZ, retail 0x00262AEA, 15 bytes.
// Sibling two-field setter in the AIUpdateInterface +0x3B6 cluster beside
// 0x00262ACE: sets the byte at +0x3B6 while clearing the byte at +0x3B7.
// Layout follows the landed wakeUpNow (+0x3C2) and 0x134-cluster TUs. Leaf
// with no callees and twelve callers including the 0x00471ECC path.

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::rva00262AEA()
{
	m_field3B6 = true;
	m_field3B7 = false;
}
