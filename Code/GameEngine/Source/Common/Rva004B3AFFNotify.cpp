// cl: /O1 /DNDEBUG /MD
//
// ?upgradeImplementation@Rva004B3AFF@@QAEXXZ @0x004B3AFF 67B.
// Run the upgrade hook at this-0x10, push the AsciiString at +0x118 of
// the object at this-0xC onto the Object at this-8, tell the skirmish
// manager about that object twice, and mark TheControlBar +0x28.

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../GameLogic/Object/object.h"

class UpgradeModule
{
public:
	void rva004CE4A0();
};

#include "../../Include/GameLogic/Rva002A8F24.h"

class StringHolder
{
public:
	char m_pad[0x118];
	AsciiString m_name;
};

#include "../../Include/GameClient/ControlBar.h"

extern Rva002A8F24 *TheSkirmishAIManager;
extern ControlBar *TheControlBar;

class Rva004B3AFF
{
public:
	void upgradeImplementation();
};

void Rva004B3AFF::upgradeImplementation()
{
	((UpgradeModule *)((char *)this - 0x10))->rva004CE4A0();
	StringHolder *holder = *(StringHolder **)((char *)this - 0x0C);
	Object *obj = *(Object **)((char *)this - 8);
	obj->setCommandSetStringOverride(holder->m_name);
	TheSkirmishAIManager->UnRegister(obj);
	TheSkirmishAIManager->rva002A9365(obj);
	TheControlBar->field28 = 1;
}
