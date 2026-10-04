// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ??0MissileUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A75B9,
// 200 bytes. Behavior-side ctor completing the MissileUpdate file-unit
// (ModuleData proc/ctor/factory rowed at 0x4A74EF/0x4A77B8/0x24EFA0;
// behavior factory rowed at 0x24EF65 news 0xD0 with this pinned 2-arg
// ctor; poolkey rowed at 0x4A76C3).
//
// Shape: frameless single-base ctor over the pinned BezierProjectileBehavior
// base 0x45C850 (ModuleFactory literal, human-readable pin). The TU-local
// base carries the true member map: retail pushes the ctor args straight
// off the incoming stack (no homing) and reloads thing/moduleData from
// [ebx+4]/[ebx+8] afterwards, which only member declarations reproduce,
// and all five vtable installs (+0/+0xC/+0x10/+0x20/+0x24) are named
// member stores so the scheduler keeps source order (cast-stores sink
// below field stores and recolor the frame-load registers). No virtuals
// are declared anywhere so no vtable is emitted here; all vtable
// immediates are DIR32-masked in comparison. The GameLogic frame at +0x40
// lands in +0x8C via the TU-local GameLogic view (DeletionUpdate
// precedent). Thing+0xCC feeds +0x9C; the ModuleData +0x38 twelve-byte
// block copies into +0xAC as one struct assignment (unrolled movs triple);
// the +0xA0/+0xB8 triples zero as inline float stores (/arch:SSE movss,
// xorps hoisted). Factory news 0xD0 fits the +0xCE tail. Zero new pins
// (base resolves via the existing BezierProjectileBehavior pin;
// TheGameLogic is an absolute global).

extern "C" const void *const vtbl_00C53570[];  // folded, 2 classes; via ??_7BezierProjectileBehavior@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00C53570=??_7BezierProjectileBehavior@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00C53530[];  // ??_7MissileUpdate@@6BRva004A76DEBase4@@@
#pragma comment(linker, "/alternatename:_vtbl_00C53530=??_7MissileUpdate@@6BRva004A76DEBase4@@@")
extern "C" const void *const vtbl_00C53548[];  // ??_7MissileUpdate@@6BRva004A76DEBase3@@@
#pragma comment(linker, "/alternatename:_vtbl_00C53548=??_7MissileUpdate@@6BRva004A76DEBase3@@@")
extern "C" const void *const vtbl_00C53560[];  // ??_7MissileUpdate@@6BRva004A76DEBase2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C53560=??_7MissileUpdate@@6BRva004A76DEBase2@@@")
extern "C" const void *const vtbl_00C5362C[];  // ??_7MissileUpdate@@6BRva004A76DEBase0@@@
#pragma comment(linker, "/alternatename:_vtbl_00C5362C=??_7MissileUpdate@@6BRva004A76DEBase0@@@")

class Thing;
class ModuleData;

class BezierProjectileBehavior
{
public:
	BezierProjectileBehavior(Thing *thing, const ModuleData *moduleData);
	void rva0045C026();

protected:
	const void *m_vtable0; // +0
	Thing *m_thing; // +4 (stored by the base ctor, reloaded below)
	const ModuleData *m_data; // +8 (stored by the base ctor, reloaded below)
	const void *m_vtableC; // +0xC
	const void *m_vtable10; // +0x10
	unsigned char m_pad14[0xC]; // +0x14..+0x1F
	const void *m_vtable20; // +0x20
	const void *m_vtable24; // +0x24
	unsigned char m_pad28[0x88 - 0x28]; // +0x28..+0x87
};

class Thing
{
public:
	unsigned char m_pad[0xCC];
	int m_unkCC; // +0xCC
};

struct TriInt
{
	int m_first;
	int m_second;
	int m_third;
};

struct Coord3D
{
	void zero() { m_x = 0.0f; m_y = 0.0f; m_z = 0.0f; }
	float m_x;
	float m_y;
	float m_z;
};

class ModuleData
{
public:
	unsigned char m_pad[0x38];
	TriInt m_flight; // +0x38 (copied into the behavior +0xAC)
};

class GameLogic
{
public:
	unsigned int getFrame() { return m_frame; }

private:
	unsigned char m_pad[0x40];
	unsigned int m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class MissileUpdate : public BezierProjectileBehavior
{
public:
	MissileUpdate(Thing *thing, const ModuleData *moduleData);
	void Rva004A7512Clear();
	void Rva004A7530Set(int val);
	void Rva004A75A3Init();
	void rva004A7580();

private:
	int m_88; // +0x88
	unsigned int m_frame; // +0x8C (TheGameLogic frame)
	int m_90; // +0x90
	int m_94; // +0x94
	int m_98; // +0x98
	int m_9C; // +0x9C (Thing+0xCC)
	Coord3D m_velA; // +0xA0
	TriInt m_flight; // +0xAC (ModuleData+0x38 block)
	Coord3D m_velB; // +0xB8
	int m_C4; // +0xC4
	int m_C8; // +0xC8
	unsigned char m_CC; // +0xCC
	unsigned char m_CD; // +0xCD
	unsigned char m_CE; // +0xCE
};

// ??0MissileUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004A75B9
MissileUpdate::MissileUpdate(Thing *thing, const ModuleData *moduleData) :
	BezierProjectileBehavior(thing, moduleData)
{
	m_vtable0 = reinterpret_cast<const void *>(((unsigned int)vtbl_00C5362C));
	m_vtableC = reinterpret_cast<const void *>(((unsigned int)vtbl_00C53570));
	m_vtable10 = reinterpret_cast<const void *>(((unsigned int)vtbl_00C53560));
	m_vtable20 = reinterpret_cast<const void *>(((unsigned int)vtbl_00C53548));
	m_vtable24 = reinterpret_cast<const void *>(((unsigned int)vtbl_00C53530));
	m_88 = 0;
	m_frame = TheGameLogic->getFrame();
	Thing *storedThing = m_thing;
	m_90 = 0;
	m_94 = 0;
	m_CD = 0;
	m_98 = 0;
	m_9C = storedThing->m_unkCC;
	m_flight = m_data->m_flight;
	m_CC = 0;
	m_C8 = 0;
	m_C4 = 0;
	m_velA.zero();
	m_CE = 0;
	m_velB.zero();
}
void MissileUpdate::Rva004A7512Clear()
{
	int id = m_C8;
	if (id != 0)
	{
		TheParticleSystemManager->destroyParticleSystemByID((ParticleSystemID)id);
		m_C8 = 0;
	}
}
void MissileUpdate::Rva004A7530Set(int val)
{
	if (m_88 != val)
	{
		m_88 = val;
		m_frame = TheGameLogic->getFrame();
	}
}
void MissileUpdate::Rva004A75A3Init()
{
	m_98 = TheGameLogic->getFrame();
	Rva004A7530Set(7);
}
void MissileUpdate::rva004A7580()
{
	if (m_CE != 0)
		return;
	rva0045C026();
	Rva004A7530Set(7);
	m_CE = 1;
}
