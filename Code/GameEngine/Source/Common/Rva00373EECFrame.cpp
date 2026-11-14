// cl: /DNDEBUG /MD
//
// ?rva00373EEC@StealthUpdate@@QAEXI@Z @0x00373EEC 48B:
// Frame-horizon max store: holder at +0x04 (value at +0x08), stored frame at
// +0x24, base frame from TheGameLogic+0x40 (rowed extern
// ?TheGameLogic@@3PAVGameLogic@@A). Zero arg overwrites, nonzero keeps the
// max (unsigned cmp jae). Callers at 0x003747FF plus 0x00375730.
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

struct Rva00373EECSub
{
	char m_pad[8];
	unsigned int m_8;
};

#include "../../Include/GameLogic/Module/StealthUpdate.h"

void StealthUpdate::rva00373EEC(unsigned int v)
{
	if (m_moduleData == 0)
		return;
	unsigned int base = TheGameLogic->getFrame();
	if (v == 0)
		m_detectionExpiresFrame = ((Rva00373EECSub *)m_moduleData)->m_8 + base;
	else {
		unsigned int nv = base + v;
		if (m_detectionExpiresFrame < nv)
			m_detectionExpiresFrame = nv;
	}
}
