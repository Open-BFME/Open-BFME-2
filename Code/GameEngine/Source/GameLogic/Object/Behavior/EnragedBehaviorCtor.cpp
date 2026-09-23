// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0EnragedBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00458FA3,
// 89 bytes. Behavior-side ctor completing the EnragedBehavior file-unit
// (poolkey rowed at 0x459002, ModuleData factory rowed at 0x24ADC1,
// instance factory rowed at 0x24AD89 with this pinned 2-arg ctor as its
// sole raw caller).
//
// Shape follows the rowed RampageBehavior ctor (0x458B60): UpdateModule
// base call, hoisted float-zero plus call setups, compiler vtable store,
// the re-stored +0x0C/+0x10 secondary slots, float store, then the
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

class EnragedBehavior : public UpdateModule
{
public:
	EnragedBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~EnragedBehavior();

private:
	float m_20;
};

// ??0EnragedBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00458FA3
EnragedBehavior::EnragedBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_20 = 0.0f;
	setWakeFrame(m_object, 1);
}
