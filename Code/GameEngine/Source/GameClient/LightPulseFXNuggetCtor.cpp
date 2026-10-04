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

// Retail VA 0x00BDD790 (.rdata): a 5-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_001DFF5D();
extern "C" void vfn_001E0373();
extern "C" void vfn_001E03B4();
extern "C" void vfn_001E0A3B();
extern "C" void vfn_0050B238();
#pragma comment(linker, "/alternatename:_vfn_001DFF5D=?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")
#pragma comment(linker, "/alternatename:_vfn_001E0373=?doFXPos@LightPulseFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z")
#pragma comment(linker, "/alternatename:_vfn_001E03B4=?doFXObj@LightPulseFXNugget@@UBEXPBVObject@@0@Z")
#pragma comment(linker, "/alternatename:_vfn_001E0A3B=??_GRva001E009E@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B238=?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")
extern "C" const void *const vtbl_00BDD790[] = {
	(const void *)&vfn_001E0A3B,
	(const void *)&vfn_001E0373,
	(const void *)&vfn_001E03B4,
	(const void *)&vfn_0050B238,
	(const void *)&vfn_001DFF5D
};

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
inline LightPulseFXNugget::LightPulseFXNugget()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BDD790);
	m_increaseFrames = 0;
	m_decreaseFrames = 0;
	m_radius = 0.0f;
	m_boundingCirclePct = 0.0f;
	m_color.blue = 0.0f;
	m_color.green = 0.0f;
	m_color.red = 0.0f;
	m_field04 = 4;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeLightPulseFXNuggetInlineAnchor@@YAXPAVLightPulseFXNugget@@@Z absent-from-retail
void _bfmeLightPulseFXNuggetInlineAnchor(LightPulseFXNugget *p)
{
    p->LightPulseFXNugget::LightPulseFXNugget();
}
#pragma inline_depth()
