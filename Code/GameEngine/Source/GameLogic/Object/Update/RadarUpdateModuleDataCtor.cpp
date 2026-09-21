// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0RadarUpdateModuleData@@QAE@XZ, retail 0x003ECC80, 17 bytes.
// Frameless trivial ctor: the folded-trivial vtable literal 0x00C4ED70
// (shared by many ModuleData classes, so the install alone proves nothing)
// plus the xorps float zero of the RadarExtendTime word at +8. Size 0xC
// matches the 0x254291 factory news. The body is a shared fold: the
// DefaultRadius factory 0x24FC08 (proc 0x3ECC91 holding the DefaultRadius
// table) runs this same body; the row proves this spelling while the
// DefaultRadius share is documented in the factory note (Defector
// precedent: rowed as one class, sibling shares the fold). Class identity
// is the rowed RadarUpdateModuleData::buildFieldParse proc (single
// RadarExtendTime field at +8) pushed as the 0x254291 factory immediate.

class RadarUpdateModuleData
{
public:
	RadarUpdateModuleData();

private:
	void *m_vtable; // +0 (explicit; no virtuals declared, so no vtable is emitted)
	int m_unused04; // +4
	float m_radarExtendTime; // +8
};

// ??0RadarUpdateModuleData@@QAE@XZ @0x3ECC80
RadarUpdateModuleData::RadarUpdateModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00C4ED70);
	m_radarExtendTime = 0.0f;
}
