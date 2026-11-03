// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0SpellRechargeModifierUpgradeModuleData@@QAE@XZ, retail 0x004B6011
// (93 bytes). EH derived ctor over the rowed Rva00253487Base base
// (0x00253487, size 0x118): the +0x118 vector<float> member constructs
// stores Percentage values (the field parser and upgrade consumers use float).
// Construction goes through the ICF-folded Vector_base at 0x00211E58 (explicit allocator in
// init, CreateCrateDie precedent), the compiler installs vtable 0x00C583E0
// automatically. The string constructor zeroes +0x128 before set assigns
// ">UNSPECIFIED<", and the body clears +0x124. Identity is the
// ModuleFactory registration under "SpellRechargeModifierUpgrade"
// (sole-caller data factory per the superseded ctor pin).

#include <vector>

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"

class SpellRechargeModifierUpgradeModuleData : public Rva00253487Base
{
public:
	SpellRechargeModifierUpgradeModuleData();
	virtual ~SpellRechargeModifierUpgradeModuleData(); // declared only; defined in SpellRechargeModifierUpgradeModuleDataDtor.cpp (0x004B608A)

private:
	_STL::vector<float> m_vec118;	// +0x118
	bool m_flag124;	// +0x124
	AsciiString m_str128;	// +0x128
};

SpellRechargeModifierUpgradeModuleData::SpellRechargeModifierUpgradeModuleData()
	: Rva00253487Base()
	, m_vec118(_STL::allocator<float>())
{
	m_str128.set(">UNSPECIFIED<");
	m_flag124 = false;
}
