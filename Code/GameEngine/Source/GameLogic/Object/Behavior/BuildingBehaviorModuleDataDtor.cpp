// cl: /O1 /GX /DNDEBUG /MD
//
// ??1BuildingBehaviorModuleData@@UAE@XZ, retail 0x004564E6, 58 bytes.
// ModuleData dtor: four-element window-name array at +0x08 torn down via
// ehvec ??_M (size 0xC count 4 array +8 element dtor DIR32-masked to retail
// 0x42CC70) then Snapshot base vtable 0x00BBB554 restored with no base call.
// Layout from rowed ctor 0x00456489 (vtable 0xC40798 table 0xC40748 factory
// 0x24ABAF news 0x38 gap +4 array +8). Shape follows BoneFX/LargeGroupBonus
// ModuleData dtors (TU-local Snapshot with inline BBB554 restore plus
// novtable derived suppressing the entry store retail lacks).

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	char *m_data;
};

class BuildingWindowName
{
public:
	BuildingWindowName() {}
	~BuildingWindowName() {}

private:
	AsciiString m_name;
	unsigned char m_pad[8];
};

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

class __declspec(novtable) BuildingBehaviorModuleData : public Snapshot
{
public:
	virtual ~BuildingBehaviorModuleData();

private:
	int m_unused04;
	BuildingWindowName m_windows[4];
};

// ??1BuildingBehaviorModuleData@@UAE@XZ @0x004564E6
BuildingBehaviorModuleData::~BuildingBehaviorModuleData()
{
}
