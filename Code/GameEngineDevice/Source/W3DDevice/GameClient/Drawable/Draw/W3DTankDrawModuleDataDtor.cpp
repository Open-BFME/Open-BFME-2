// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??1W3DTankDrawModuleData@@UAE@XZ, retail 0x000CE764, 80 bytes.
// W3DTankDraw ModuleData dtor: reinstalls vtable 0xBCCB58, tears down the
// two INI strings in reverse order (+0x18C TreadDebrisRight at state 1,
// +0x188 TreadDebrisLeft at state 0, through the folded AsciiString dtor at
// 0x36410) and calls the W3DModelDrawModuleData base dtor (pinned at
// 0xC8BE0). Implicit vtable through a shared-vptr virtual base, same
// modeling as the landed W3DSupplyDrawModuleData dtor; the AsciiString dtor
// resolves to the existing folded pin at 0x36410. File-unit companion to
// the banked Tank ctor at 0xCE6E6 (0.9 partial: push-lea order + missing
// mov-state-1) and the rowed proc/factory.

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

class W3DTankDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DTankDrawModuleData();
	virtual ~W3DTankDrawModuleData();

private:
	// Base (shared vptr at +0x00) occupies +0x00..+0x03; its real members
	// fill +0x04..+0x187 through the pinned base ctor/dtor.
	unsigned char m_basePad[0x188 - 4]; // +0x04
	AsciiString m_treadDebrisLeft; // +0x188
	AsciiString m_treadDebrisRight; // +0x18C
	float m_treadAnimationRate; // +0x190
	float m_treadPivotSpeedFraction; // +0x194
	float m_treadDriveSpeedFraction; // +0x198
};

// ??1W3DTankDrawModuleData@@UAE@XZ @0xCE764
W3DTankDrawModuleData::~W3DTankDrawModuleData()
{
}
