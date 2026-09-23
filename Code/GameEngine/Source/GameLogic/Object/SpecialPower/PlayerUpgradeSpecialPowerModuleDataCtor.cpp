// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0PlayerUpgradeSpecialPowerModuleData@@QAE@XZ, retail 0x004C7D68, 80 bytes.
// PlayerUpgrade data ctor over the pinned Rva004930A0 base (0x4930A0, 0x7C
// bytes): installs vtable 0x00C5E1C0 via the ??_7 pin, constructs the
// UpgradeName string list at +0x7C through the ICF-folded Vector_base at
// 0x00211E58, then clears the list through the rowed
// vector<AsciiString>::erase at 0x002CCFC. Table 0x00C5E23C carries the
// single UpgradeName field at +0x7C; factory 0x25253B news 0x88 (sole
// caller); pool key 0x4C7C4C. Row supersedes the ctor pin. Recipe:
// reference-spelled erase through a named vector reference binds the list
// in esi with this in edi (body-first binding inverts the standard homing);
// virtual base plus virtual derived with declared-only dtors (no code) arm
// the two EH states with the derived vtable store compiler-emitted mid-init.

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
	_STL::vector<AsciiString> m_upgradeNames;	// +0x7C UpgradeName
};

// ??0PlayerUpgradeSpecialPowerModuleData@@QAE@XZ @0x4C7D68
PlayerUpgradeSpecialPowerModuleData::PlayerUpgradeSpecialPowerModuleData()
	: Rva004930A0()
{
	_STL::vector<AsciiString> &names = m_upgradeNames;
	names.erase(names.begin(), names.end());
}
