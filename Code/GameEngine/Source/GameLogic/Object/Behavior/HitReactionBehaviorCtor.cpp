// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0HitReactionBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00459228,
// 93 bytes. Behavior-side ctor completing the HitReactionBehavior file-unit
// (ModuleData proc/factory/ctor rowed at 0x459217/0x24AE4A/0x4591EA,
// instance factory rowed at 0x24AE12 with this pinned 2-arg ctor as its
// sole raw caller).
//
// Shape follows the rowed RampageBehavior/EnragedBehavior ctors: UpdateModule
// base call, hoisted float-zero plus call setups, compiler vtable store, the
// re-stored +0x0C/+0x10 secondary slots, int zero, float store, then the
// setWakeFrame tail call via the rowed UpdateModule base and pinned 0x44DF71.
// Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque UpdateModule base; ctor resolves to its row. The declared-only
// virtual dtor drives the single EH state with zero emitted code. Protected
// slots mirror the retail stores.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, unsigned int frame);

	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class HitReactionBehavior : public UpdateModule
{
public:
	HitReactionBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~HitReactionBehavior();

private:
	int m_20;
	float m_24;
};

// ??0HitReactionBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00459228
HitReactionBehavior::HitReactionBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_20 = 0;
	m_24 = 0.0f;
	setWakeFrame(m_object, 1);
}
