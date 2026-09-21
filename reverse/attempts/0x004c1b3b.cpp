// ??0FreeLifeBodyModuleData@@QAE@XZ
// partial score=0.8 date=2026-09-21
// cl: /O1 /arch:SSE /DNDEBUG /MD /Oi
//
// ??0FreeLifeBodyModuleData@@QAE@XZ, retail 0x004C1B3B (64 bytes). Frameless
// Body-side ModuleData for the free-life respawn: runs the pinned
// RespawnUpdate base ctor (0x4C14DF), installs the explicit vtable 0xC5BC48,
// zeroes the FreeLife scalars and sets the anim state matching the rowed
// chained proc's table 0x0085BD38 (FreeLifeHealthPercent at +0x6C,
// FreeLifeTime at +0x70, FreeLifeInvincible at +0x74, FreeLifeAnimAndDuration
// at +0x78, FreeLifePrerequisiteUpgrade at +0x84). The +0x78 anim block is
// primed through a local pointer (retail's lea plus indirect forms) while
// the re-touch of the mask is fenced by _ReadWriteBarrier (zero bytes,
// MarkerType precedent against dead-store folding) and the trailing words
// land through plain member access (retail's direct forms). Flat classes
// throughout (no declared dtors anywhere) keep the body frameless. The
// FreeLifeBody pool key at 0x4C18AA sits in the same cluster; the ModuleData
// factory at 0x2516B1 (news 0x88) is the only raw caller. Supersedes the
// 0x4C1B3B ctor pin (row proves the body).

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier();

class RespawnUpdateModuleData
{
public:
	RespawnUpdateModuleData();

private:
	unsigned char m_pad[0x6C];
};

struct FreeLifeAnimAndDuration
{
	int m_animMask;
	int m_word7C;
	int m_word80;

	void init()
	{
		m_animMask |= -1;
		m_word7C = 0;
		m_word80 = 0;
	}
};

class FreeLifeBodyModuleData : public RespawnUpdateModuleData
{
public:
	FreeLifeBodyModuleData();

private:
	float m_healthPercent; // +0x6C
	int m_time; // +0x70
	unsigned char m_invincible; // +0x74
	unsigned char m_pad75[3];
	FreeLifeAnimAndDuration m_anim; // +0x78
	int m_prerequisite; // +0x84
};

// ??0FreeLifeBodyModuleData@@QAE@XZ @0x4C1B3B
FreeLifeBodyModuleData::FreeLifeBodyModuleData()
	: RespawnUpdateModuleData()
{
	FreeLifeAnimAndDuration *register anim = &m_anim;
	*(unsigned int *)this = 0x00C5BC48;
	m_healthPercent = 0.0f;
	m_time = 0;
	m_invincible = 0;
	anim->init();
	_ReadWriteBarrier();
	anim->m_animMask |= -1;
	m_prerequisite = 0;
	m_anim.m_word7C = 0;
	m_anim.m_word80 = 0;
}
