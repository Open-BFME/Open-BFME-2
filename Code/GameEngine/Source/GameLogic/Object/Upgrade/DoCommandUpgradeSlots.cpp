// cl: /DNDEBUG /MD
//
// Two DoCommandUpgrade overrides on the upgrade-mux vtable 0x00C57B10 that its
// matched ctor 0x004B4C2E installs at +0x10, compiled with that subobject
// this. Each looks a command button up by a name from the module data in
// TheControlBar and has our Object do it. Names are by address.
//
// ?upgradeRemovalImplementation@DoCommandUpgrade@@UAEXXZ, retail 0x004B4C7B, 50 bytes: slot 8,
// the button named at module data +0x11C.
// ?upgradeImplementation@DoCommandUpgrade@@UAEXXZ, retail 0x004B4CAD, 50 bytes: slot 10,
// the button named at module data +0x118.

class AsciiString;
class CommandButton;

#include "../object.h"

#include "../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

struct DoCommandUpgradeModuleData
{
	unsigned char m_pad000[0x118];
	unsigned char m_118[4]; // +0x118 (AsciiString)
	unsigned char m_11C[4]; // +0x11C (AsciiString)
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/DoCommandUpgrade.h"

// ?upgradeRemovalImplementation@DoCommandUpgrade@@UAEXXZ @0x004B4C7B
void DoCommandUpgrade::upgradeRemovalImplementation()
{
	Object *obj = m_object;
	if (obj && getModuleData())
	{
		const CommandButton *button = TheControlBar->findCommandButton(*(const AsciiString *)((const DoCommandUpgradeModuleData *)getModuleData())->m_11C);
		if (button)
			obj->doCommandButton(button, 0, 0);
	}
}

// ?upgradeImplementation@DoCommandUpgrade@@UAEXXZ @0x004B4CAD
void DoCommandUpgrade::upgradeImplementation()
{
	Object *obj = m_object;
	if (obj && getModuleData())
	{
		const CommandButton *button = TheControlBar->findCommandButton(*(const AsciiString *)((const DoCommandUpgradeModuleData *)getModuleData())->m_118);
		if (button)
			obj->doCommandButton(button, 0, 0);
	}
}
