// cl: /DNDEBUG /MD /EHsc
//
// ?loadPostProcess@AudioLoopUpgrade@@MAEXXZ, retail 0x004B7BAA, 17 bytes.
// Slot 1 (offset 0x4) of vtable 0x00858CC4 (class of rowed dtor
// ??1AudioLoopUpgrade@@MAE@XZ at 0x004B7B20 in AudioLoopUpgradeDtor.cpp;
// also slot 1 of 0x0083FCDC/0x0084965C/0x0084A034 via ICF fold).
// Calls the pinned UpdateModule base loadPostProcess at 0x0058B03E first,
// then tail-jumps to the rowed wide StringBase validate at 0x000B3FD0 on
// the +0x20 member (retail lea ecx,[esi+0x20]). Layout follows UpdateModule
// base size 0x20 plus wide string at +0x20; identity is slot 1 of the own
// vtable 0x00858CC4 with AudioLoopUpgrade neighbours (prev 0x004B7B87
// AudioLoopUpgradeUpdate.cpp, next 0x004B7BBB AudioLoopUpgradePoolKey.cpp).
// Shape follows SpawnBehavior::loadPostProcess at 0x0045F382 (17B base call
// plus validate tail-jmp).

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

class AudioLoopUpgrade;

template <typename T>
class StringBase
{
	friend class AudioLoopUpgrade;
	void validate() const;
};

class AudioLoopUpgrade : public UpdateModule
{
protected:
	virtual void loadPostProcess();

private:
	StringBase<unsigned short> m_str20; // +0x20 retail validate target
};

void AudioLoopUpgrade::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	m_str20.validate();
}
