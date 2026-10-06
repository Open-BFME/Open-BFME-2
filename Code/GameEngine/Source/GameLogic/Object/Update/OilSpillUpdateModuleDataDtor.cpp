// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /Oy-
//
// ??1OilSpillUpdateModuleData@@UAE@XZ, retail 0x0048C191, 74 bytes.
// Virtual dtor for the rowed ctor 0x0048C16C in OilSpillUpdateModuleDataCtor.cpp
// (vtable 0x00C4C2F8, slot0 deleting dtor 0x0048C1DB calls this at 0x0048C1DE).
// Shape follows DamageFieldUpdateModuleDataDtor (same FireWeaponUpdateModuleData
// base rowed 0x48BC46 plus AsciiString teardown via the folded 0x36410 body where
// the AsciiString pin shares the address with the StringBase<char> pin retail
// calls): restores the own vtable 0x00C4C2F8, destroys IgnitionWeaponName at
// +0x14 (state 1) then BreadcrumbName at +0x10 (state 0), then the base.
// Layout from the rowed ctor TU (base 0x10 plus BreadcrumbName +0x10 plus
// IgnitionWeaponName +0x14 plus IgnitionWeaponSpacing +0x18 plus OilSpillFX
// +0x1C, INI table 0x00C4C2A8, factory 0x24CFDF news 0x20). Unlike DamageField
// retail HAS the derived store so no novtable. Empty derived body.

class FireWeaponUpdateModuleData
{
public:
	FireWeaponUpdateModuleData();
	virtual ~FireWeaponUpdateModuleData();

private:
	unsigned char m_pad[0x10 - 4];
};

#include "ascii_string.h"

class OilSpillUpdateModuleData : public FireWeaponUpdateModuleData
{
public:
	virtual ~OilSpillUpdateModuleData();

private:
	AsciiString m_breadcrumbName; // +0x10
	AsciiString m_ignitionWeaponName; // +0x14
	float m_ignitionWeaponSpacing; // +0x18
	int m_oilSpillFX; // +0x1C
};

OilSpillUpdateModuleData::~OilSpillUpdateModuleData()
{
}
