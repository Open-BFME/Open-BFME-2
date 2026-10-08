// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

#include "ascii_string.h"

// Open-BFME5: CommandSetUpgrade module ctor via UpgradeModule multi-inheritance.

class Thing;
class ModuleData;
class Object;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void m01() = 0;
	virtual void m02() = 0;
	virtual void m03() = 0;
	virtual void m04() = 0;
	virtual void m05() = 0;
	virtual void m06() = 0;
	virtual void m07() = 0;

protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;

private:
	bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
public:
	UpgradeModule( Thing *thing, const ModuleData *moduleData );
	void rva004CE4A8();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CommandSetUpgrade.h
class CommandSetUpgrade : public UpgradeModule
{
public:
	CommandSetUpgrade( Thing *thing, const ModuleData *moduleData );

protected:
	virtual void upgradeRemovalImplementation();
};

// ??0CommandSetUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
CommandSetUpgrade::CommandSetUpgrade(
	Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}

// Target identity is established by the CommandSetUpgrade constructor at
// 0x004B3AB2: it installs the UpgradeMux vtable at VA 0x00C57248, whose slot 8
// at 0x00C57268 points to retail RVA 0x004B3B88. The target compares the
// module-data string at +0x118 with the Object string at +0x420; on equality it
// clears the override, marks TheControlBar dirty, removes the UpgradeModule
// condition, then clears the executed flag. BFME 1 declares a same-purpose Object setter by value. This target passes
// an existing AsciiString directly, so this view uses a const-reference ABI;
// the exact BFME 2 method-name correspondence remains an inference.
class CommandSetUpgradeModuleDataView
{
private:
	unsigned char m_pad000[0x118];

public:
	AsciiString m_commandSet;
};

class Object
{
public:
	void setCommandSetStringOverride(const AsciiString &commandSet);

	// Target access at Object +0x420; preceding bytes are opaque in this view.
	unsigned char m_pad000[0x420];
	AsciiString m_commandSet;
};

class ControlBar
{
public:
	unsigned char m_pad000[0x28];
	Bool m_28;
};

extern ControlBar *TheControlBar;

void CommandSetUpgrade::upgradeRemovalImplementation()
{
	if (isAlreadyUpgraded())
	{
		rva004CE4A8();
		const CommandSetUpgradeModuleDataView *data = (const CommandSetUpgradeModuleDataView *)m_moduleData;
		Object *object = m_object;
		if (object->m_commandSet.compare(data->m_commandSet) == 0)
		{
			AsciiString empty("");
			object->setCommandSetStringOverride(empty);
		}
		TheControlBar->m_28 = true;
		setUpgradeExecuted(false);
	}
}
