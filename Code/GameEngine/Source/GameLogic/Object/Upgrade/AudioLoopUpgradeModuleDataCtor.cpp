// cl: /O1 /GX /DNDEBUG /MD
//
// ??0AudioLoopUpgradeModuleData@@QAE@XZ, retail 0x004B7C00, 76 bytes.
// Audio-side upgrade ModuleData: vtable 0x00C58CF8, size 0x154 (factory
// 0x250798 news 0x154, sole caller). Members: sound string at +0x08,
// kill-after at +0x0C, kill-on-death at +0x10, Rva0025342C member at +0x14
// (0x110 bytes, via rowed construct 0x25342C), DieMuxData at +0x124 (via
// rowed init 0x4CE534). Shape follows AttributeModifierAuraUpdateModuleData
// (explicit vtable plus empty base plus string member).

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_pad[0x110];
};

class DieMuxData
{
public:
	DieMuxData *init();

private:
	unsigned char m_pad[0x30];
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase();

private:
	void *m_data;
};

typedef StringBase<char> AsciiString;

class UpdateBase
{
public:
	UpdateBase() {}
	~UpdateBase();
};

class AudioLoopUpgradeModuleData : public UpdateBase
{
public:
	AudioLoopUpgradeModuleData();
	~AudioLoopUpgradeModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	AsciiString m_soundToPlay; // +0x08
	int m_killAfterMS; // +0x0C
	bool m_killOnDeath; // +0x10
	unsigned char m_pad11[3];
	Rva0025342CMember m_member14; // +0x14
	DieMuxData m_die124; // +0x124
};

// ??0AudioLoopUpgradeModuleData@@QAE@XZ @0x004B7C00
AudioLoopUpgradeModuleData::AudioLoopUpgradeModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C58CF8))
	, m_soundToPlay()
{
	m_killAfterMS = 0;
	m_killOnDeath = true;
	m_member14.construct();
	m_die124.init();
}
