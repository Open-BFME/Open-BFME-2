// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??1W3DTruckDrawModuleData@@UAE@XZ, retail 0x000CB28E, 269 bytes.
// W3DTruckDraw ModuleData dtor: reinstalls vtable 0xBCC508, tears down the
// 21 INI strings in reverse order (+0x1D8 TrailerBone down to +0x188 Dust
// at states 0x14..0, through the folded AsciiString dtor at 0x36410) and
// calls the W3DModelDrawModuleData base dtor (pinned at 0xC8BE0). Implicit
// vtable through a shared-vptr virtual base, same modeling as the landed
// Supply/Tank draw dtors; the AsciiString dtor resolves to the existing
// folded pin at 0x36410. Member names follow retail's FieldParse table at
// 0xBCC358. File-unit companion to the landed ctor at 0xCB1C9.

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

class W3DTruckDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DTruckDrawModuleData();
	virtual ~W3DTruckDrawModuleData();

private:
	// Base (shared vptr at +0x00) occupies +0x00..+0x03; its real members
	// fill +0x04..+0x187 through the pinned base ctor/dtor.
	unsigned char m_basePad[0x188 - 4]; // +0x04
	AsciiString m_dustEffectName; // +0x188
	AsciiString m_dirtEffectName; // +0x18C
	AsciiString m_powerslideEffectName; // +0x190
	AsciiString m_frontLeftTireBoneName; // +0x194
	AsciiString m_frontRightTireBoneName; // +0x198
	AsciiString m_rearLeftTireBoneName; // +0x19C
	AsciiString m_rearRightTireBoneName; // +0x1A0
	AsciiString m_midFrontLeftTireBoneName; // +0x1A4
	AsciiString m_midFrontRightTireBoneName; // +0x1A8
	AsciiString m_midRearLeftTireBoneName; // +0x1AC
	AsciiString m_midRearRightTireBoneName; // +0x1B0
	AsciiString m_midMidLeftTireBoneName; // +0x1B4
	AsciiString m_midMidRightTireBoneName; // +0x1B8
	AsciiString m_frontLeftTireBoneName2; // +0x1BC
	AsciiString m_frontRightTireBoneName2; // +0x1C0
	AsciiString m_rearLeftTireBoneName2; // +0x1C4
	AsciiString m_rearRightTireBoneName2; // +0x1C8
	AsciiString m_midMidLeftTireBoneName2; // +0x1CC
	AsciiString m_midMidRightTireBoneName2; // +0x1D0
	AsciiString m_cabBoneName; // +0x1D4
	AsciiString m_trailerBoneName; // +0x1D8
	float m_cabRotationFactor; // +0x1DC
	float m_trailerRotationFactor; // +0x1E0
	float m_rotationDampingFactor; // +0x1E4
	float m_rotationSpeedMultiplier; // +0x1E8
	float m_powerslideRotationAddition; // +0x1EC
};

// ??1W3DTruckDrawModuleData@@UAE@XZ @0xCB28E
W3DTruckDrawModuleData::~W3DTruckDrawModuleData()
{
}
