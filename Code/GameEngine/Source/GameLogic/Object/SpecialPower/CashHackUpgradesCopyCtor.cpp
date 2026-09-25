// cl: /O1 /DNDEBUG /MD
//
// CashHackSpecialPowerModuleData::Upgrades copy helper, retail 0x003FA3AF,
// 36 bytes, sole caller the _STL::_Construct at 0x003FA3D3. Upgrades is the
// 8-byte UpgradeMoneyAmount pair (science word at +0, amount word at +4);
// the amount word rebuilds through the pinned 4-byte zeroing member
// (Rva003B31ADMember convention, same as PassiveAreaEffectBehaviorModuleData
// and AttributeModifierAuraUpdateModuleData) followed by |= of the source
// word, which is why the copy calls out instead of plain movs.

typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

// 4-byte zeroing member; default ctor is pinned to retail 0x003B31AD.
class Rva003B31ADMember
{
public:
	Rva003B31ADMember();

	int m_value;
};

class CashHackSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		int m_science; // +0, SCIENCE_INVALID (-1) when unset
		Rva003B31ADMember m_amount; // +4, money amount

		Upgrades(const Upgrades &src);
	};
};

// ??0Upgrades@CashHackSpecialPowerModuleData@@QAE@ABU12@@Z @0x003FA3AF
CashHackSpecialPowerModuleData::Upgrades::Upgrades(const Upgrades &src)
	: m_science(src.m_science)
	, m_amount()
{
	m_amount.m_value |= src.m_amount.m_value;
}

namespace _STL
{

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value)
{
	if (p)
		new (p) T1(value);
}

}

// ??$_Construct@UUpgrades@CashHackSpecialPowerModuleData@@U12@@_STL@@YAXPAUUpgrades@CashHackSpecialPowerModuleData@@ABU12@@Z @0x003FA3D3
template void _STL::_Construct(CashHackSpecialPowerModuleData::Upgrades *, const CashHackSpecialPowerModuleData::Upgrades &);
