// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0BoneFXUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004878E6, 307 bytes.
//
// BoneFXUpdate 2-arg ctor. Donor is Zero Hour BoneFXUpdate.cpp ctor
// (reference/open-bfme-1/.../GeneralsMD/.../BoneFXUpdate.cpp:61) verbatim:
// UpdateModule base, vector clear, -1 frames, Coord zero, bonesResolved
// false, active false, curBodyState pristine. BFME2 layout matches ZH
// (UpdateModule 0x20 per UpdateModuleCtor.cpp, vector at +0x20, frames at
// +0x2C/+0xAC/+0x12C, positions at +0x1AC/+0x32C/+0x4AC, curBodyState at
// +0x62C, bonesResolved at +0x630, active at +0x634, size 0x638 per the
// rowed friend_newModuleInstance factory). Secondaries 0xBEFF90/+0x0C and
// 0xC4B164/+0x10 plus primary 0xC4B170 follow the DynamicShroud/Attach
// explicit-member precedent (DIR32). Coord arrays ride ehvec 0x629512 via
// declared-only ctor/dtor (rowed Coord3D 0x47A6A9/0xB3FD0 ICF folds);
// vector base/erases resolve via the rowed BfmeE16/ScienceType folds and
// the rowed ParticleSystemID erase at 0x532803. /O1 for or-minus-1,
// and-zero, push-8/pop-edi and EBP frame; /GX for the EH prologue and
// states 0-3; /arch:SSE for xorps/movss zeros.

#include <vector>

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();
};

struct Coord3D
{
	Coord3D();
	~Coord3D();
	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	float x;
	float y;
	float z;
};

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

typedef _STL::vector<ParticleSystemID, _STL::allocator<ParticleSystemID> > ParticleSystemIDVec;

enum BodyDamageType
{
	BODY_PRISTINE = 0,
	BODY_DAMAGED = 1,
	BODY_REALLYDAMAGED = 2,
	BODY_RUBBLE = 3
};

enum
{
	BONE_FX_MAX_BONES = 8,
	BODYDAMAGETYPE_COUNT = 4
};

class BoneFXUpdate : public UpdateModule
{
public:
	BoneFXUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_vtable; // +0x00, retail 0x00C4B170
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	const void *m_secondary0C; // +0x0C, retail 0x00BEFF90
	const void *m_secondary10; // +0x10, retail 0x00C4B164
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_reserved1C; // +0x1C
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

BoneFXUpdate::BoneFXUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	m_vtable(reinterpret_cast<const void *>(0x00C4B170)),
	m_secondary0C(reinterpret_cast<const void *>(0x00BEFF90)),
	m_secondary10(reinterpret_cast<const void *>(0x00C4B164))
{
	int i, j;
	for (i = 0; i < BODYDAMAGETYPE_COUNT; ++i) {
		for (j = 0; j < BONE_FX_MAX_BONES; ++j) {
			m_nextFXFrame[i][j] = -1;
			m_nextOCLFrame[i][j] = -1;
			m_nextParticleSystemFrame[i][j] = -1;
			m_FXBonePositions[i][j].zero();
			m_OCLBonePositions[i][j].zero();
			m_PSBonePositions[i][j].zero();
		}
		m_bonesResolved[i] = false;
	}
	m_particleSystemIDs.clear();
	m_curBodyState = BODY_PRISTINE;
	m_active = false;
}
