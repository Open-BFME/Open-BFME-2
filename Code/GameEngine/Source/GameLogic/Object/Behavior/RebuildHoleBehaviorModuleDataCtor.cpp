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
extern float g_oneTenth;

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
	float holeHealth = g_oneTenth;
	m_vtable = reinterpret_cast<const void *>(0x00C49950);
	m_holeHealthRegen = holeHealth;
	*workerName &= 0;
}
