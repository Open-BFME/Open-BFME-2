// cl: /O1 /DNDEBUG /MD /GX
// ??1FlammableUpdate@@UAE@XZ @0x0048C724 77B
// Dtor restores four vptrs (+0 +0xC +0x10 +0x20) then calls rowed stopBurningSound at 0x0048C55E and pinned base ??1UpdateModule at 0x0024A797; DamageModuleInterface trivial so no call; vtable values DIR32 auto-patches. Model follows PoisonedBehaviorDtor.
class Thing;
class ModuleData;
class Object;
class DamageInfo;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
};

class FlammableUpdate : public UpdateModule, public DamageModuleInterface
{
public:
	virtual ~FlammableUpdate();

protected:
	void stopBurningSound();

private:
	int m_status;
	unsigned int m_aflameEndFrame;
	unsigned int m_burnedEndFrame;
	unsigned int m_damageEndFrame;
	void *m_audioHandle;
};

FlammableUpdate::~FlammableUpdate()
{
	stopBurningSound();
}
