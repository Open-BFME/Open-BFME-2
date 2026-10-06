// cl: /Oy- /GX /DNDEBUG /MD
//
// ??0PickupStuffUpdateModuleData@@QAE@XZ, retail 0x00491E37, 80 bytes.
// ModuleData ctor over table 0xC4EC68 (ScanRate@8 plus ScanRange@C plus
// NeverHeal@10 plus AlwaysHeal@14). Identity is the rowed poolkey 0x491E1C
// in cluster plus rowed proc 0x491E87 plus factory 0x24D95B (news 0x18,
// sole caller). Shape: empty base (inline ctor plus declared-only dtor,
// single state with no transitions) plus explicit void*m_vtable (no
// virtuals, no vtable emission) plus body-order stores. The scan-range
// default loads through a named local first (load plus store split:
// the load stays above the state arm, the store lands after the bool),
// and the filter at +0x10 builds through the existing construct pin at
// 0x3623E5 (body-phase call, so its lea setup hoists above the vtable
// store while the call itself stays after the float store).


// Retail VA 0x00C4DDE0 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_00491F5A();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_00491F5A=??_GPickupStuffUpdateModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C4DDE0[] = {
	(const void *)&vfn_00491F5A,
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

class Rva003623E5Member
{
public:
	void construct();
};

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class PickupStuffUpdateModuleData : public EmptyBase
{
public:
	PickupStuffUpdateModuleData();

private:
	const void *m_vtable; // +0 (EBO: base contributes no size)
	unsigned int m_unused04; // +4
	bool m_skirmishAIOnly; // +8
	float m_scanRange; // +0xC
	Rva003623E5Member m_stuffToPickUp; // +0x10
	float m_scanIntervalSeconds; // +0x14
};

// ??0PickupStuffUpdateModuleData@@QAE@XZ @0x491E37
PickupStuffUpdateModuleData::PickupStuffUpdateModuleData()
{
	float scanRange = 200.0f;
	m_vtable = reinterpret_cast<const void *>(((unsigned int)vtbl_00C4DDE0));
	m_skirmishAIOnly = true;
	m_scanRange = scanRange;
	m_stuffToPickUp.construct();
	m_scanIntervalSeconds = 0.5f;
}
