// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0HeightDieUpdateModuleData@@QAE@XZ, retail 0x0048FC75, 44 bytes.
// Frameless store-only ctor over the Height table 0xC4CFC8 (TargetHeight@8,
// TargetHeightIncludesStructures@C, OnlyWhenMovingDown@D,
// DestroyAttachedParticlesAtHeight@10, SnapToGroundOnDeath@14,
// InitialDelay@18). Identity is the table plus the rowed HeightDieUpdate
// poolkey 0x48FC5A ending exactly where this ctor begins plus factory
// 0x24D3B6 (news 0x1C, sole caller) plus rowed proc 0x48FCA1. Shape follows
// the ReflectDamage trivial-ctor precedent: flat TU-local class with
// explicit void*m_vtable (no virtuals, no vtable emission) plus plain-data
// members; body assignments in retail order; /O1 emits integer zeros as
// compact AND MOVs and /arch:SSE emits the float zero as xorps plus movss.
// Vtable 0x00C4ED70 is ICF-folded (DeletionUpdate/SlotToLock/ReflectDamage
// share); the -1.0f pool literal reproduces the DestroyAttachedParticles
// default.

class HeightDieUpdateModuleData
{
public:
	HeightDieUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4 (retail never stores it)
	float m_targetHeight; // +8
	bool m_targetHeightIncludesStructures; // +0xC
	bool m_onlyWhenMovingDown; // +0xD
	float m_destroyAttachedParticlesAtHeight; // +0x10
	bool m_snapToGroundOnDeath; // +0x14
	int m_initialDelay; // +0x18
};

// ??0HeightDieUpdateModuleData@@QAE@XZ @0x48FC75
HeightDieUpdateModuleData::HeightDieUpdateModuleData()
{
	m_targetHeight = 0.0f;
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_targetHeightIncludesStructures = false;
	m_onlyWhenMovingDown = false;
	m_destroyAttachedParticlesAtHeight = -1.0f;
	m_snapToGroundOnDeath = false;
	m_initialDelay = 0;
}
