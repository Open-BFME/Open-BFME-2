// cl: /DNDEBUG /MD
//
// ?rva00262FFF@AIUpdateInterface@@QAEXXZ, retail 0x00262FFF, 38 bytes.
// AIUpdateInterface tail sibling of rva00263025 (same +0x21C/+0x3BC and
// TheGameLogic 0x00DFE78C): call virtual slot 0x1B8; if false return; else
// load TheGameLogic+0x40 into +0x21C and set +0x3BC to 1. Honest
// address-derived name; slot identity unproven. No other callees.

extern class GameLogic *TheGameLogic;

struct GameLogicFrame
{
	char m_pad00[0x40];
	unsigned int m_frame;
};

#define TheGameLogic (*(GameLogicFrame **)&TheGameLogic)

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::rva00262FFF()
{
	if (!isIdle())
		return;
	m_field21C = TheGameLogic->m_frame;
	m_field3BC = 1;
}
