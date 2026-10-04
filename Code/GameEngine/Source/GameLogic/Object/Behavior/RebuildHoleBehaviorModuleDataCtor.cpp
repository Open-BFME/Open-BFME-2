// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0RebuildHoleBehaviorModuleData@@QAE@XZ,
// retail 0x0048323E, 34 bytes. Frameless ModuleData ctor: the vtable literal
// 0x00C49950 stays an explicit first member (no virtuals declared, so no
// vtable is emitted and no dtor row is owed), the +0x04 word retail never
// stores, WorkerRespawnDelay at +0x08 zeroed via xorps/movss, HoleHealth at
// +0x0C from the shared 0.1f global, and WorkerObjectName at +0x10 cleared.
// Field identity is retail's own INI table at 0x00C49A10 (landed
// buildFieldParse row: WorkerObjectName plus WorkerRespawnDelay plus
// HoleHealthRegen%PerSecond) beside the rowed RebuildHoleBehavior pool key
// (0x4832D7); the 0x24C433 factory sole-calls this ctor. The holeName
// pointer anchors the and-zero below the vtable store (RebuildHoleExposeDie
// precedent: else it hoists above it); the temp splits the global load above
// the vtable store (else the health store sinks below it).

// Retail VA 0x00C49950 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_0048332E();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_0048332E=??_GRebuildHoleBehaviorModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C49950[] = {
	(const void *)&vfn_0048332E,
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

class RebuildHoleBehaviorModuleData
{
public:
	RebuildHoleBehaviorModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	float m_workerRespawnDelay;	// +0x08
	float m_holeHealthRegen;	// +0x0C
	int m_workerObjectName;		// +0x10 (name key data word)
};

// ??0RebuildHoleBehaviorModuleData@@QAE@XZ @0x48323E
RebuildHoleBehaviorModuleData::RebuildHoleBehaviorModuleData()
{
	int *workerName = &m_workerObjectName;
	m_workerRespawnDelay = 0.0f;
	float holeHealth = 0.1f;
	m_vtable = reinterpret_cast<const void *>(((unsigned int)vtbl_00C49950));
	m_holeHealthRegen = holeHealth;
	*workerName &= 0;
}
