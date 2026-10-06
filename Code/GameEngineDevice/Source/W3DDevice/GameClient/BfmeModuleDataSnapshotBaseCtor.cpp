// cl: /DNDEBUG /MD
//
// ??0BfmeModuleDataSnapshotBase@@QAE@XZ, retail 0x0011646E, 13 bytes.
// Base ctor installing vtable 0x00BCFB24 and zeroing +0x04. Evidence:
// sole matched caller LookupTablePostEffect ctor 0x111B87 constructs this
// base; vtable 0x00BCFB24.

extern const void *const g_00BCFB24[];

class BfmeModuleDataSnapshotBase
{
public:
	BfmeModuleDataSnapshotBase();
private:
	unsigned char m_pad[4];
	unsigned char m_04;
};

BfmeModuleDataSnapshotBase::BfmeModuleDataSnapshotBase()
{
	*(const void **)this = g_00BCFB24;
	m_04 = 0;
}
