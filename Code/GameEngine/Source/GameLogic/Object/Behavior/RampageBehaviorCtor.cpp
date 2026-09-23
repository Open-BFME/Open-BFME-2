// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0RampageBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00458B60,
// 101 bytes. Behavior-side ctor completing the RampageBehavior file-unit
// (poolkey rowed at 0x458B0A, ModuleData proc/factory/ctor rowed at
// 0x458B4F/0x24AD38/0x458C0F, instance factory rowed at 0x24AD00 with news
// 0x2C and this pinned 2-arg ctor as its sole raw caller).
//
// Shape follows the rowed BoredUpdate ctor (0x496791): UpdateModule base
// call, hoisted float load plus call setups, compiler vtable store, the
// re-stored +0x0C/+0x10 secondary slots, int zeros, float store, then the
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

class RampageBehavior : public UpdateModule
{
public:
	RampageBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~RampageBehavior();

private:
	float m_20;
	int m_24;
	int m_28;
};

// ??0RampageBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00458B60
RampageBehavior::RampageBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_24 = 0;
	m_28 = 0;
	m_20 = 99999.0f;
	setWakeFrame(m_object, 1);
}
