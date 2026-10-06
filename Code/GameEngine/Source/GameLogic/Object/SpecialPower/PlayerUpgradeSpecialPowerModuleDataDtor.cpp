// cl: /Ireference/shims/bfme2_ascii /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1PlayerUpgradeSpecialPowerModuleData@@UAE@XZ, retail 0x004C7DD4, 53 bytes.
// PlayerUpgrade data dtor over the rowed SpecialPowerModuleData base (0x0049334F, 0x7C
// bytes): destroys the UpgradeName string list at +0x7C through the rowed
// vector<AsciiString> dtor at 0x0002CC70, then calls the base dtor. Layout
// follows the verified ctor at 0x004C7D68 in
// PlayerUpgradeSpecialPowerModuleDataCtor.cpp (same base plus vector at +0x7C,
// table 0x00C5E23C, factory 0x0025253B news 0x88, vtable 0x00C5E1C0).
// Called by the audited ??_G wrapper at 0x004C7DB8 (slot 0 of 0x00C5E1C0).
// No derived vptr store in retail, so the derived class is novtable (cf.
// RiderChangeContainModuleDataDtor). No donor; identity is the ctor plus
// factory plus table.

#include <vector>

#include "ascii_string.h"

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_opaque[0x7C - 4];
};

class __declspec(novtable) PlayerUpgradeSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~PlayerUpgradeSpecialPowerModuleData();

private:
	_STL::vector<AsciiString> m_upgradeNames; // +0x7C UpgradeName
};

PlayerUpgradeSpecialPowerModuleData::~PlayerUpgradeSpecialPowerModuleData()
{
}
