// ??0StrafeAreaUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.47 date=2026-09-23
// ??0StrafeAreaUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.92 date=2026-09-23
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0StrafeAreaUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x003A4D23,
// 129 bytes. StrafeArea behavior over the rowed UpdateModule base
// (0x00253390, thing plus data): redo stores plus setWakeFrame(getObject(),
// UPDATE_SLEEP_NONE) via the 0x44DF71 pin, then the three most-derived
// table slots (literals, DIR32-masked). The ModuleData side is fully
// rowed (proc 0x003A4D12, ctor 0x003A4E5A, factory 0x0024D737, poolkey
// 0x003A4CCD); the instance factory at 0x0024D6FF news 0x48 and calls
// this ctor as sole caller. Shape follows ObjectHelperCtor (opaque
// UpdateModule base with inline getObject at +8, explicit vtable so body
// order is source order, protected enum-typed setWakeFrame). No BFME1
// donor names the behavior members, so the seven float slots and the
// int/byte slots keep positional names.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// Opaque UpdateModule base; 2-arg ctor resolves to its row. Empty here
// (EBO contributes no size) so the derived class carries the full layout
// and every store can sit in the mem-init in source order; m_object sits
// at +8 per the rowed getObject users.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
};

class StrafeAreaUpdate : public UpdateModule
{
public:
	StrafeAreaUpdate(Thing *thing, const ModuleData *moduleData);

private:
	Object *getObject() const { return m_object; }

	const void *m_vtable; // +0
	int m_pad04; // +4
	Object *m_object; // +8
	const void *m_table0C; // +0x0C, shared secondary table
	const void *m_table10; // +0x10
	unsigned char m_reserved14[12]; // +0x14..+0x1F, unstored by the ctor
	float m_float20; // +0x20
	float m_float24; // +0x24
	float m_float28; // +0x28
	float m_float2C; // +0x2C
	float m_float30; // +0x30
	float m_float34; // +0x34
	float m_float38; // +0x38
	int m_int3C; // +0x3C
	unsigned char m_byte40; // +0x40
	int m_int44; // +0x44
};

// ??0StrafeAreaUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x3A4D23
StrafeAreaUpdate::StrafeAreaUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	// Store order below is the retail order (not layout order); the zero
	// stores schedule freely and the compiler grouped them this way.
	m_vtable = reinterpret_cast<const void *>(0x00C1B164);
	m_table0C = reinterpret_cast<const void *>(0x00BEFF90);
	m_table10 = reinterpret_cast<const void *>(0x00C1B158);
	m_float38 = 0.0f;
	m_int3C = 0;
	m_byte40 = 0;
	m_int44 = 0;
	m_float28 = 0.0f;
	m_float24 = 0.0f;
	m_float20 = 0.0f;
	m_float34 = 0.0f;
	m_float30 = 0.0f;
	m_float2C = 0.0f;
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
