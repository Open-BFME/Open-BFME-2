// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0RousingSpeechUpdateModuleData@@QAE@XZ, retail 0x004AD0EE, 136 bytes.
// Rousing-speech behavior data: the own table at 0x00C54F28 carries
// BonusRadius at +0xC8, SpeechDuration at +0xCC, UpdateInterval at +0xD0,
// LeaderFX at +0xD4, FollowerFX at +0xD8, CreateWave at +0xDC, WaveWidth
// at +0xE0, ModifierName at +0xE4, LevelUp at +0xF0 and ObjectFilter at
// +0xF4, matching every store below; the ModuleData factory at 0x24F58C
// news 0xF8 and the pool key at 0x4ACED8 proves the class. Shape follows
// SupplyCenterProductionExitUpdateCtor (opaque 0xC8 virtual base through
// the 0x44EB54 pin, derived virtuals) plus the AutoPickUp/Bored recipe
// (BfmeE16 vector member through the 0x211E58 fold, filter with declared
// dtor, /arch:SSE float zeros). Retail runs base-call, state-0, vtable,
// zeros, vector-call, byte, filter-call, state-1, which the all-init-list
// transcription reproduces: the ModifierName element type is unproven, so
// the TU keeps the BfmeE16 stand-in (fold-equivalent and byte-correct,
// BattlePlanUpdate precedent) and the row carries the identity.

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

private:
	int m_x;
};

class Rva0044EB54
{
public:
	Rva0044EB54();
	virtual ~Rva0044EB54();

protected:
	unsigned char m_pad[0xC8 - 4];
};

Rva0044EB54::~Rva0044EB54()
{
}

class RousingSpeechUpdateModuleData : public Rva0044EB54
{
public:
	RousingSpeechUpdateModuleData();
	virtual ~RousingSpeechUpdateModuleData();

private:
	float m_bonusRadius; // +0xC8
	int m_speechDuration; // +0xCC
	int m_updateInterval; // +0xD0
	int m_leaderFX; // +0xD4
	int m_followerFX; // +0xD8
	unsigned char m_createWave; // +0xDC
	unsigned char m_padDD[3]; // +0xDD
	float m_waveWidth; // +0xE0
	_STL::vector<BfmeE16> m_modifierNames; // +0xE4, element unproven
	unsigned char m_levelUp; // +0xF0
	unsigned char m_padF1[3]; // +0xF1
	Rva003623E5Member m_objectFilter; // +0xF4
};

RousingSpeechUpdateModuleData::~RousingSpeechUpdateModuleData()
{
}

// ??0RousingSpeechUpdateModuleData@@QAE@XZ @0x4AD0EE
RousingSpeechUpdateModuleData::RousingSpeechUpdateModuleData()
	: Rva0044EB54()
	, m_bonusRadius(0.0f)
	, m_speechDuration(0)
	, m_updateInterval(0)
	, m_leaderFX(0)
	, m_followerFX(0)
	, m_createWave(0)
	, m_waveWidth(0.0f)
	, m_levelUp(0)
{
}
