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

class Object
{
public:
	void doCommandButton(const CommandButton *button, int a2, bool a3);
};

#include "../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

struct DoCommandUpgradeModuleData
{
	unsigned char m_pad000[0x118];
	unsigned char m_118[4]; // +0x118 (AsciiString)
	unsigned char m_11C[4]; // +0x11C (AsciiString)
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class UpgradeMux
{
public:
	virtual void gap0() = 0; virtual void gap1() = 0; virtual void gap2() = 0; virtual void gap3() = 0;
	virtual void gap4() = 0; virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0;
	virtual void upgradeRemovalImplementation() = 0;
	virtual void gap9() = 0;
	virtual void upgradeImplementation() = 0;
};

class UpgradeModule : public BehaviorModule, public UpgradeMux
{
};

class DoCommandUpgrade : public UpgradeModule
{
public:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};

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
