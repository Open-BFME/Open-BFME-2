// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0DestroyEnvironmentUpdateModuleData@@QAE@XZ, retail 0x004AC615, 20 bytes.
// Frameless trivial ctor: the BFME1 DestroyEnvironmentUpdate.cpp donor models
// a trivial base (vptr at +0 plus an untouched word at +4) with a zeroed
// StartTime at +8 and DestructionTime at +0xC defaulting to 100 (see the rowed
// buildFieldParse proc holding the StartTime plus DestructionTime table at
// 0x00C54D28). The TU-local class keeps an explicit vtable slot (factory-TU
// precedent, so no vtable is emitted) and plain-data members, so the body
// statements reproduce retail order: integer zero, vtable literal 0x00C4ED70,
// then the 100 default (/O1 keeps the integer zero as the compact and form).
// Size 0x10 matches the 0x24F474 factory news.

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class DestroyEnvironmentUpdateModuleData
{
public:
	DestroyEnvironmentUpdateModuleData();

private:
	void *m_vtable; // +0
	int m_unused04; // +4
	int m_startTime; // +8
	int m_destructionTime; // +0xC
};

// ??0DestroyEnvironmentUpdateModuleData@@QAE@XZ @0x4AC615
DestroyEnvironmentUpdateModuleData::DestroyEnvironmentUpdateModuleData()
{
	m_startTime = 0;
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C4ED70));
	m_destructionTime = 100;
}
