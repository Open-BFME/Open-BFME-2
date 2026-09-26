// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1PassiveAreaEffectBehaviorModuleData@@UAE@XZ, retail 0x00484EA9,
// 75 bytes. ModuleData dtor destroying the UpgradeRequired string at +0x24
// through the folded 0x36410 and the AllowFilter at +0x20 through the
// pinned 0x360D26 and the ModifierName vector at +0x14 through the rowed
// 0x2CC70 then restoring the Snapshot base vtable 0xBBB554. Member order
// vector plus filter plus string drives states 0 plus 1 plus 2 so teardown
// reads 2 plus 1 plus 0 exactly as retail. Shape follows
// LargeGroupBonusUpdateModuleDataDtor (TU-local Snapshot with inline
// BBB554-restoring dtor, novtable suppressing the entry derived-vtable
// store retail lacks). Identity is the ctor TU 0x484DF4 plus own vtable
// 0x00C4A490 plus table 0x00C4A388 plus factory 0x24C724 which news 0x38
// plus slot 0 deleting dtor 0x484E8D calling this body. BFME1 donor
// PassiveAreaEffectBehaviorModuleDataDestructorThunk.cpp proves virtual
// public UAE spelling.

#include <vector>

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

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class __declspec(novtable) PassiveAreaEffectBehaviorModuleData : public Snapshot
{
public:
	virtual ~PassiveAreaEffectBehaviorModuleData();

private:
	int m_unused04; // +0x04
	float m_effectRadius; // +0x08
	float m_healPercentPerSecond; // +0x0C
	int m_pingDelay; // +0x10
	_STL::vector<AsciiString> m_modifierName; // +0x14
	Rva00360D26Member m_allowFilter; // +0x20
	AsciiString m_upgradeRequired; // +0x24
	bool m_nonStackable; // +0x28
	unsigned char m_pad29[3];
	int m_antiCategories; // +0x2C trivial
	int m_antiFX; // +0x30
	int m_healFX; // +0x34
};

// ??1PassiveAreaEffectBehaviorModuleData@@UAE@XZ @0x00484EA9
PassiveAreaEffectBehaviorModuleData::~PassiveAreaEffectBehaviorModuleData()
{
}
