// cl: /DNDEBUG /MD
//
// ?rva00262804@AIUpdateInterface@@QAEXE@Z, retail 0x00262804, 38 bytes.
// Sibling of wakeUpNow 0x00262871 and setQueueForPathTime 0x0026282A in the
// same AIUpdateInterface tail: stores the byte arg at +0x3B9 then when the
// int at +0x1F4 is 0 or 1 issues the virtual at slot 142 (offset 0x238) with
// 0. m_object-adjacent layout and the +0x3C2 guard in the landed siblings
// prove AIUpdateInterface.

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::rva00262804(unsigned char val)
{
	m_field3B9 = val;
	if (m_curLocomotorSet == 0 || m_curLocomotorSet == 1)
		chooseLocomotorSet(0);
}
