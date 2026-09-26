// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1EntEnragedUpdateModuleData@@UAE@XZ, retail 0x004B2722, 63 bytes.
// Virtual dtor over vtable 0x00856980 (slot 0 deleting dtor at 0x004B2706).
// Layout from ctor 0x004B249D (news 0x30). Destruction reverse: +0x1C/+0x18
// filters via pinned 0x00360D26 (states 1/0), then Snapshot base restores
// 0x00BBB554. No entry vtable store, so novtable.
// BloodthirstyUpdateModuleDataDtor precedent.

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class __declspec(novtable) EntEnragedUpdateModuleData : public Snapshot
{
public:
	virtual ~EntEnragedUpdateModuleData();

private:
	int m_baseTail;
	int m_scanDelayTime;
	int m_enragedTime;
	int m_timeUntilCanRageAgain;
	float m_scanDistance;
	Rva00360D26Member m_hatedFilter;
	Rva00360D26Member m_friendlyFilter;
	int m_transitionTime;
	int m_transitionFX;
	int m_onBuffFX;
	int m_offBuffFX;
};

EntEnragedUpdateModuleData::~EntEnragedUpdateModuleData()
{
}
