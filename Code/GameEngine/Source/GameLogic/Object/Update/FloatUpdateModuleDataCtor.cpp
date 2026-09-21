// cl: /O1 /MD /DNDEBUG
//
// ??0FloatUpdateModuleData@@QAE@XZ, retail 0x0048D7A6,
// 12 bytes. Frameless store-only ctor over table 0xC4C7A4 (Enabled@8).
// Identity is the rowed poolkey 0x48D761 (FloatUpdate), which ends
// exactly where this ctor begins, plus factory 0x24D0F1 (news 0xC, sole
// caller) plus proc 0x48D7B3 (same table). Shape follows the
// SlaveWatcher trivial-ctor precedent: flat TU-local class with explicit
// void*m_vtable (no virtuals, no vtable emission) plus plain-data
// members; body assignments in retail order. Vtable 0x00C4ED70 is
// ICF-folded, so the install proves nothing by itself; table plus size
// plus stores do.

class FloatUpdateModuleData
{
public:
	FloatUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	bool m_enabled; // +8
};

// ??0FloatUpdateModuleData@@QAE@XZ @0x48D7A6
FloatUpdateModuleData::FloatUpdateModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_enabled = false;
}
