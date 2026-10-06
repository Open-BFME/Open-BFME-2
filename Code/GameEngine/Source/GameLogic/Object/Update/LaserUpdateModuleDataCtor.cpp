// cl: /MD /DNDEBUG
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
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_003631CC();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_003631CC=??_GLaserUpdateModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C17120[] = {
	(const void *)&vfn_003631CC,
	(const void *)&vfn_000B3FD0,
	(const void *)&vfn_00065212,
	(const void *)&vfn_0047A69C,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000B69A1,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_0050B5C6
};

#define NULL 0

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
	float m_unk18; // +0x18
};

// ??0LaserUpdateModuleData@@QAE@XZ @0x363147
LaserUpdateModuleData::LaserUpdateModuleData()
{
	m_vtable = reinterpret_cast<const void *>(((unsigned int)vtbl_00C17120));
	m_muzzleParticleSystem = NULL;
	m_parentFireBoneName = NULL;
	m_targetParticleSystem = NULL;
	m_parentFireBoneOnTurret = false;
	m_unk18 = 0.0f;
}
