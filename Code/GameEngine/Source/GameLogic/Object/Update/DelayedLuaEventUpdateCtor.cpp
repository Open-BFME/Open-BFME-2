// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0DelayedLuaEventUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A8E7B,
// 116 bytes. DelayedLuaEventUpdate behavior ctor over the rowed UpdateModule
// base (0x253390, thing plus data). Substantial BFME1 reconstruction from the
// DelayedLuaEventUpdateConstructor.cpp donor: the TU-local UpdateModule
// models the donor's multiple inheritance (primary plus two interface words,
// padded to the rowed 0x20 size) so the derived vtable group lands at
// ([esi], +0x0C, +0x10) ahead of the init-list member; the DelayedLuaEventList
// member at +0x24 resolves to its row (0xB6D8B); the body parks the module at
// FOREVER via setWakeFrame, then zeroes +0x20/+0x70/+0x74/+0x75.
//
// Two documented deviations from the donor, both codegen-neutral for this
// body: m_f70 is float here (retail stores it with movss; the donor spells
// uint), and setWakeFrame spells the rowed UpdateModule member resolving to
// the 0x44DF71 pin. Vtable immediates are DIR32-masked.
//
// Identity: the rowed instance factory 0x24F109 is the sole raw caller
// (ModuleFactory registration literal); the name getter at 0x4A8D93, the pool
// key at 0x4A8D99 and the ModuleData pair prove the class; the +0x24 member
// is the rowed DelayedLuaEventList. The MinefieldBehavior pin at this address
// is a wrong guess (that class has no literal, factory or rows in this
// image). Row supersedes the DelayedLuaEventUpdate pin.
class Thing;
class ModuleData;
class Object;

// Primary base chain of the rowed UpdateModule: vptr plus module data plus
// object (0x0C) with the two interface words following (donor layout,
// padded with ints to the rowed 0x20 size).
class UpdateModuleBase
{
public:
	UpdateModuleBase(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModuleBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class UpdateModuleInterface1
{
public:
	virtual void slot1() = 0;
};

class UpdateModuleInterface2
{
public:
	virtual void slot2() = 0;
};

class UpdateModule : public UpdateModuleBase,
		     public UpdateModuleInterface1,
		     public UpdateModuleInterface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, unsigned int frame);

	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class DelayedLuaEventList
{
public:
	DelayedLuaEventList();
	~DelayedLuaEventList();

private:
	unsigned char m_data[0x4C];
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData);

private:
	unsigned int m_f20;
	DelayedLuaEventList m_events;
	float m_f70;
	bool m_f74;
	bool m_f75;
};

// ??0DelayedLuaEventUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4A8E7B
DelayedLuaEventUpdate::DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), m_events()
{
	setWakeFrame(m_object, 0x3FFFFFFF);
	m_f20 = 0;
	m_f70 = 0.0f;
	m_f74 = false;
	m_f75 = false;
}
