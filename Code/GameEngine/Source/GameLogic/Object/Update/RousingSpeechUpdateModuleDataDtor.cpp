// cl: /O1 /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1RousingSpeechUpdateModuleData@@UAE@XZ, retail 0x004AD34F, 74 bytes.
// RousingSpeechUpdateModuleData dtor: destroys the ObjectFilter at +0xF4
// through the pinned 0x360D26 forwarder (state 1) then the ModifierName
// AsciiString vector at +0xE4 through the rowed 0x2CC70 body (state 0) then
// the DamageModuleBase base through the pinned 0x44ECCE body. Layout from
// the rowed ctor 0x4AD0EE (base 0xC8 plus BonusRadius +0xC8 plus
// SpeechDuration +0xCC plus UpdateInterval +0xD0 plus LeaderFX +0xD4 plus
// FollowerFX +0xD8 plus CreateWave +0xDC plus WaveWidth +0xE0 plus vector
// +0xE4 plus LevelUp +0xF0 plus filter +0xF4 total 0xF8 matching the factory
// 0x24F58C news) and the chained table 0x00C54F28 with 10 of 10 BFME1 fields.
// Identity via vtable 0x00C55048 slot 0 deleting dtor 0x004AD333 calling here
// and the BFME1 RousingSpeechUpdateModuleDataDestructorThunk donor. Shape
// follows CivilianSpawnUpdateModuleDataDtor (2-member EH dword-1 byte-0)
// plus LevelGrantSpecialPowerModuleDataDtor (novtable plus 0x44ECCE base).
#include <vector>

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class DamageModuleBase
{
public:
	virtual ~DamageModuleBase();

private:
	unsigned char m_pad[0xC8 - 4];
};

class __declspec(novtable) RousingSpeechUpdateModuleData : public DamageModuleBase
{
public:
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
	_STL::vector<AsciiString> m_modifierNames; // +0xE4
	unsigned char m_levelUp; // +0xF0
	unsigned char m_padF1[3]; // +0xF1
	Rva00360D26Member m_objectFilter; // +0xF4
};

// ??1RousingSpeechUpdateModuleData@@UAE@XZ @0x004AD34F
RousingSpeechUpdateModuleData::~RousingSpeechUpdateModuleData()
{
}
