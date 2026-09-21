// ??0WeaponFireSpecialAbilityUpdateModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-21
// cl: /O1 /MD /GX /arch:SSE /DNDEBUG
//
// ??0WeaponFireSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x004926CA,
// 62 bytes. Ctor over table 0xBEF0A8 (SpecialWeapon@C8, WhichSpecialWeapon
// @CC, SkipContinue@D0, BusyForDuration@D4, NeedLivingTargets@D8,
// PlayWeaponPreFireFX@D9). Identity is the rowed poolkey 0x492685
// (WeaponFireSpecialAbilityUpdate), which ends exactly where this ctor
// begins, plus factory 0x24DB56 (sole caller) plus proc 0x24DB00 (same
// table, chained on the Rva0044EB54 base proc). Shape follows the
// Devastate-V5/TerrainResource precedent: virtual base (declared-only
// virtual dtor, sole unwindable is none here since frameless) plus
// virtual derived with declared-only virtual dtor and NO source vtable
// store; the compiler emits the store in position, resolving through the
// ??_7 pin at the true vtable 0x00C4E108 (slot0 is the scalar-deleting
// dtor 0x4927EA calling dtor 0x492806 plus ??3). The +0xC4 byte has no
// table field; retail zeroes it last, modeled as a base-tail member.

class Rva0044EB54
{
public:
	Rva0044EB54();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0xC4 - 4]; // +4..+0xC3

protected:
	bool m_tailC4; // +0xC4, retail zeroes it here (purpose unknown)

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

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ??0WeaponFireSpecialAbilityUpdateModuleData@@QAE@XZ @0x4926CA
WeaponFireSpecialAbilityUpdateModuleData::WeaponFireSpecialAbilityUpdateModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00C4E108);
	_ReadWriteBarrier();
	m_specialWeapon = 0;
	m_whichSpecialWeapon = 0;
	m_skipContinue = false;
	m_busyForDuration = 0;
	m_needLivingTargets = false;
	m_playWeaponPreFireFX = false;
	m_tailC4 = false;
}
