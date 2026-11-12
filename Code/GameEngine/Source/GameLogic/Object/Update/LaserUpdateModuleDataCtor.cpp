// cl: /MD /DNDEBUG
// platformsdk
//
// ??0LaserUpdateModuleData@@QAE@XZ, retail 0x00363147,
// 31 bytes. Frameless store-only ctor over table 0xC17208
// (MuzzleParticleSystem@8, ParentFireBoneName@0xC, ParentFireBoneOnTurret@0x10,
// TargetParticleSystem@0x14, plus a trailing zero real at +0x18).
// Identity is the rowed poolkey 0x363102 (LaserUpdate), which ends exactly
// where this ctor begins, plus factory 0x24D55A (news 0x1C, sole caller)
// plus proc 0x363166 (same table). Shape follows the DualWeapon
// trivial-ctor precedent: flat TU-local class with explicit void*m_vtable
// (no virtuals, no vtable emission) plus plain-data members; body
// assignments in retail order; /arch:SSE emits the float zero as
// xorps/movss. Vtable 0x00C17120 is ICF-folded, so the install proves
// nothing by itself; table plus size plus stores do.

// Retail VA 0x00C17120 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
#include <windows.h>

extern "C" void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
extern "C" void __identifier("??1Coord2D@@QAE@XZ")();
extern "C" void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
extern "C" void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
extern "C" void __identifier("??_GLaserUpdateModuleData@@UAEPAXI@Z")();
extern "C" void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
extern "C" void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
extern "C" const void *const vtbl_00C17120[] = {
	(const void *)&__identifier("??_GLaserUpdateModuleData@@UAEPAXI@Z"),
	(const void *)&__identifier("??1Coord2D@@QAE@XZ"),
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
};

class LaserUpdateModuleData
{
public:
	LaserUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	void *m_muzzleParticleSystem; // +8
	void *m_parentFireBoneName; // +0xC
	bool m_parentFireBoneOnTurret; // +0x10
	void *m_targetParticleSystem; // +0x14
	float m_laserLifetime; // +0x18
};

// ??0LaserUpdateModuleData@@QAE@XZ @0x363147
LaserUpdateModuleData::LaserUpdateModuleData()
{
	m_vtable = reinterpret_cast<const void *>(((unsigned int)vtbl_00C17120));
	m_muzzleParticleSystem = NULL;
	m_parentFireBoneName = NULL;
	m_targetParticleSystem = NULL;
	m_parentFireBoneOnTurret = false;
	m_laserLifetime = 0.0f;
}
