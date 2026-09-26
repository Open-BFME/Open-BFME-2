// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
// stlport
//
// ??0SlowDeathBehaviorModuleData@@QAE@XZ, retail 0x0045E386, 287 bytes.
// SlowDeath ModuleData EH ctor over vtable 0x00C42108 (installed
// automatically via virtual base, RubbleRise precedent). Layout from the
// rowed INI table 0x00C42290 (SinkRate@0x38 ProbabilityModifier@0x3c
// ModifierBonus@0x40 SinkDelay@0x44 SinkDelayVariance@0x48 DestructionDelay
// @0x4c DestructionDelayVariance@0x50 DecayBeginTime@0x54 FX@0x58 OCL@0x88
// Weapon@0xb8 Sound@0xe8 FlingForce@0x118 FlingForceVariance@0x11c
// FlingPitch@0x120 FlingPitchVariance@0x124 DeathFlags@0x128/0x174
// FadeTime@0x184 FadeDelay@0x188 ShadowWhenDead@0x18d) plus DieMuxData@0x08
// (0x30 via alias pin ??0DieMuxData at 0x4CE534, StructureCollapse
// precedent) plus mask@0x18c (HAS_FX=1 HAS_OCL=2 HAS_WEAPON=4 HAS_SOUND=8
// proven by parse procs 0x45E533/0x45E5A4/0x45E618/0x45E8A9 doing or byte
// [reg+0x18c],1/2/4/8). Phase count 4 (ehvec size 0xc count 4, RubbleRise
// 4-phase precedent). Rva0042526Member@0x128 (0x4c via rowed 0x42526) and
// bitset<128>@0x174 (reset via rowed 0x24CA24) are DeathFlags members
// (parse 0x45E293 leas 0x128 and 0x174). Size 0x190 matches factory
// 0x24B29C news 0x190 (SlowDeathBehaviorModuleDataFriendNew). Donor is ZH
// SlowDeathBehavior.h (same member order, BFME2 adds Sound/DeathFlags/
// Fade/Shadow and 4th phase). Identity is pinned name plus 4 callers
// (friend_new 0x24B2C0 Ship 0x45E964 GiantBird 0x461F83 ClearanceTesting
// 0x483E36).
#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset() throw();
}

class DieMuxData
{
public:
	DieMuxData();

private:
	unsigned char m_bytes[0x30];
};

class SlowDeathFXVec
{
public:
	SlowDeathFXVec();
	~SlowDeathFXVec();

private:
	unsigned char m_data[0x0C];
};

class SlowDeathOCLVec
{
public:
	SlowDeathOCLVec();
	~SlowDeathOCLVec();

private:
	unsigned char m_data[0x0C];
};

class SlowDeathWeaponVec
{
public:
	SlowDeathWeaponVec();
	~SlowDeathWeaponVec();

private:
	unsigned char m_data[0x0C];
};

class SlowDeathSoundVec
{
public:
	SlowDeathSoundVec();
	~SlowDeathSoundVec();

private:
	unsigned char m_data[0x0C];
};

class Rva0042526Member
{
public:
	Rva0042526Member() throw();

private:
	unsigned char m_pad[0x4C];
};

class UpdateModuleData
{
public:
	virtual ~UpdateModuleData();

private:
	unsigned char m_pad04[4];
};

enum
{
	SLOWDEATH_PHASE_COUNT = 4,
};

class SlowDeathBehaviorModuleData : public UpdateModuleData
{
public:
	SlowDeathBehaviorModuleData();
	virtual ~SlowDeathBehaviorModuleData();

private:
	DieMuxData m_dieMuxData; // +0x08
	float m_sinkRate; // +0x38
	int m_probabilityModifier; // +0x3c
	float m_modifierBonusPerOverkillPercent; // +0x40
	unsigned int m_sinkDelay; // +0x44
	unsigned int m_sinkDelayVariance; // +0x48
	unsigned int m_destructionDelay; // +0x4c
	unsigned int m_destructionDelayVariance; // +0x50
	unsigned int m_decayBeginTime; // +0x54
	SlowDeathFXVec m_fx[SLOWDEATH_PHASE_COUNT]; // +0x58
	SlowDeathOCLVec m_ocls[SLOWDEATH_PHASE_COUNT]; // +0x88
	SlowDeathWeaponVec m_weapons[SLOWDEATH_PHASE_COUNT]; // +0xb8
	SlowDeathSoundVec m_sounds[SLOWDEATH_PHASE_COUNT]; // +0xe8
	float m_flingForce; // +0x118
	float m_flingForceVariance; // +0x11c
	float m_flingPitch; // +0x120
	float m_flingPitchVariance; // +0x124
	Rva0042526Member m_unk128; // +0x128
	unsigned long m_unk174[4]; // +0x174 bitset<128>
	int m_fadeTime; // +0x184
	int m_fadeDelay; // +0x188
	unsigned char m_maskOfLoadedEffects; // +0x18c
	bool m_shadowWhenDead; // +0x18d
};

SlowDeathBehaviorModuleData::SlowDeathBehaviorModuleData()
{
	((_STL::bitset<128> *)m_unk174)->reset();
	m_sinkDelay = 0;
	m_sinkDelayVariance = 0;
	m_destructionDelay = 0;
	m_destructionDelayVariance = 0;
	m_decayBeginTime = 0;
	m_maskOfLoadedEffects = 0;
	m_shadowWhenDead = false;
	m_sinkRate = 0.0f;
	m_probabilityModifier = 10;
	m_modifierBonusPerOverkillPercent = 0.0f;
	m_flingForce = 0.0f;
	m_flingForceVariance = 0.0f;
	m_flingPitch = 0.0f;
	m_flingPitchVariance = 0.0f;
	m_fadeTime = 6;
	m_fadeDelay = 0xfacade00;
}
