// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0AIGateUpdateModuleData@@QAE@XZ, retail 0x004B08C1, 22 bytes.
// Frameless trivial ctor: vtable literal 0x00C4ED70 (the folded trivial
// ModuleData vtable, also installed by DeletionUpdate plus SlotToLock plus
// ReflectDamage, so the install alone proves nothing) plus float zeros at
// +8/+0xC, matching the rowed buildFieldParse table (TriggerWidthX at +8,
// TriggerWidthY at +0xC). Size 0x10 matches the rowed 0x24FA64 factory news.
// The TU-local class keeps an explicit vtable slot (factory-TU precedent, so
// no vtable is emitted) plus an unstored +4 gap member (DemoTrap m_unused04
// precedent) plus the two floats; body order vtable then floats reproduces
// retail, with the ctor return-this homing placing mov eax,ecx after the
// hoisted xorps (probe-proven). Class identity is pool-key adjacency: the
// rowed AIGateUpdate pool key (0x4B087C, 69B) ends where this ctor begins.

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class AIGateUpdateModuleData
{
public:
	AIGateUpdateModuleData();

private:
	void *m_vtable; // +0
	int m_unused04; // +4
	float m_triggerWidthX; // +8
	float m_triggerWidthY; // +0xC
};

// ??0AIGateUpdateModuleData@@QAE@XZ @0x4B08C1
AIGateUpdateModuleData::AIGateUpdateModuleData()
{
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C4ED70));
	m_triggerWidthX = 0.0f;
	m_triggerWidthY = 0.0f;
}
