// cl: /O1 /MD /GX /arch:SSE /DNDEBUG
//
// ??0WeaponFireSpecialAbilityUpdateModuleData@@QAE@XZ,
// retail 0x004926CA, 62 bytes. Ctor over table 0xBEF0A8 (SpecialWeapon
// at +0xC8, WhichSpecialWeapon at +0xCC, SkipContinue at +0xD0,
// BusyForDuration at +0xD4, NeedLivingTargets at +0xD8,
// PlayWeaponPreFireFX at +0xD9). Identity is the rowed poolkey 0x492685
// (WeaponFireSpecialAbilityUpdate) which ends exactly where this ctor
// begins, plus factory 0x24DB56 (sole caller) plus proc 0x24DB00 (same
// table, chained on the Rva0044EB54 base proc). Shape follows the
// Devastate-V5 precedent: pinned opaque base Rva0044EB54 (0x44EB54) with
// the vtable slot at +0 and the tail byte at +0xC4, derived zeros in
// table order with the base tail zeroed last. The specialWeapon pointer
// anchors the first zero below the vtable store (else the store sinks
// last) while the xor-zero setup still hoists above it.

class Rva0044EB54
{
public:
	Rva0044EB54();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0xC4 - 4]; // +4..+0xC3

protected:
	bool m_tailC4; // +0xC4, retail zeroes it last (purpose unknown)

private:
	unsigned char m_padC5[3]; // +0xC5..+0xC7
};

class WeaponFireSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	WeaponFireSpecialAbilityUpdateModuleData();

private:
	int m_specialWeapon; // +0xC8
	int m_whichSpecialWeapon; // +0xCC
	bool m_skipContinue; // +0xD0
	int m_busyForDuration; // +0xD4
	bool m_needLivingTargets; // +0xD8
	bool m_playWeaponPreFireFX; // +0xD9
};

// ??0WeaponFireSpecialAbilityUpdateModuleData@@QAE@XZ @0x4926CA
WeaponFireSpecialAbilityUpdateModuleData::WeaponFireSpecialAbilityUpdateModuleData()
{
	int *specialWeapon = &m_specialWeapon;
	m_vtable = reinterpret_cast<void *>(0x00C4E108);
	*specialWeapon = 0;
	m_whichSpecialWeapon = 0;
	m_skipContinue = false;
	m_busyForDuration = 0;
	m_needLivingTargets = false;
	m_playWeaponPreFireFX = false;
	m_tailC4 = false;
}
