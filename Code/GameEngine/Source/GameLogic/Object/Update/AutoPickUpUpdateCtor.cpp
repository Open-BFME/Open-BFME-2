// cl: /DNDEBUG /MD /GX
//
// ??0AutoPickUpUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00495D31,
// 121 bytes. Behavior-side ctor (rowed instance factory 0x24E061 news
// 0x2C with this pinned 2-arg ctor as its sole raw caller at 0x24E088).
//
// Shape follows the AutoHealBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20 slot via sourced-before address-take, the
// module data pointer homed in eax with an ecx-homed int zero (sequential
// lifetimes keep pressure low), early __FILE__-literal pushes, the three
// derived vtable installs, zeros at +0x24/+0x28/+0x29, and a
// GetGameLogicRandomValue accumulation into +0x24 (rowed int twin
// 0x233FF4 over lo/hi/file/line with the TU __FILE__ literal and line
// 0x83). Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;
class Xfer;
enum NameKeyType;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
typedef int Int;
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, int line);
struct AutoPickUpUpdateModuleData
{
	char m_pad00[8];
	int m_scanDelayTime;
	char m_pad0C[4];
	float m_scanDistance;
};

#include "../../../../Include/Common/ObjectModule.h"

// BehaviorModuleBase vftable 0x00C4F06C.
class BehaviorModule : public ObjectModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
};

// BehaviorModuleOther vftable 0x00C4EFB0.
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// UpdateModule vftable 0x00C4EFA0.
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

// Folded base vftable 0x00C4EF80 (7 classes), named GhostObject in the data ledger.
class AutoPickUpUpdateInterface
{
public:
	virtual void anchor() = 0;
	virtual void slot1() = 0;
	virtual void rva00495C6E() = 0;
};

// AutoPickUpUpdateInterface vftable 0x00C4EF90.
class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateInterface
{
public:
	AutoPickUpUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AutoPickUpUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void rva00495C6E();
	virtual UpdateSleepTime update();
	bool rva00495DD4();__forceinline float getScanRange()const{return getAutoPickUpUpdateModuleData()->m_scanDistance;}

	const AutoPickUpUpdateModuleData *getAutoPickUpUpdateModuleData() const
	{
		return (const AutoPickUpUpdateModuleData *)m_moduleData;
	}
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_count24;
	bool m_flag28;
	bool m_flag29;
};

// ??0AutoPickUpUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00495D31
AutoPickUpUpdate::AutoPickUpUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const AutoPickUpUpdateModuleData *data = getAutoPickUpUpdateModuleData();
	int zero = 0;
	m_count24 = zero;
	m_flag28 = zero;
	m_flag29 = zero;
	m_count24 += GetGameLogicRandomValue(0, data->m_scanDelayTime, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AutoPickUpUpdate.cpp", 0x83);
}
