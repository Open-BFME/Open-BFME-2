// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0LightPulseFXNugget@@QAE@XZ 82B @0x1E0321: no-arg ctor called by
// LightPulseFXNugget::parse (0x001E1421) for the LightPulse FXList keyword;
// class name from BFME1. Member names and offsets from the retail FieldParse
// table 0x00BDCBD8 (Color@0x148 Radius@0x154 RadiusAsPercent@0x158
// IncreaseTime@0x15C DecreaseTime@0x160) and the BFME1 donor (m_color RGB
// plus m_radius plus m_boundingCirclePct plus m_increaseFrames plus
// m_decreaseFrames plus FXNugget::m_field04 type id 4).
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

struct LightPulseColor
{
	float red; // +0x148
	float green; // +0x14C
	float blue; // +0x150
};

class LightPulseFXNugget : public Rva001DFEAABase
{
public:
	LightPulseFXNugget();
private:
	LightPulseColor m_color; // +0x148
	float m_radius; // +0x154
	float m_boundingCirclePct; // +0x158
	int m_increaseFrames; // +0x15C
	int m_decreaseFrames; // +0x160
};

// ??0LightPulseFXNugget@@QAE@XZ
LightPulseFXNugget::LightPulseFXNugget()
{
	*(unsigned int *)this = 0x00BDD790;
	m_increaseFrames = 0;
	m_decreaseFrames = 0;
	m_radius = 0.0f;
	m_boundingCirclePct = 0.0f;
	m_color.blue = 0.0f;
	m_color.green = 0.0f;
	m_color.red = 0.0f;
	m_field04 = 4;
}
