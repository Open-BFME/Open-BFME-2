// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0FreeLifeBodyModuleData@@QAE@XZ, retail 0x004C1B3B, 64 bytes. Frameless
// ctor over the pinned RespawnUpdate base (0x4C14DF): vtable literal
// 0x00C5BC48, HealthPercent 0.0f at +0x6C, Time 0 at +0x70, Invincible false
// at +0x74, AnimAndDuration |= -1 at +0x78 with zeroed spares at +0x7C/+0x80,
// Prerequisite null at +0x84 (own table 0x0085BD38 all five fields). The TU-
// local base keeps an explicit vtable slot (DestroyEnvironment precedent, so
// no vtable is emitted). Scheduling: the early address-take commits the
// +0x78 block to eax-addressing, so lea hoists with the xor pair above the
// vtable store while both |= stay in place; the second |= is spelled direct
// which defeats the CSE that eats a repeated pointer-spelled |=. No barrier
// needed (a barrier traps the lea below the movs).

class RespawnBodyModuleData
{
public:
	RespawnBodyModuleData();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x6C - 4];
};

class FreeLifeBodyModuleData : public RespawnBodyModuleData
{
public:
	FreeLifeBodyModuleData();

private:
	float m_healthPercent; // +0x6C
	int m_lifeTime; // +0x70
	bool m_invincible; // +0x74
	int m_animAndDuration; // +0x78
	int m_unused7C; // +0x7C
	int m_unused80; // +0x80
	void *m_prerequisite; // +0x84
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ??0FreeLifeBodyModuleData@@QAE@XZ @0x4C1B3B
FreeLifeBodyModuleData::FreeLifeBodyModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00C5BC48);
	int *animSlots = &m_animAndDuration;
	m_healthPercent = 0.0f;
	m_lifeTime = 0;
	m_invincible = false;
	animSlots[0] |= -1;
	animSlots[1] = 0;
	animSlots[2] = 0;
	m_animAndDuration |= -1;
	m_prerequisite = 0;
	m_unused7C = 0;
	m_unused80 = 0;
}
