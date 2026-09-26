// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1AttachUpdateModuleData@@UAE@XZ retail 0x00491AA0 48B.
// Dtor lane: ctor rowed at 0x00491968 in AttachUpdateModuleDataCtor.cpp vtable
// 0x00C4DD18 with slot0 ??_G at 0x00491A84. Destroys ObjectFilter at +8 through
// pinned 0x360D26 then restores Snapshot base vtable 0x00BBB554. Layout follows
// ctor TU (+0 vtable +4 unused +8 filter 4B +0xC parentStatus 16B +0x1C scanRange
// +0x20 flags +0x21 anchor +0x24 +0x28 +0x2C +0x30 FX +0x34 +0x38 +0x3C size 0x40
// matching factory 0x24D8D2 news 0x40). Shape follows BloodthirstyUpdateModuleDataDtor
// (TU-local Snapshot with inline BBB554 restore empty derived body novtable
// suppresses entry derived store retail lacks). Single tracked member gives
// and-state-0 exactly as retail. Caller is ??_G at 0x00491A87.

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

class __declspec(novtable) AttachUpdateModuleData : public Snapshot
{
public:
	virtual ~AttachUpdateModuleData();

private:
	int m_unused04; // +4
	Rva00360D26Member m_objectFilter; // +8
	unsigned long m_parentStatus[4]; // +0xC
	float m_scanRange; // +0x1C
	bool m_alwaysTeleport; // +0x20
	bool m_anchorToTopOfGeometry; // +0x21
	unsigned char m_pad22[2]; // +0x22
	int m_parentOwnerAttachmentEvaEvent; // +0x24
	int m_parentAllyAttachmentEvaEvent; // +0x28
	int m_parentEnemyAttachmentEvaEvent; // +0x2C
	void *m_attachFX; // +0x30
	int m_parentOwnerDiedEvaEvent; // +0x34
	int m_parentAllyDiedEvaEvent; // +0x38
	int m_parentEnemyDiedEvaEvent; // +0x3C
};

AttachUpdateModuleData::~AttachUpdateModuleData()
{
}
