// cl: /DNDEBUG /MD /EHsc /O1
// stlport
//
// ??1RemoveUpgradeUpgradeModuleData@@UAE@XZ, retail 0x004B8050, 69 bytes.
// ModuleData dtor: tears down two AsciiString vectors at +0x124 (state 1)
// then +0x118 (state 0) through the rowed 0x2CC70 body, then restores the
// Snapshot base vtable 0x00BBB554. Empty derived body with no base call since
// the large 0x118 base dtor is inline. Shape follows the landed
// ModelConditionSoundSelectorClientBehaviorModuleDataDtor/CivilianSpawnCollideModuleDataDtor (TU-local base
// with inline BBB554-restoring dtor, novtable derived, empty body) plus the
// Rampage vector precedent. Layout from the rowed ctor 0x004B7FF1 (base
// 0x118 via OpenContain 0x253487, vectors at +0x118/+0x124, bytes at
// +0x130/+0x131, size 0x134 via factory 0x0025082A) and table 0xC58EA0.
// Caller is the slot-0 ??_G at 0x004B8034 (vtable 0x58EF0).
#include <vector>

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x118 - 4];
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	AsciiString();
	~AsciiString();

private:
	void *m_data;
};

class __declspec(novtable) RemoveUpgradeUpgradeModuleData : public Snapshot
{
public:
	virtual ~RemoveUpgradeUpgradeModuleData();

private:
	_STL::vector<AsciiString> m_upgradeToRemove; // +0x118
	_STL::vector<AsciiString> m_upgradeGroupsToRemove; // +0x124
	unsigned char m_suppressEvaEventForRemoval; // +0x130
	unsigned char m_removeFromAllPlayerObjects; // +0x131
};

RemoveUpgradeUpgradeModuleData::~RemoveUpgradeUpgradeModuleData()
{
}
