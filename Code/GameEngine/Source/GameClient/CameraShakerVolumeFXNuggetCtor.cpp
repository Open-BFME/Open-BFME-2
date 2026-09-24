// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0CameraShakerVolumeFXNugget@@QAE@XZ 76B @0x1E0714: no-arg ctor called by
// CameraShakerVolumeFXNugget::parse (0x001E1595) for the CameraShakerVolume
// FXList keyword; class name from BFME1. Member names and offsets from the
// retail FieldParse table 0x00BDD040 (Radius@0x154 Duration_Seconds@0x158
// Amplitude_Degrees@0x15C) and the BFME1 donor (lower triple m_fieldB4/B8/BC
// plus FXNugget::m_field04 type id 5; BFME2 stores the lower triple as
// float-zero). Body order follows retail scheduling.
// Base 0x001DFEAA is a shared FXNugget-family base ctor; pinned opaquely.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
protected:
	unsigned int m_vtablePad; // +0, overwritten by the derived vtable store
	int m_field04; // +4, nugget type id (BFME1 FXNugget::m_field04)
	unsigned char m_pad[0x148 - 8];
};

class CameraShakerVolumeFXNugget : public Rva001DFEAABase
{
public:
	CameraShakerVolumeFXNugget();
private:
	float m_fieldB4; // +0x148, runtime state (BFME1 int, BFME2 float-zero)
	float m_fieldB8; // +0x14C, runtime state (BFME1 int, BFME2 float-zero)
	float m_fieldBC; // +0x150, runtime state (BFME1 int, BFME2 float-zero)
	float m_radius; // +0x154
	float m_durationSeconds; // +0x158
	float m_amplitudeDegrees; // +0x15C
};

// ??0CameraShakerVolumeFXNugget@@QAE@XZ
CameraShakerVolumeFXNugget::CameraShakerVolumeFXNugget()
{
	*(unsigned int *)this = 0x00BDD7CC;
	m_radius = 0.0f;
	m_durationSeconds = 0.0f;
	m_amplitudeDegrees = 0.0f;
	m_fieldB4 = 0.0f;
	m_fieldB8 = 0.0f;
	m_fieldBC = 0.0f;
	m_field04 = 5;
}
