// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ClearanceTestingSlowDeathBehavior module ctor (ICF 74B family).
// Base call, interim vtbl at +0x50, then most-derived vtbls at
// +0/+0xC/+0x10/+0x20/+0x24/+0x50.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


class ClearanceTestingSlowDeathBehaviorIface2
{
public:
	virtual void clearanceTestingSlowDeathBehaviorIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class ClearanceTestingSlowDeathBehaviorIface3
{
public:
	virtual void clearanceTestingSlowDeathBehaviorIface3Anchor();
};

class ClearanceTestingSlowDeathBehaviorIface4
{
public:
	virtual void clearanceTestingSlowDeathBehaviorIface4Anchor();

private:
	unsigned char m_pad[0x28];
};

class ClearanceTestingSlowDeathBehaviorIface5
{
public:
	virtual void clearanceTestingSlowDeathBehaviorIface5Anchor();
};

// The base is SlowDeathBehavior: the derived ctor 0x00483D39 calls the rowed
// ??0SlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z at 0x0045D4B4
// (Zero Hour: ClearanceTestingSlowDeathBehavior : public SlowDeathBehavior).
class SlowDeathBehavior : public BehaviorModule, public ClearanceTestingSlowDeathBehaviorIface2, public ClearanceTestingSlowDeathBehaviorIface3, public ClearanceTestingSlowDeathBehaviorIface4
{
public:
	SlowDeathBehavior(Thing *thing, const ModuleData *moduleData);
};

class ClearanceTestingSlowDeathBehavior : public SlowDeathBehavior,
	public ClearanceTestingSlowDeathBehaviorIface5
{
public:
	ClearanceTestingSlowDeathBehavior(Thing *thing, const ModuleData *moduleData);
public:
	virtual ~ClearanceTestingSlowDeathBehavior();
protected:
	// retail slot 3: the rowed ?xfer@ClearanceTestingSlowDeathBehavior@@MAEXPAVXfer@@@Z
	virtual void xfer(Xfer *xfer);
public:
	// retail slot 4: the rowed ?getModuleNameKey@ClearanceTestingSlowDeathBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0ClearanceTestingSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
ClearanceTestingSlowDeathBehavior::ClearanceTestingSlowDeathBehavior(Thing *thing, const ModuleData *moduleData)
	: SlowDeathBehavior(thing, moduleData)
{
}
