// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// ??0StealthDetectorUpdateModuleData@@QAE@XZ, retail 0x00255371, 84 bytes
// (frameless): compiler vtable store at +0 (pinned ??_7 at 0xBF3540, slot0
// is the ??_G at 0x256000), DetectionRate at +8, DetectionRange float at
// +0xC, inline-ctor AsciiStrings for the sound/name members, two 0x1C
// KindOf members at +0x30/+0x4C via the existing Rva0024C7B3 pin, trailing
// bytes plus RequiredUpgrade in the body. The owning factory at 0x002553C5
// (news 0x70) is the sole caller; the table at 0xC52188 is DetectionRate-led
// with ExtraRequiredKindOf at +0x30 and ExtraForbiddenKindOf at +0x4C. Row
// supersedes the ctor pin.
class AsciiString
{
public:
	AsciiString() : m_data(0) {}

private:
	void *m_data;
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

class StealthDetectorUpdateModuleData
{
public:
	StealthDetectorUpdateModuleData();
	virtual ~StealthDetectorUpdateModuleData();

	int m_unused04;
	int m_detectionRate;
	float m_detectionRange;
	bool m_initiallyDisabled;
	AsciiString m_pingSound;
	AsciiString m_loudPingSound;
	AsciiString m_beaconParticleSysName;
	AsciiString m_particleSysName;
	AsciiString m_brightParticleSysName;
	AsciiString m_gridParticleSysName;
	AsciiString m_particleSysBone;
	Rva0024C7B3Member m_extraRequiredKindOf;
	Rva0024C7B3Member m_extraForbiddenKindOf;
	bool m_canDetectWhileGarrisoned;
	bool m_canDetectWhileContained;
	bool m_cancelOneRingEffect;
	int m_requiredUpgrade;
};

StealthDetectorUpdateModuleData::StealthDetectorUpdateModuleData()
	: m_detectionRate(1)
	, m_detectionRange(0.0f)
	, m_initiallyDisabled(false)
{
	m_canDetectWhileGarrisoned = false;
	m_canDetectWhileContained = false;
	m_cancelOneRingEffect = false;
	m_requiredUpgrade = 0;
}
