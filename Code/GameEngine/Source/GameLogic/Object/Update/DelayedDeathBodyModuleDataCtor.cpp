// cl: /O1 /DNDEBUG /MD
//
// ??0DelayedDeathBodyModuleData@@QAE@XZ, retail 0x004C180A (37 bytes).
// Frameless Body-side ModuleData for delayed death: runs the pinned
// RespawnUpdate base ctor (0x4C14DF), installs the explicit vtable 0xC5BC48,
// zeroes the DelayedDeath scalars and sets the Immortal and DoHealthCheck
// bytes matching the rowed chained proc's table 0x0085BAE8
// (DelayedDeathTime at +0x6C, ImmortalUntilDeathTime at +0x70,
// InvulnerableFX at +0x74, DoHealthCheck at +0x78,
// DelayedDeathPrerequisiteUpgrade at +0x7C). Flat classes throughout (no
// declared dtors anywhere) keep the body frameless. The DelayedDeathBody
// pool key at 0x4C1642 sits in the same cluster; the ModuleData factory at
// 0x251622 (news 0x80) is the only raw caller. Supersedes nothing (no pin);
// the FreeLifeBody sibling shares the base and vtable.

class RespawnUpdateModuleData
{
public:
	RespawnUpdateModuleData();

private:
	unsigned char m_pad[0x6C];
};

class DelayedDeathBodyModuleData : public RespawnUpdateModuleData
{
public:
	DelayedDeathBodyModuleData();

private:
	int m_delayedDeathTime; // +0x6C
	unsigned char m_immortal; // +0x70
	unsigned char m_pad71[3];
	int m_invulnerableFX; // +0x74
	unsigned char m_doHealthCheck; // +0x78
	unsigned char m_pad79[3];
	int m_prerequisite; // +0x7C
};

// ??0DelayedDeathBodyModuleData@@QAE@XZ @0x4C180A
DelayedDeathBodyModuleData::DelayedDeathBodyModuleData()
	: RespawnUpdateModuleData()
{
	m_delayedDeathTime = 0;
	m_invulnerableFX = 0;
	m_prerequisite = 0;
	*(unsigned int *)this = 0x00C5BC48;
	m_immortal = 1;
	m_doHealthCheck = 1;
}
