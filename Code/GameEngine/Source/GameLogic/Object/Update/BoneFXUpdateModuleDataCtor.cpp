// cl: /O1 /GX /DNDEBUG /MD
//
// ??0BoneFXUpdateModuleData@@QAE@XZ, retail 0x00487797, 196 bytes.
//
// The module-data half of BoneFXUpdate: three [4][8] info arrays (FX, OCL,
// particle-system) of 0x24-byte elements plus the three damage-type flag
// words. Total 0xD94 bytes (the rowed factory news exactly that).
//
// Layout (retail-proven, agrees with the landed initTimes TU in this
// directory): vtable at +0, 4 bytes of base at +4 the retail ctor never
// stores, damage flags at +8/+0x48C/+0x910, arrays at +0x0C/+0x490/+0x914.
// Each element is AsciiString boneName at +0, two trivial 12-byte random
// variables at +4/+0x10, a single-byte onlyOnce at +0x1C (retail stores it
// with a byte mov, so it is bool, not the donor's int-sized Bool) and the
// payload pointer at +0x20.
//
// The donor is the Zero Hour BoneFXUpdateModuleData ctor (null payload plus
// onlyOnce true over the whole [4][8], then flip each damage word). Retail
// keeps only the flip half of the flag assignment as a lone `or -1` per
// word, and the /O1 scheduler groups the three null stores ahead of the
// three byte stores. The empty UpdateModuleData base (inline-empty ctor
// plus declared-only dtor, Topple precedent) arms the single EH state with
// no emitted code; the three arrays bracket states 0/1/2 exactly as retail.
// The string clears through the rowed AsciiString clear fold.

typedef int Int;

#define NULL 0

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class GameClientRandomVariable
{
public:
	float getValue() const;

private:
	int m_type;
	float m_low;
	float m_high;
};

class GameLogicRandomVariable
{
public:
	float getValue() const;

private:
	int m_type;
	float m_low;
	float m_high;
};

class FXList;
class ObjectCreationList;
class ParticleSystemTemplate;

struct BoneFXListInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	bool onlyOnce;
	unsigned char m_pad[3];
	const FXList *fx;
};

struct BoneOCLInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	bool onlyOnce;
	unsigned char m_pad[3];
	const ObjectCreationList *ocl;
};

struct BoneParticleSystemInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	bool onlyOnce;
	unsigned char m_pad[3];
	const ParticleSystemTemplate *particleSysTemplate;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

enum { BONE_FX_MAX_BONES = 8 };
enum { BODYDAMAGETYPE_COUNT = 4 };

class BoneFXUpdateModuleData : public UpdateModuleData
{
public:
	BoneFXUpdateModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	int m_damageFXTypes;
	BoneFXListInfo m_fxList[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_damageOCLTypes;
	BoneOCLInfo m_OCL[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_damageParticleTypes;
	BoneParticleSystemInfo m_particleSystem[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
};

BoneFXUpdateModuleData::BoneFXUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4B0E8))
{
	Int i, j;
	for (i = 0; i < BODYDAMAGETYPE_COUNT; ++i) {
		for (j = 0; j < BONE_FX_MAX_BONES; ++j) {
			m_fxList[i][j].fx = NULL;
			m_fxList[i][j].onlyOnce = true;
			m_OCL[i][j].ocl = NULL;
			m_OCL[i][j].onlyOnce = true;
			m_particleSystem[i][j].particleSysTemplate = NULL;
			m_particleSystem[i][j].onlyOnce = true;
		}
	}

	m_damageFXTypes |= -1;
	m_damageOCLTypes |= -1;
	m_damageParticleTypes |= -1;
}
