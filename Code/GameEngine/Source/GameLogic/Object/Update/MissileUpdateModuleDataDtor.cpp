// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1MissileUpdateModuleData@@UAE@XZ, retail 0x004A7869, 51 bytes.
// MissileUpdateModuleData destructor: destroys the exhaust AsciiString at
// +0x11C through the pinned StringBase dtor 0x00036410 (state 0) then
// restores the Snapshot base vtable 0x00BBB554. Layout from the rowed ctor
// 0x004A77B8 (size 0x120 via factory 0x0024EFA0, exhaust string at +0x11C,
// table 0x00C53470) and the rowed FriendNew TU (vptr plus 0x11C pad).
// Own vtable 0x00853668 installed by the ctor. Caller is the slot-0 ??_G at
// 0x004A784D. Shape follows CreateObjectDieModuleDataDtor (TU-local Snapshot
// with inline BBB554-restoring dtor plus novtable derived suppressing the
// entry store retail lacks plus single string member).

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

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class __declspec(novtable) MissileUpdateModuleData : public Snapshot
{
public:
	virtual ~MissileUpdateModuleData();

private:
	unsigned char m_pad04[0x11C - 4];
	AsciiString m_exhaust;
};

MissileUpdateModuleData::~MissileUpdateModuleData()
{
}
