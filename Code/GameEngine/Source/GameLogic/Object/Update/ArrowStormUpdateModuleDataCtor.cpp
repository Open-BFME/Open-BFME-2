// cl: /DNDEBUG /MD
//
// ??0ArrowStormUpdateModuleData@@QAE@XZ, retail 0x00490639, 64 bytes.
// ModuleData ctor over the canonical SpecialAbilityUpdateModuleData base (0x44EB54,
// 0xC8 bytes). +0xC8 WeaponTemplate is an AsciiString: the destructor 0x00490695
// releases it through 0x00036410. With that member type the compiler installs the
// class's own vftable (retail 0x00C4D5A0, 31 ModuleData slots) right after the base
// ctor, as retail does, then zeroes the string, sets ShotsPerTarget/ShotsPerBurst/
// MaxShots at +0xD0/+0xD4/+0xD8 to 1, TargetRadius at +0xCC to 0 and
// CanShootEmptyGround at +0xDC to false. Table 0x00BEEE08 proves the six fields;
// factory 0x24D601 (news 0xE0, sole caller) proves the class size.

class MultiIniFieldParse;
struct FieldParse;

#include "../../../../Include/Common/INI/FieldParse.h"

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class ArrowStormUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	ArrowStormUpdateModuleData();
	virtual ~ArrowStormUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	AsciiString m_weaponTemplate;	// +0xC8 WeaponTemplate
	float m_targetRadius;	// +0xCC TargetRadius
	int m_shotsPerTarget;	// +0xD0 ShotsPerTarget
	int m_shotsPerBurst;	// +0xD4 ShotsPerBurst
	int m_maxShots;	// +0xD8 MaxShots
	bool m_canShootEmptyGround;	// +0xDC CanShootEmptyGround
	unsigned char m_padDD[3];	// +0xDD pad to the 0xE0 factory size
};

// ??0ArrowStormUpdateModuleData@@QAE@XZ @0x00490639
ArrowStormUpdateModuleData::ArrowStormUpdateModuleData()
	: m_targetRadius(0.0f),
	  m_shotsPerTarget(1),
	  m_shotsPerBurst(1),
	  m_maxShots(1),
	  m_canShootEmptyGround(false)
{
}
