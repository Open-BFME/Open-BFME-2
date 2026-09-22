// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??1W3DSupplyDrawModuleData@@UAE@XZ, retail 0x000CAF30, 62 bytes.
// W3DSupplyDraw ModuleData dtor: reinstalls vtable 0xBCC0D0, tears down the
// single INI string at +0x188 (SupplyBonePrefix through the folded
// AsciiString dtor at 0x36410) and calls the W3DModelDrawModuleData base
// dtor (pinned at 0xC8BE0, 5 draw-dtor callers: 0x652B8/0xC8DC6/0xCAF5C/
// 0xCB3E9/0xCE7A2). The vtable is implicit through a shared-vptr virtual
// base (the sibling ctor TU uses explicit-member modeling for its base
// call; each TU models independently). The base dtor pin carries the
// virtual UAE spelling; the AsciiString dtor resolves to the existing
// folded pin at 0x36410. File-unit companion to the landed ctor at 0xCAF17.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	void *m_data;
};

class W3DModelDrawModuleData
{
public:
	W3DModelDrawModuleData();
	virtual ~W3DModelDrawModuleData();
};

class W3DSupplyDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DSupplyDrawModuleData();
	virtual ~W3DSupplyDrawModuleData();

private:
	// Base (shared vptr at +0x00) occupies +0x00..+0x03; its real members
	// fill +0x04..+0x187 through the pinned base ctor/dtor.
	unsigned char m_basePad[0x188 - 4]; // +0x04
	AsciiString m_supplyBonePrefix; // +0x188
};

// ??1W3DSupplyDrawModuleData@@UAE@XZ @0xCAF30
W3DSupplyDrawModuleData::~W3DSupplyDrawModuleData()
{
}
