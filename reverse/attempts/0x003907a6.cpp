// ??0PhysicsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.99 date=2026-09-26
// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: sole raw caller is the rowed PhysicsBehavior instance factory
// 0x24E73C (news 0x34); Dumb pin at this address superseded.
// 182/182B 52/52insns; vtables are gate-filled relocs. Sole wall: EH state1
// store placement (ours 0x45 eager after vector-ctor, retail 0x98 sunk below
// the setWakeFrame pushes to just before the MD store). Refuted: barrier
// removal (MD-load hoists), empty asm (no barrier), volatile load (hoists),
// /EHsc + /EHs (same wall). Retry needs a non-flushing order lever, not flags.
// stlport
//
#include <vector>

struct BfmeE16
{
	unsigned char m_pad[16];
};

class Thing;
class ModuleData;
class Object;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, unsigned int frame);
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class PhysicsBehaviorModuleData
{
public:
	unsigned char m_pad[0x58];
	unsigned char m_bfme58;
};

class PhysicsBehavior : public UpdateModule
{
public:
	PhysicsBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~PhysicsBehavior();
private:
	_STL::vector<BfmeE16> m_elements;
	float m_bfme2C;
	float m_bfme30;
	float m_bfme34;
	float m_bfme38;
	float m_bfme3C;
	float m_bfme40;
	float m_bfme44;
	float m_bfme48;
	int m_bfme4C;
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	bool m_bfme5C;
	unsigned char m_bfme5D;
	bool m_bfme5E;
	bool m_bfme5F;
	int m_bfme60;
	int m_bfme64;
};

// ??0PhysicsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x003907A6
PhysicsBehavior::PhysicsBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	m_bfme44 = 0.0f;
	m_bfme48 = 0.0f;
	m_bfme4C = 0;
	m_bfme50 = 0;
	m_bfme54 = 0;
	m_bfme58 = 0;
	m_bfme5C = false;
	m_bfme5E = false;
	m_bfme5F = false;
	m_bfme60 = 0;
	m_bfme64 = 0;
	m_bfme2C = 0.0f;
	m_bfme30 = 0.0f;
	m_bfme34 = 0.0f;
	m_bfme38 = 0.0f;
	m_bfme3C = 0.0f;
	m_bfme40 = 0.0f;
	_ReadWriteBarrier();
	m_bfme5D = reinterpret_cast<const PhysicsBehaviorModuleData *>(m_moduleData)->m_bfme58;
	setWakeFrame(m_object, 0x3fffffff);
}
