// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?loadPostProcess@SpawnBehavior@@MAEXXZ, retail 0x0045F382, 17 bytes.
// Slot 1 (offset 0x4) of vtable 0x008426AC (class of rowed dtor
// ??1SpawnBehavior@@UAE@XZ at 0x0045F6D3 in SpawnBehaviorDtor.cpp).
// Calls the pinned UpdateModule base loadPostProcess at 0x0058B03E first,
// then tail-jumps to the rowed wide StringBase validate at 0x000B3FD0 on
// the +0x30 member (retail lea ecx,[esi+0x30]). Layout follows the ctor at
// 0x0045F581 (UpdateModule base size 0x20, +0x30 UpgradeMux/string slot)
// and the ZH donor SpawnBehavior::loadPostProcess (base call). Identity is
// slot 1 of the own vtable 0xC426AC.

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
public:
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

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void loadPostProcess();
};

class SpawnBehavior;

template <typename T>
class StringBase
{
	friend class SpawnBehavior;
	void validate() const;
};

class SpawnBehavior : public UpdateModule
{
protected:
	virtual void loadPostProcess();

private:
	unsigned char m_pad20[0x10]; // +0x20..+0x2F secondary slots
	StringBase<unsigned short> m_str30; // +0x30 retail validate target
};

void SpawnBehavior::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	m_str30.validate();
}
