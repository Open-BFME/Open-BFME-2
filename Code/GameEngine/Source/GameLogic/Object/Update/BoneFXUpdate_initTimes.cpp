// cl: /DNDEBUG /MD /EHs-c-
// BoneFXUpdate::initTimes — retail 0x0048750B / 297B.
// Upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp
// (BoneFXUpdate::initTimes, ZH uses REAL_TO_INT; retail BFME2 uses a plain
// (int) cast which calls __ftol2 — same transfer BFME1 landed in
// reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_initTimes.cpp).
// Layout notes (all verified against the target disasm):
// - GameLogic::m_frame at +0x40 (ZH/BFME1 have +0x3C; BFME2 added 4 bytes).
// - BoneFXUpdateModuleData matches ZH exactly: m_fxList at +0x0C (base 0x08 +
//   m_damageFXTypes 4), m_OCL at +0x490, m_particleSystem at +0x914, element
//   size 0x24.
// - BoneFXUpdate matches ZH: m_moduleData at +4, m_nextFXFrame at +0x2C,
//   m_nextOCLFrame at +0xAC, m_curBodyState at +0x62C.
// - BoneLocInfo is a single-AsciiString wrapper, so the shim names the member
//   boneName directly (offset 0, identical codegen to locInfo.boneName).
// - AsciiString::compare is DECLARED only so the three call sites encode the
//   retail StringBase::compare at 0x000069D6 (see symbols.csv pin); defining it
//   locally with memcmp (as BFME1 did) would call memcmp instead and mismatch.

class AsciiString
{
public:
	static const AsciiString TheEmptyString;

	int compare(const AsciiString &stringSrc) const;

private:
	struct AsciiStringHeader *m_data;
};

// AsciiString::TheEmptyString: defined in Common/Rva00380200Getter.cpp.

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

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

private:
	char m_pad[0x40];
	unsigned int m_frame;
};

GameLogic *TheGameLogic;

enum { BONE_FX_MAX_BONES = 8 };
enum { BODYDAMAGETYPE_COUNT = 4 };

struct BoneFXListInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	int onlyOnce;
	void *payload;
};

struct BoneOCLInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	int onlyOnce;
	void *payload;
};

struct BoneParticleSystemInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	int onlyOnce;
	void *payload;
};

class BoneFXUpdateModuleData
{
public:
	char m_hdr[0x0C];
	BoneFXListInfo m_fxList[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_damageOCLTypes;
	BoneOCLInfo m_OCL[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_damageParticleTypes;
	BoneParticleSystemInfo m_particleSystem[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
};

class BoneFXUpdate
{
protected:
	void initTimes();

public:
	const BoneFXUpdateModuleData *getBoneFXUpdateModuleData() const
	{
		return m_moduleData;
	}

private:
	void *m_vptr;
	const BoneFXUpdateModuleData *m_moduleData;
	char m_beforeFrames[0x2C - 8];
	int m_nextFXFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_nextOCLFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_nextParticleSystemFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	char m_positions[0x62C - 0x1AC];
	int m_curBodyState;
};

void BoneFXUpdate::initTimes()
{
	int i;
	const BoneFXUpdateModuleData *d = getBoneFXUpdateModuleData();
	int now = TheGameLogic->getFrame();

	for (i = 0; i < BONE_FX_MAX_BONES; ++i) {
		if (d->m_fxList[m_curBodyState][i].boneName.compare(AsciiString::TheEmptyString) != 0) {
			m_nextFXFrame[m_curBodyState][i] = now + (int)d->m_fxList[m_curBodyState][i].gameLogicDelay.getValue();
		} else {
			m_nextFXFrame[m_curBodyState][i] = -1;
		}
		if (d->m_OCL[m_curBodyState][i].boneName.compare(AsciiString::TheEmptyString) != 0) {
			m_nextOCLFrame[m_curBodyState][i] = now + (int)d->m_OCL[m_curBodyState][i].gameLogicDelay.getValue();
		} else {
			m_nextOCLFrame[m_curBodyState][i] = -1;
		}
		if (d->m_particleSystem[m_curBodyState][i].boneName.compare(AsciiString::TheEmptyString) != 0) {
			m_nextParticleSystemFrame[m_curBodyState][i] = now + (int)d->m_particleSystem[m_curBodyState][i].gameClientDelay.getValue();
		} else {
			m_nextParticleSystemFrame[m_curBodyState][i] = -1;
		}
	}
}
