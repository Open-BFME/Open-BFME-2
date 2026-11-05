// cl: /DNDEBUG /MD /EHsc

class Thing;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
#include "../../../../Include/Common/ModuleData.h"

class CivilianSpawnUpdateModuleData : public ModuleData
{
public:
    unsigned int m_spawnDelay;
};

int __cdecl GetGameLogicRandomValue(int, int, char *, int);

enum UpdateSleepTime
{
    UPDATE_SLEEP_DUMMY
};

class PB_Iface1
{
public:
    virtual void slot();
};

class PB_Iface2
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class CivilianSpawnUpdate : public UpdateModule
{
public:
    CivilianSpawnUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_spawnFrame;
public:
	// retail slot 4: the rowed ?getModuleNameKey@CivilianSpawnUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
public:
	// retail vftable slot: the rowed override
	virtual UpdateSleepTime update();
};

// ??0CivilianSpawnUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
CivilianSpawnUpdate::CivilianSpawnUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_spawnFrame(0)
{
    m_spawnFrame = GetGameLogicRandomValue(
        static_cast<const CivilianSpawnUpdateModuleData *>(m_moduleData)->m_spawnDelay / 2,
        static_cast<const CivilianSpawnUpdateModuleData *>(m_moduleData)->m_spawnDelay,
        "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\CivilianSpawnUpdate.cpp",
        61);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot@PB_Iface1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot@PB_Iface2@@UAEXXZ=?update@CivilianSpawnUpdate@@UAE?AW4UpdateSleepTime@@XZ")
