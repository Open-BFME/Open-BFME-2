// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeAIUpdate module ctor.
// Out-of-line base MI, then five most-derived vtbls at
// +0/+0xC/+0x10/+0x20/+0x24.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../../Include/GameLogic/Module/BehaviorModule.h"


class SiegeAIUpdateIface2
{
public:
	virtual void siegeAIUpdateIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class SiegeAIUpdateIface3
{
public:
	virtual void siegeAIUpdateIface3Anchor();
};

class SiegeAIUpdateIface4
{
public:
	virtual void siegeAIUpdateIface4Anchor();
};

class AIUpdateInterface : public BehaviorModule, public SiegeAIUpdateIface2, public SiegeAIUpdateIface3, public SiegeAIUpdateIface4
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~AIUpdateInterface();
};

class SiegeAIUpdate : public AIUpdateInterface
{
public:
	SiegeAIUpdate(Thing *thing, const ModuleData *moduleData);
public:
	virtual ~SiegeAIUpdate();
public:
	// retail slot 4: the rowed ?getModuleNameKey@SiegeAIUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0SiegeAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SiegeAIUpdate::SiegeAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData)
{
}

