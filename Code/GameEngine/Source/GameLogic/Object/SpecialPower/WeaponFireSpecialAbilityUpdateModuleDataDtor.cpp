// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG
//
// ??1WeaponFireSpecialAbilityUpdateModuleData@@UAE@XZ, retail 0x00492806, 56 bytes.
// WeaponFireSpecialAbilityUpdate ModuleData dtor over the pinned Rva0044ECCE
// base (0x0044ECCE). Destroys the AsciiString at +0xC8 through the folded
// 0x00036410, then calls the base dtor. Layout follows the verified ctor at
// 0x004926CA in WeaponFireSpecialAbilityUpdateModuleDataCtor.cpp (base 0xC8,
// string +0xC8, scalars to 0xDC from factory 0x0024DB56, vtable 0x00C4E108).
// Called by the audited ??_G wrapper at 0x004927EA (slot 0 of 0x00C4E108).
// No derived vptr store in retail, so the derived class is novtable (cf.
// RiderChangeContainModuleDataDtor). BFME1 donor
// WeaponFireSpecialAbilityUpdateModuleDataDestructorThunk.cpp:36 proves the
// string-plus-base shape; retail followed.

#include "ascii_string.h"

class Rva0044ECCE
{
public:
	Rva0044ECCE();
	virtual ~Rva0044ECCE();

private:
	unsigned char m_pad[0xC8 - 4];
};

class __declspec(novtable) WeaponFireSpecialAbilityUpdateModuleData : public Rva0044ECCE
{
public:
	virtual ~WeaponFireSpecialAbilityUpdateModuleData();

private:
	AsciiString m_specialWeapon; // +0xC8
	int m_whichSpecialWeapon; // +0xCC
	bool m_skipContinue; // +0xD0
	unsigned char m_padD1[3];
	int m_busyForDuration; // +0xD4
	bool m_needLivingTargets; // +0xD8
	bool m_playWeaponPreFireFX; // +0xD9
	unsigned char m_padDA[2];
};

WeaponFireSpecialAbilityUpdateModuleData::~WeaponFireSpecialAbilityUpdateModuleData()
{
}
