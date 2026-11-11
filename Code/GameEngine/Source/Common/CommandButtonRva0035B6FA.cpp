// cl: /O1 /arch:SSE /G7 /MD /EHsc
// CommandButton identity and fields at +0x14, +0x1c, +0xfc are supported by adjacent CommandButton rows;
// arguments follow the call-site and callee shapes. The final findObjectByID/rva0035B5C2 call is written once per
// branch that reaches it: VC7.1 cross-jumps the identical tails, which is what gives retail its
// ECX-before-last-push call setup (a single shared tail swaps it). Pattern: BFME1 WeaponSet_releaseWeaponLock.cpp.
// ?rva0035B6FA@CommandButton@@QAEXW4ObjectID@@_N@Z @0x0035B6FA 86B
// ?rva0035B6FA@CommandButton@@QAEXW4ObjectID@@_N@Z, retail 0x0035B6FA (86 bytes).
// CommandButton identity and fields at +0x14, +0x1c, and +0xfc are supported by
// adjacent CommandButton rows; the two arguments follow the call-site and callee shapes.
#include "../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

#include "../../Include/GameClient/Rva0035B164.h"
#include "../../Include/GameClient/CommandButton.h"

void CommandButton::rva0035B6FA(ObjectID objectID, bool value)
{
	if (m_options & 0x00800000)
	{
		if (m_command != 0x23)
		{
			if (m_command == 0x30)
				rva0035B5C2(TheGameLogic->findObjectByID(objectID), value);
		}
		else
			fieldFC = reinterpret_cast<Rva0035B164 *>(this)->rva0035B164(objectID);
	}
	else if (m_options & 0x03000000)
		rva0035B5C2(TheGameLogic->findObjectByID(objectID), value);
}
