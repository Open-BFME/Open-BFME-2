// cl: /O1 /DNDEBUG /MD /GX
//
// ??0HordeAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0049A7F3,
// 113 bytes. Behavior-side ctor completing the HordeAIUpdate file-unit
// (behavior instance factory rowed at 0x24E525 news 0x444 with this pinned
// 2-arg ctor as its caller at 0x24E54F; poolkey rowed at 0x49A67C; name
// getter rowed at 0x49A6C1).
//
// Shape follows AssaultTransport precedent over the same pinned opaque
// Transport base 0x26E9BD (thing plus data): volatile-first double store
// at +0x3E4 (C52EE8-then-C50868) plus the five behavior vtable slots
// (+0x00/+0x0C/+0x10/+0x20/+0x24 via explicit members) plus setWakeFrame
// awake-through-none tail. The class declares no virtuals of its own: the
// stores land from explicit members in body order with the setWakeFrame
// push/mov-ecx setup hoisted above them by the scheduler (WallUpgrade
// scheduling notes). /GX for the EH prologue plus the single mid-body
// state store; the defined-empty base dtor arms it while resolving its own
// unwind reference in-TU (PrisonDock precedent: a defined base dtor is what
// the linker needs). The pinned HordeWorkerAIUpdate ctor at 0x49AD15 calls
// this body at base position (Transport-pattern shared base, GarrisonContain
// precedent); this row documents the HordeAIUpdate side of the share. Zero
// other new pins (base ctor resolves via the existing Rva0026E9BDBase pin;
// setWakeFrame resolves via the new Rva0026E9BDBase-spelling alias pin at
// 0x44DF71 placed alongside).

class Thing;
class ModuleData;
class Object;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Rva0026E9BDBase
{
public:
	Rva0026E9BDBase(Thing *thing, const ModuleData *moduleData);
	~Rva0026E9BDBase() { m_p3E4 = 0; }

protected:
	void setWakeFrame(Object *object, unsigned int frame);

	const void *m_vtable;			// +0x00
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;			// +0x08
	const void *m_p0C;			// +0x0C
	const void *m_p10;			// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;			// +0x20
	const void *m_p24;			// +0x24
	unsigned char m_pad28[0x3E4 - 0x28];
	const void *m_p3E4;			// +0x3E4
};

class HordeAIUpdate : public Rva0026E9BDBase
{
public:
	HordeAIUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0HordeAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0049A7F3
HordeAIUpdate::HordeAIUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0026E9BDBase(thing, moduleData)
{
	*(const void * volatile *)&m_p3E4 = (const void *)0x00C52EE8;
	_ReadWriteBarrier();
	m_vtable = (const void *)0x00C505F8;
	m_p0C = (const void *)0x00C50538;
	m_p10 = (const void *)0x00C5052C;
	m_p20 = (const void *)0x00C50528;
	m_p24 = (const void *)0x00C52F88;
	m_p3E4 = (const void *)0x00C50868;
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
