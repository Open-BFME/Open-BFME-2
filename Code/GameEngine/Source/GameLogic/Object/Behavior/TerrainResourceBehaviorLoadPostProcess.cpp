// cl: /MD
//
// ?loadPostProcess@TerrainResourceBehavior@@MAEXXZ, retail 0x0048223D, 28 bytes.
// Slot 1 (offset 0x04) of vtable 0x00849408 (class of rowed dtor
// ??1Rva00481F82@@UAE@XZ; same primary as rowed ctor 0x0048209B and rowed xfer
// 0x004821CB in TerrainResourceBehaviorXfer.cpp). Base loadPostProcess via
// pinned 0x0058B03E first, then conditional setWakeFrame via rowed 0x0044DF71
// when +0x28 is false. Layout is UpdateModule base 0x20 plus pointers at
// +0x20/+0x24 plus bools plus float, matching the rowed ctor/xfer shape.

class Thing;
class ModuleData;
class Object;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Thing;
class ModuleData;
class Object;
class TerrainResourceBehaviorModuleData;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

// The module data is +0x04, the object is +0x08 and the update interface is +0x10.
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
	__forceinline void wakeNativeObject(Object *object)
	{
		setWakeFrame(object, UPDATE_SLEEP_NONE);
	}
protected:
	virtual void loadPostProcess();
	void setWakeFrame(Object *object, UpdateSleepTime delay);
	const TerrainResourceBehaviorModuleData *getTerrainResourceBehaviorModuleData() const
	{
		return reinterpret_cast<const TerrainResourceBehaviorModuleData *>(m_moduleData);
	}
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class TRB_Iface3 { public: virtual void slot3(); };
class TRB_Iface4 { public: virtual void slot4(); };

class TerrainResourceBehavior : public UpdateModule, public TRB_Iface3, public TRB_Iface4
{
public:
	TerrainResourceBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~TerrainResourceBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	bool m_registered; // +0x28
	bool m_sleepAfterRegister; // +0x29
	float m_incomeScale; // +0x2C
};

void TerrainResourceBehavior::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	if (!m_registered) {
		setWakeFrame(m_object, UPDATE_SLEEP_NONE);
	}
}
