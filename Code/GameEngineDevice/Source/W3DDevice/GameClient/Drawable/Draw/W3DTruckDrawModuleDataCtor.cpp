// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??0W3DTruckDrawModuleData@@QAE@XZ, retail 0x000CB1C9, 197 bytes.
// W3DTruckDraw ModuleData ctor: calls the W3DModelDrawModuleData base ctor
// (pinned at 0xC8EEF, 7 subclass callers: 0x648FA/0x651D3/0x789E6/0xCAF1A/
// 0xCB1CC/0xCE6F7/0xD073A), installs vtable 0xBCC508, zeroes the 21 INI
// string slots at +0x188..+0x1D8, sets the four rotation scalars at
// +0x1DC..+0x1E8 to 1.0f (single pooled load) and PowerslideRotationAddition
// at +0x1EC to 0.0f. Layout is retail's own FieldParse table at 0xBCC358
// (Dust/DirtSpray/PowerslideSpray + 16 tire bones + 2 Bone2 spares +
// CabBone/TrailerBone strings, then CabRotationMultiplier/
// TrailerRotationMultiplier/RotationDamping/TireRotationMultiplier/
// PowerslideRotationAddition reals); BFME2 adds a second tire-bone set over
// the ZH donor (empty ctor), so the member list follows the table, not the
// donor. The factory at 0x64AF0 news 0x1F0 (= 0x188 base + 0x68) and is the
// sole caller of this ctor; the chained proc at 0xCB133 is rowed. The string
// members use the inline-empty AsciiString idiom (m_data = 0, no call), so
// the only out-of-line call is the base ctor and the body stays frameless
// with no EH states despite the 21 dtor-needing members.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	const char *m_data;
};

class W3DModelDrawModuleData
{
public:
	W3DModelDrawModuleData();
};

class W3DTruckDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DTruckDrawModuleData();

private:
	const void *m_vtable; // +0x00
	// Base occupies +0x04..+0x187 (0x188 bytes); the base ctor fills it.
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

// ??0W3DTruckDrawModuleData@@QAE@XZ @0xCB1C9
W3DTruckDrawModuleData::W3DTruckDrawModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BCC508))
	, m_cabRotationFactor(1.0f)
	, m_trailerRotationFactor(1.0f)
	, m_rotationDampingFactor(1.0f)
	, m_rotationSpeedMultiplier(1.0f)
	, m_powerslideRotationAddition(0.0f)
{
}
