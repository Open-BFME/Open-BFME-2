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

// Retail VA 0x00BDD7CC (.rdata): a 5-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_001DFF5D();
extern "C" void vfn_001E0760();
extern "C" void vfn_001E079E();
extern "C" void vfn_001E0A3B();
extern "C" void vfn_0050B238();
#pragma comment(linker, "/alternatename:_vfn_001DFF5D=?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")
#pragma comment(linker, "/alternatename:_vfn_001E0760=?doFXPos@CameraShakerVolumeFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z")
#pragma comment(linker, "/alternatename:_vfn_001E079E=?doFXObj@CameraShakerVolumeFXNugget@@UBEXPBVObject@@0@Z")
#pragma comment(linker, "/alternatename:_vfn_001E0A3B=??_GRva001E009E@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B238=?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")
extern "C" const void *const vtbl_00BDD7CC[] = {
	(const void *)&vfn_001E0A3B,
	(const void *)&vfn_001E0760,
	(const void *)&vfn_001E079E,
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
	*(unsigned int *)this = ((unsigned int)vtbl_00BDD7CC);
	m_radius = 0.0f;
	m_durationSeconds = 0.0f;
	m_amplitudeDegrees = 0.0f;
	m_fieldB4 = 0.0f;
	m_fieldB8 = 0.0f;
	m_fieldBC = 0.0f;
	m_field04 = 5;
}
