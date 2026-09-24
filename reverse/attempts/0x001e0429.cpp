// ??0DynamicDecalFXNugget@@QAE@XZ
// partial score=0.98 date=2026-09-24
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0DynamicDecalFXNugget@@QAE@XZ 147B @0x1E0429: no-arg ctor called by
// DynamicDecalFXNugget::parse (0x001E149D) for the DynamicDecal FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDCCF0 (DecalName@0x148, Shader@0x14C, Size@0x150,
// Color@0x154, Offset@0x160, OrientToObject@0x168, OpacityStart@0x16C,
// OpacityFadeTimeOne@0x170, OpacityPeak@0x174, OpacityPeakTime@0x178,
// OpacityFadeTimeTwo@0x17C, OpacityEnd@0x180, StartingDelay@0x184,
// Lifetime@0x188) and the BFME1 donor (DynamicDecalFXNuggetConstructor:
// shader ALPHA, size 0, type 13, color/offset/opacity zeros,
// orientToObject true). Base 0x001DFEAA is a shared FXNugget-family base
// ctor; pinned opaquely, do not name.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
protected:
	unsigned int m_vtablePad; // +0, overwritten by the derived vtable store
	int m_nuggetType; // +4, nugget type id
	unsigned char m_pad[0x148 - 8];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct RGBColor
{
	void setFromInt(int color);
	float red;
	float green;
	float blue;
};

struct Coord2D
{
	float x;
	float y;
};

class DynamicDecalFXNugget : public Rva001DFEAABase
{
public:
	DynamicDecalFXNugget();
private:
	const char *m_decalName; // +0x148
	int m_shader; // +0x14C, ALPHA = 0
	float m_size; // +0x150
	RGBColor m_color; // +0x154
	Coord2D m_offset; // +0x160
	bool m_orientToObject; // +0x168
	int m_opacityStart; // +0x16C
	float m_opacityFadeTimeOne; // +0x170
	int m_opacityPeak; // +0x174
	float m_opacityPeakTime; // +0x178
	float m_opacityFadeTimeTwo; // +0x17C
	int m_opacityEnd; // +0x180
	float m_startingDelay; // +0x184
	float m_lifetime; // +0x188
};

// ??0DynamicDecalFXNugget@@QAE@XZ
DynamicDecalFXNugget::DynamicDecalFXNugget()
{
	*(unsigned int *)this = 0x00BDD7A4;
	m_decalName = 0;
	_ReadWriteBarrier();
	m_nuggetType = 13;
	m_shader = 0;
	m_size = 0.0f;
	m_color.setFromInt(0);
	Coord2D *offset = &m_offset;
	offset->x = offset->y = 0.0f;
	m_opacityStart = 0;
	m_opacityPeak = 0;
	m_opacityEnd = 0;
	m_orientToObject = true;
	m_opacityFadeTimeOne = 0.0f;
	m_opacityPeakTime = 0.0f;
	m_opacityFadeTimeTwo = 0.0f;
	m_startingDelay = 0.0f;
	m_lifetime = 0.0f;
}
