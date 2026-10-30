// cl: /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1BoneFXUpdate@@MAE@XZ, retail 0x00487ABF, 161 bytes.
//
// BoneFXUpdate virtual dtor (MAE, protected virtual, most Module/Behavior
// precedent). Donor is ZH BoneFXUpdate.cpp dtor verbatim:
// `~BoneFXUpdate() { killRunningParticleSystems(); }` — the three Coord
// arrays, the ParticleSystemID vector and the UpdateModule base are
// compiler-generated after the body, exactly as retail: vtable reinstall
// (C4B170/BEFF90/C4B164 via three-vptr UpdateModule hierarchy,
// Flood/StructureTopple precedent), killRunning call (rowed 0x487A64),
// three reverse-order ??_M destroys (0x629110 helper, dtor rowed 0xB3FD0
// Coord/validate fold, count 0x20 size 0xC), vector storage free via rowed
// _free 0x30830, base UpdateModule dtor via pin 0x24A797 (UAE). Layout
// matches the landed ctor TU (vector +0x20, frames +0x2C/+0xAC/+0x12C,
// positions +0x1AC/+0x32C/+0x4AC, curBodyState +0x62C, bonesResolved +0x630,
// active +0x634, size 0x638). /O1 for EBP frame and push-immidiates; /GX
// for EH prologue and states 4/3/2/1/0; /arch:SSE harmless (no floats here)
// and keeps the proven ctor flag combo.

#include <vector>

class Thing;
class ModuleData;
class Object;

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

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

// Keep stateless allocator wrappers inline and provide the real POD-vector
// teardown used by native exception cleanup. These bodies follow the local
// allocator shim and STLport header; reusing the allocator subobject avoids
// introducing a temporary lifetime into retail's five-state EH graph.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<ParticleSystemID>::deallocate(ParticleSystemID *__p, size_t __n) const
{
    _STLP_ASSERT((__p == 0) == (__n == 0))
    if (__p != 0) ::free((void *)__p);
}

template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<ParticleSystemID *, ParticleSystemID, allocator<ParticleSystemID> >::deallocate(ParticleSystemID *__p, size_t __n)
{
    __stl_alloc_rebind(static_cast<allocator<ParticleSystemID> &>(*this),
        (ParticleSystemID *)0).deallocate(__p, __n);
}

template <> __declspec(nothrow) __forceinline
_Vector_base<ParticleSystemID, allocator<ParticleSystemID> >::~_Vector_base()
{
    if (_M_start != 0)
        _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
}

}

typedef _STL::vector<ParticleSystemID, _STL::allocator<ParticleSystemID> > ParticleSystemIDVec;

enum { BONE_FX_MAX_BONES = 8 };
enum { BODYDAMAGETYPE_COUNT = 4 };

class BoneFXUpdate : public UpdateModule
{
protected:
	virtual ~BoneFXUpdate();
	void killRunningParticleSystems();

public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	BoneFXUpdate(Thing *thing, const ModuleData *moduleData);

private:

	ParticleSystemIDVec m_particleSystemIDs; // +0x20
	int m_nextFXFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x2C
	int m_nextOCLFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0xAC
	int m_nextParticleSystemFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x12C
	Coord3D m_FXBonePositions[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x1AC
	Coord3D m_OCLBonePositions[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x32C
	Coord3D m_PSBonePositions[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x4AC
	int m_curBodyState; // +0x62C
	bool m_bonesResolved[BODYDAMAGETYPE_COUNT]; // +0x630
	bool m_active; // +0x634
};

BoneFXUpdate::~BoneFXUpdate()
{
	killRunningParticleSystems();
}
