// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0StrafeAreaUpdateModuleData@@QAE@XZ, retail 0x003A4E5A, 117 bytes.
//
// The module-data half of StrafeAreaUpdate: vtable immediate 0x00C1B268
// modelled as an explicit first member (ToppleUpdateModuleDataCtor
// precedent, so no vtable is emitted and no dtor row is owed), an
// uninitialised word at +0x04 retail never stores, the WeaponName string at
// +0x08, the four sweep reals at +0x0C/+0x10/+0x14/+0x18 (150.0, 0.4, 100.0,
// 50.0) and a trailing zero real at +0x1C. Field identity is retail's own
// INI table at RVA 0x81B1F8 (VA 0xC1B1F8, landed buildFieldParse row:
// WeaponName, StrafeAreaRadius, Sweepfrequency, SweepAmplitude, Slope). The
// string clears through the rowed 0x36410 clear fold (Topple precedent:
// inline default ctor plus declared-only clear and dtor). The empty
// UpdateModuleData base (inline-empty ctor plus declared-only dtor) is
// load-bearing for the EH state machine: it advances the state to 0 with no
// emitted code, so the member init is bracketed by state 0/1 exactly as
// retail. Body order follows retail.

typedef int Int;

#define NULL 0

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class StrafeAreaUpdateModuleData : public UpdateModuleData
{
public:
	StrafeAreaUpdateModuleData();

private:
	const void *m_vtable;				// +0
	unsigned int m_unused04;			// +4
	AsciiString m_weaponName;			// +0x08
	float m_strafeAreaRadius;			// +0x0C
	float m_sweepFrequency;			// +0x10
	float m_sweepAmplitude;			// +0x14
	float m_slope;				// +0x18
	float m_unk1C;				// +0x1C
};

StrafeAreaUpdateModuleData::StrafeAreaUpdateModuleData()
	: m_vtable( reinterpret_cast<const void *>(0x00C1B268) )
	, m_weaponName()
{
	m_strafeAreaRadius = 150.0f;
	m_sweepFrequency = 0.4f;
	m_sweepAmplitude = 100.0f;
	m_slope = 50.0f;
	m_unk1C = 0.0f;
	m_weaponName.clear();
}
