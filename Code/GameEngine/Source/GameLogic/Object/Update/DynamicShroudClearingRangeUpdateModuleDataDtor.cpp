// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1DynamicShroudClearingRangeUpdateModuleData@@UAE@XZ, retail 0x0048B634,
// 48 bytes. ModuleData-side dtor completing the DynamicShroud file-unit
// (ctor rowed at 0x48B5C6 installs vtable 0xC4BEF8, factory 0x24CE44 news
// 0x5C, table 0xC4BE20). Destroys the RadiusDecalTemplate member at +0x28
// through the pinned 0xB6CF1 body (two-AsciiString teardown, same offset
// the ctor builds via rowed 0x330E5D), then restores the Snapshot base
// vtable 0xBBB554. Shape follows LargeGroupBonusUpdateModuleDataDtor
// (TU-local Snapshot with inline BBB554-restoring dtor, novtable
// suppresses the derived-vtable store retail lacks). Single tracked member
// gives state 0 exactly as retail; caller is the slot-0 deleting dtor at
// 0x48B618. BFME1 donor: open-bfme-1 DestructorThunk (dual-AsciiString at
// +0x28).

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

class Rva00B6CF1
{
public:
	virtual ~Rva00B6CF1();

private:
	unsigned char m_data[0x34];
};

class __declspec(novtable) DynamicShroudClearingRangeUpdateModuleData : public Snapshot
{
public:
	virtual ~DynamicShroudClearingRangeUpdateModuleData();

private:
	unsigned int m_unused04; // +0x04, unstored gap
	int m_shrinkDelay; // +0x08
	int m_shrinkTime; // +0x0C
	int m_growDelay; // +0x10
	int m_growTime; // +0x14
	float m_finalVision; // +0x18
	int m_changeInterval; // +0x1C
	int m_growInterval; // +0x20
	bool m_doSpySatFX; // +0x24
	unsigned char m_pad25[3];
	Rva00B6CF1 m_gridDecalTemplate; // +0x28
};

// ??1DynamicShroudClearingRangeUpdateModuleData@@UAE@XZ @0x0048B634
DynamicShroudClearingRangeUpdateModuleData::~DynamicShroudClearingRangeUpdateModuleData()
{
}
