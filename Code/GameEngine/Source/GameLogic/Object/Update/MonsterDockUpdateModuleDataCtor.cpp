// cl: /O1 /GX /MD /DNDEBUG
//
// ??0MonsterDockUpdateModuleData@@QAE@XZ, retail 0x004A1517, 59 bytes (EH):
// base call into the pinned DockUpdateModuleData 0x5896B0, single state-0
// store, compiler vtable store at +0 (pinned ??_7 at 0xC51DA8, slot0 is the
// ??_G at 0x4A1552 sitting right after the ctor), filter member at +0x10
// via the existing Rva003623E5Member ctor pin (no dtor, else a 2nd state),
// zero at +0x14 matching the DockableObjectFilter/DockedAnimationTime table.
// Devastate recipe: the virtual base dtor (declared-only, no code) is the
// sole unwindable. The owning factory at 0x0024EB2C (news 0x18) is the sole
// caller; the pool key plus Update ctor plus dtor sit in the cluster at
// 0x4A139A right where the proc ends. Row supersedes the ctor pin.
class DockUpdateModuleData
{
public:
	DockUpdateModuleData();
	virtual ~DockUpdateModuleData();

protected:
	unsigned char m_pad[0x0C];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();

	unsigned char m_data[4];
};

class MonsterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	MonsterDockUpdateModuleData();

	Rva003623E5Member m_filter;
	int m_dockedAnimationTime;
};

MonsterDockUpdateModuleData::MonsterDockUpdateModuleData()
	: DockUpdateModuleData()
{
	m_dockedAnimationTime = 0;
}
