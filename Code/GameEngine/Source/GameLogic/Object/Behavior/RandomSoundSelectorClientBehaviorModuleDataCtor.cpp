// cl: /O1 /GX /DNDEBUG /MD /arch:SSE
//
// ??0RandomSoundSelectorClientBehaviorModuleData@@QAE@XZ, retail 0x0025785C,
// 102 bytes. Nullary ModuleData ctor over the rowed factory (0x25792A, news
// 0x1E0) and rowed proc (0x4CBC09, table 0xC5F318). Field layout from the
// table: UnitSpecificSounds at +0x1C8, Chance at +0x1D4, VoicePriority at
// +0x1D8, RerollOnEveryFrame at +0x1DD. The +8 region is a 448-byte array
// member (56 8-byte elements built by the 5-arg ehvec in 0x254FE4); the
// +0x1C8 member is 12 bytes built by 0x24613C. Both are TU-local opaque
// members with pins. The empty base (inline-empty ctor plus declared-only
// dtor) drives the two EH states with zero emitted code (Topple pattern);
// without it the TU emits a single state. Chance defaults to 0.5 as a
// literal (pool-merged movss, address masked).

class Rva00254FE4Member
{
public:
	Rva00254FE4Member();
	~Rva00254FE4Member();

private:
	unsigned char m_data[0x1C0];
};

class Rva0024613CMember
{
public:
	Rva0024613CMember();
	~Rva0024613CMember();

private:
	unsigned char m_data[0x0C];
};

struct EmptyModuleDataBase
{
	EmptyModuleDataBase() {}
	~EmptyModuleDataBase();
};

class RandomSoundSelectorClientBehaviorModuleData : public EmptyModuleDataBase
{
public:
	RandomSoundSelectorClientBehaviorModuleData();

private:
	unsigned int m_vtable; // +0x00
	unsigned int m_pad04; // +0x04
	Rva00254FE4Member m_08; // +0x08 (0x1C0 bytes)
	Rva0024613CMember m_unitSpecificSounds; // +0x1C8
	float m_chance; // +0x1D4
	int m_voicePriority; // +0x1D8
	bool m_unknown1DC; // +0x1DC
	bool m_rerollOnEveryFrame; // +0x1DD
};

// ??0RandomSoundSelectorClientBehaviorModuleData@@QAE@XZ @0x25785C
RandomSoundSelectorClientBehaviorModuleData::RandomSoundSelectorClientBehaviorModuleData()
	: m_vtable(0x00BF42A8), m_08(), m_unitSpecificSounds()
{
	m_chance = 0.5f;
	m_voicePriority = 0;
	m_unknown1DC = false;
	m_rerollOnEveryFrame = true;
}
