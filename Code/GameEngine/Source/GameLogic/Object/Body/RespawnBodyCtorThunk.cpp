// cl: /O1 /DNDEBUG /MD /EHsc

// Open-BFME5: RespawnBody module ctor.
// Out-of-line base MI, then three most-derived vtbls at +0/+0xC/+0x10.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


#include "../../../../Include/GameLogic/Module/BodyModule.h"

class ActiveBody : public BehaviorModule, public BodyModuleInterface
{
public:
	ActiveBody(Thing *thing, const ModuleData *moduleData);
	virtual ~ActiveBody();
};

class RespawnBody : public ActiveBody
{
public:
	RespawnBody(Thing *thing, const ModuleData *moduleData);
	virtual ~RespawnBody();
public:
	// retail slot 4: the rowed ?getModuleNameKey@RespawnBody@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0RespawnBody@@QAE@PAVThing@@PBVModuleData@@@Z
RespawnBody::RespawnBody(Thing *thing, const ModuleData *moduleData)
	: ActiveBody(thing, moduleData)
{
}

// ??1RespawnBody@@UAE@XZ present-unmatched
RespawnBody::~RespawnBody()
{
}
