// cl: /O1 /DNDEBUG /MD /GX
//
// ??0ObjectRecoveryHelper@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0028C9F9, 84 bytes.
// ObjectRecoveryHelper behavior ctor over the rowed ObjectHelper base
// (0x28C8DF, thing plus data): re-stores the three most-derived vtable slots
// then setWakeFrame(m_object, UPDATE_SLEEP_FOREVER) via the 0x44DF71 pin
// (address-of TU-local dummies, DIR32-masked; EH frametry via the
// declared-only base dtor, store-then-wake source order for the hoist).
// BFME1 donor is ObjectRecoveryHelperCtor.cpp; BFME2 keeps the shape. The
// rowed factory 0x29955B (news 0x20, no new members) is the sole raw caller,
// and the ObjectRecoveryHelper pool key at 0x28CA4D immediately follows. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// Opaque UpdateModule base; setWakeFrame resolves to its pin, m_object at +8.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);

	const void *m_vtable;
	int m_pad04;
	Object *m_object;
};

// Opaque ObjectHelper base (0x20 bytes); 2-arg ctor resolves to its row, the
// declared-only dtor arms the EH frame with no emitted code.
class ObjectHelper : public UpdateModule
{
public:
	ObjectHelper(Thing *thing, const ModuleData *moduleData);
	~ObjectHelper();

protected:
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_tailPad[0x20 - 0x14];
};

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

class ObjectRecoveryHelper : public ObjectHelper
{
public:
	ObjectRecoveryHelper(Thing *thing, const ModuleData *moduleData);
};

// ??0ObjectRecoveryHelper@@QAE@PAVThing@@PBVModuleData@@@Z @0x28C9F9
ObjectRecoveryHelper::ObjectRecoveryHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
