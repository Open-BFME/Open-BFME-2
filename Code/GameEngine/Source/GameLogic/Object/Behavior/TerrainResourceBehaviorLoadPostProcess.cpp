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

class BehaviorModuleBase
{
public:
	virtual void unused();
	const ModuleData *m_moduleData;
	Object *m_object;
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
	virtual void update() = 0;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void loadPostProcess();
	void setWakeFrame(Object *object, UpdateSleepTime frame);
};

class TerrainResourceBehavior : public UpdateModule
{
protected:
	virtual void loadPostProcess();

private:
	const void *m_20;
	const void *m_24;
	bool m_28;
	bool m_29;
	float m_2C;
};

void TerrainResourceBehavior::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	if (!m_28) {
		setWakeFrame(m_object, UPDATE_SLEEP_NONE);
	}
}
