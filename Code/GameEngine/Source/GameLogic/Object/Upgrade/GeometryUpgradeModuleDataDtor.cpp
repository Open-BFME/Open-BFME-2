// cl: /DNDEBUG /MD /EHsc /O1
// stlport
//
// ??1GeometryUpgradeModuleData@@UAE@XZ, retail 0x004B6F81, 114 bytes.
// ModuleData dtor: destroys the three AsciiStrings at +0x138 (state 4) then
// +0x134 (state 3) then +0x130 (state 2) through the folded StringBase<char>
// teardown at 0x00036410 then the two AsciiString vectors at +0x124 (state 1)
// then +0x118 (state 0) through the rowed 0x2CC70 body then restores the
// Snapshot base vtable 0x00BBB554. Empty derived body with no base call since
// the large 0x118 base dtor is inline. Layout from the rowed ctor 0x004B6EE2
// (base 0x118 via OpenContain 0x253487, vectors at +0x118/+0x124, strings at
// +0x130/+0x134/+0x138, size 0x13C via factory 0x00250642) and table 0x858918.
// Caller is the slot-0 ??_G at 0x004B6F65 (vtable 0x008589F0). Shape follows
// RemoveUpgradeUpgradeModuleDataDtor (TU-local Snapshot with inline
// BBB554-restoring dtor, novtable derived, empty body, vectors via 0x2CC70).
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

class __declspec(novtable) GeometryUpgradeModuleData : public Snapshot
{
public:
	virtual ~GeometryUpgradeModuleData();

private:
	_STL::vector<AsciiString> m_showGeometry; // +0x118
	_STL::vector<AsciiString> m_hideGeometry; // +0x124
	AsciiString m_wallBoundsMesh; // +0x130
	AsciiString m_rampMesh1; // +0x134
	AsciiString m_rampMesh2; // +0x138
};

GeometryUpgradeModuleData::~GeometryUpgradeModuleData()
{
}
