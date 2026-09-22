// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??0W3DTankDrawModuleData@@QAE@XZ, retail 0x000CE6E6, 126 bytes.
// W3DTankDraw ModuleData ctor: runs the pinned W3DModelDrawModuleData base
// ctor, installs this TU's vtable through the ??_7 pin at 0x00BCCB58,
// initializes the two tread-debris strings from their literals through the
// rowed StringBase<char> const-char ctor at 0x00037BA0 (spelled through an
// inline AsciiString forwarder so the member-inits call it directly), and
// sets the three tread scalars (0.0f plus the 0.6f and 0.3f globals).
// Layout mirrors the landed W3DTankDrawModuleDataDtor TU exactly (shared
// vptr at +0, base pad +0x04..+0x187, strings +0x188/+0x18C, scalars
// +0x190/+0x194/+0x198); the W3DTruckDrawModuleDataCtor TU proves the
// family idiom. Virtual base plus virtual derived with declared-only dtors
// arm the two EH states with the derived vtable store mid-init; /arch:SSE
// keeps the float stores as xorps plus movss.

template <typename T>
class StringBase
{
	friend class AsciiString;

protected:
	~StringBase();

	void *m_data;

private:
	StringBase(const char *str);
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *str) : StringBase<char>(str) {}
	~AsciiString();
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
	// fill +0x04..+0x187 through the pinned base ctor.
	unsigned char m_basePad[0x188 - 4]; // +0x04
	AsciiString m_treadDebrisLeft; // +0x188
	AsciiString m_treadDebrisRight; // +0x18C
	float m_treadAnimationRate; // +0x190
	float m_treadPivotSpeedFraction; // +0x194
	float m_treadDriveSpeedFraction; // +0x198
};

// ??0W3DTankDrawModuleData@@QAE@XZ @0xCE6E6
W3DTankDrawModuleData::W3DTankDrawModuleData()
	: m_treadDebrisLeft("TrackDebrisDirtLeft")
	, m_treadDebrisRight("TrackDebrisDirtRight")
{
	// Body assignments (not mem-inits) keep the global-float loads as
	// movss pairs exactly as retail.
	m_treadAnimationRate = 0.0f;
	m_treadPivotSpeedFraction = *reinterpret_cast<volatile const float *>(0x00BC4DD0);
	m_treadDriveSpeedFraction = *reinterpret_cast<volatile const float *>(0x00BCCB3C);
}
