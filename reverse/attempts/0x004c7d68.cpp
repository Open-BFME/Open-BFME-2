// ??0PlayerUpgradeSpecialPowerModuleData@@QAE@XZ
// partial score=0.9 date=2026-09-23
// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0PlayerUpgradeSpecialPowerModuleData@@QAE@XZ, retail 0x004C7D68 (80 bytes).
// EH derived ctor over the pinned Rva004930A0 intermediate base (0x004930A0,
// size 0x7C): the base call builds the base, the +0x7C vector<AsciiString>
// member constructs through the ICF-folded Vector_base at 0x00211E58
// (allocator temp on ebp), the compiler installs vtable 0x00C5E1C0, and the
// body erases the whole range through the rowed vector<AsciiString>::erase
// at 0x0002CCFC. Two unwind states count the base and the vector for the
// throwing calls. AsciiString and flag spellings follow the
// SpawnBehaviorModuleDataCtor precedent. Identity is the ModuleFactory
// registration under "PlayerUpgradeSpecialPower" (sole-caller data factory
// per the superseded ctor pin).

#include <vector>

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class Rva004930A0
{
public:
	Rva004930A0();
	virtual ~Rva004930A0();

private:
	unsigned char m_opaque[0x7C - 4];
};

class PlayerUpgradeSpecialPowerModuleData : public Rva004930A0
{
public:
	PlayerUpgradeSpecialPowerModuleData();

private:
	_STL::vector<AsciiString> m_vec7C;	// +0x7C
};

PlayerUpgradeSpecialPowerModuleData::PlayerUpgradeSpecialPowerModuleData()
	: Rva004930A0()
{
	m_vec7C.erase(m_vec7C.begin(), m_vec7C.end());
}
