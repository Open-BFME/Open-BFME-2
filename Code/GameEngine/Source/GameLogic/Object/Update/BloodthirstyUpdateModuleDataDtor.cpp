// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1BloodthirstyUpdateModuleData@@UAE@XZ, retail 0x0044E331, 67 bytes.
// BloodthirstyUpdateModuleData destructor (ctor rowed at 0x0044E2AC in
// BloodthirstyUpdateModuleDataCtor.cpp, vtable 0x0083F160 with slot 0 ??_G
// at 0x0044E315).
//
// Destroys the sacrifice-filter member at +0x08 through the pinned 0x360D26
// body, releases the +0x14 holder through the rowed Release_Ref at 0x50ED3
// when non-null, then restores the Snapshot base vtable 0x00BBB554. Layout
// follows the ctor TU (+0 vtable, +4 unused, +8 filter 4B, +0xC float,
// +0x10 voice index, +0x14 holder pointer). Shape follows
// FlammableUpdateModuleDataDtor / LargeGroupBonusUpdateModuleDataDtor
// (TU-local Snapshot with inline BBB554-restoring dtor, empty derived body,
// novtable suppresses the entry derived-vtable store retail lacks).

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

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct VoiceHolder
{
	~VoiceHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class __declspec(novtable) BloodthirstyUpdateModuleData : public Snapshot
{
public:
	virtual ~BloodthirstyUpdateModuleData();

private:
	int m_unused04; // +4
	Rva00360D26Member m_sacrificeFilter; // +8
	float m_experienceModifier; // +0xC
	int m_voiceIndex; // +0x10, -1
	VoiceHolder m_voiceHolder; // +0x14
};

BloodthirstyUpdateModuleData::~BloodthirstyUpdateModuleData()
{
}
