// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
//
// ??1MonitorConditionUpdate@@UAE@XZ, retail 0x004916AC, 73 bytes.
// MonitorConditionUpdate behavior dtor: compiler MI machinery restores the
// primary vtable 0x0084DAD8 plus the +0x0C/+0x10 secondary slots
// (0x007EFF90/0x0084DACC, DIR32-masked), then tears down the
// StringBase<char> at +0x20 through the pinned 0x36410 body, then the
// UpdateModule base through the rowed 0x24A797 body (twin pin for
// ??1UpdateModule). Layout from the rowed ctor 0x00491633 (same three
// stores plus and-[+0x20]-0) joined to UpdateModuleCtor.cpp MI hierarchy.
// Caller is the slot-0 ??_G at 0x00491750.

class Thing;
class ModuleData;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
template<int N> class BitFlags;

// The canonical frozen StringBase replaces the private copy; its switch
// declares the narrow teardown out of line, rowed at 0x00036410.
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

// The primary table starts with the deleting destructor: retail table
// RVA 0x0084DAD8 slot 0 is the owned callback 0x00491750. Inheriting an
// unrelated virtual here shifted the destructor into slot 1 and emitted
// a wrong first virtual slot. The deleting-wrapper unit uses these same
// base views, including the native three-entry update interface.
class BehaviorModuleBase
{
public:
	virtual ~BehaviorModuleBase();
private:
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual BitFlags<11> getDisabledTypesToProcess() const = 0;
	virtual void rva0044DF8D(UpdateSleepTime sleep) = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual BitFlags<11> getDisabledTypesToProcess() const;
	virtual void rva0044DF8D(UpdateSleepTime sleep);
};

class MonitorConditionUpdate : public UpdateModule
{
public:
	MonitorConditionUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~MonitorConditionUpdate();
	virtual UpdateSleepTime update();

private:
	StringBase<char> m_str; // +0x20
};

MonitorConditionUpdate::~MonitorConditionUpdate()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
