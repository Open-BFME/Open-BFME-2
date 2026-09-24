// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0TintDrawableFXNugget@@QAE@XZ 82B @0x1E0986: no-arg ctor called by
// TintDrawableFXNugget::parse (0x001E1798) for the TintDrawable FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDD278 (Color@0x148 PreColorTime@0x154
// PostColorTime@0x158 SustainedColorTime@0x15C Frequency@0x160
// Amplitude@0x164). Color is an RGBColor set from -1 (white) via the rowed
// RGBColor::setFromInt; times are game-logic defaults; Frequency/Amplitude
// default to 1.0f.
// Base 0x001DFEAA is a shared FXNugget-family base ctor; pinned opaquely.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
protected:
	unsigned int m_vtablePad; // +0, overwritten by the derived vtable store
	int m_field04; // +4, nugget type id (unused here; retail stores none)
	unsigned char m_pad[0x148 - 8];
};

struct RGBColor
{
	void setFromInt(int color);
	float red;
	float green;
	float blue;
};

class TintDrawableFXNugget : public Rva001DFEAABase
{
public:
	TintDrawableFXNugget();
private:
	RGBColor m_color; // +0x148
	int m_preColorTime; // +0x154
	int m_postColorTime; // +0x158
	int m_sustainedColorTime; // +0x15C
	float m_frequency; // +0x160
	float m_amplitude; // +0x164
};

// ??0TintDrawableFXNugget@@QAE@XZ
TintDrawableFXNugget::TintDrawableFXNugget()
{
	*(unsigned int *)this = 0x00BDD8E0;
	m_color.setFromInt(-1);
	m_preColorTime = 2000;
	m_postColorTime = 2000;
	m_sustainedColorTime = 1000;
	m_frequency = 1.0f;
	m_amplitude = 1.0f;
}
