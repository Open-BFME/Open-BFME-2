// cl: /O1 /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0SpellRechargeModifierUpgradeModuleData@@QAE@XZ, retail 0x004B6011
// (93 bytes). EH derived ctor over the rowed OpenContainModuleData base
// (0x00253487, size 0x118): the +0x118 vector<AsciiString> member constructs
// through the ICF-folded Vector_base at 0x00211E58 (explicit allocator in
// init, CreateCrateDie precedent), the compiler installs vtable 0x00C583E0
// automatically, then the body zeroes the +0x128 string data word
// explicitly, sets it from ">UNSPECIFIED<" through the AsciiString set
// alias pin at 0x000055F5, and clears the +0x124 flag. Two unwind states
// (base plus members) count for the throwing calls. AsciiString spelling
// follows the SpawnBehaviorModuleDataCtor precedent (minus the inline
// nullary, so the zero stays an explicit body store). Identity is the
// ModuleFactory registration under "SpellRechargeModifierUpgrade"
// (sole-caller data factory per the superseded ctor pin).

#include <vector>

class AsciiString
{
public:
	void set(const char *text);
	~AsciiString();

public:
	void *m_data;	// public so the body zeroes it explicitly (retail and-idiom)
};

class OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

private:
	unsigned char m_opaque[0x118 - 4];
};

class SpellRechargeModifierUpgradeModuleData : public OpenContainModuleData
{
public:
	SpellRechargeModifierUpgradeModuleData();

private:
	_STL::vector<AsciiString> m_vec118;	// +0x118
	bool m_flag124;	// +0x124
	AsciiString m_str128;	// +0x128
};

SpellRechargeModifierUpgradeModuleData::SpellRechargeModifierUpgradeModuleData()
	: OpenContainModuleData()
	, m_vec118(_STL::allocator<AsciiString>())
{
	m_str128.m_data = 0;
	m_str128.set(">UNSPECIFIED<");
	m_flag124 = false;
}
