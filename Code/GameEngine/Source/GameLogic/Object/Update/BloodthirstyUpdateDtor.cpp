// cl: /DNDEBUG /MD /GX
//
// ??1BloodthirstyUpdate@@MAE@XZ, retail 0x0044DFE0, 32 bytes. Destructor for
// BloodthirstyUpdate (ctor rowed at 0x0044E0AA in BloodthirstyUpdateCtor.cpp,
// vtable 0x0083F0B4 with slot 0 ??_G at 0x0044E113).
//
// The body restores the four vtable pointers of the complete object -- the
// derived slot at +0x00 plus the secondary slots at +0x0C/+0x10/+0x20 -- then
// tail-jumps to the UpdateModule base destructor (pinned ??1UpdateModule@@UAE@XZ
// at 0x0024A797). Recipe: InvisibilityUpdateDtor.cpp / PoisonedBehaviorDtor.cpp.

class Thing;
class ModuleData;
class Object;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


enum CommandSourceType
{
	CMD_FROM_AI = 2
};

// The +0x20 interface's vftable 0x00C3EFC4 opens with sacrificeHorde (0x0044E374).
class BloodthirstyUpdateIface
{
public:
	virtual void sacrificeHorde(Object *victim, CommandSourceType source) = 0;
};

class BloodthirstyUpdate : public UpdateModule, public BloodthirstyUpdateIface
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	virtual void sacrificeHorde(Object *victim, CommandSourceType source);
protected:
	virtual ~BloodthirstyUpdate();
public:
	// retail slot 4: the rowed ?getModuleNameKey@BloodthirstyUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
};

// Primary slot 1, retail 0x00497805 (`jmp 0x0058B03E`): the UpdateModule base call that
// every module-family override without work of its own shares (ICF).
void BloodthirstyUpdate::loadPostProcess()
{
	UpdateModule::loadPostProcess();
}

BloodthirstyUpdate::~BloodthirstyUpdate()
{
}
