// cl: /DNDEBUG /MD
//
// ??0CameraShakerVolumeFXNugget@@QAE@XZ 76B @0x1E0714: no-arg ctor called by
// CameraShakerVolumeFXNugget::parse (0x001E1595) for the CameraShakerVolume
// FXList keyword; class name from BFME1. Member names and offsets from the
// retail FieldParse table 0x00BDD040 (Radius@0x154 Duration_Seconds@0x158
// Amplitude_Degrees@0x15C) and the BFME1 donor (lower triple m_fieldB4/B8/BC
// plus FXNugget::m_field04 type id 5; BFME2 stores the lower triple as
// float-zero). Body order follows retail scheduling.
// Base 0x001DFEAA is the shared FXNugget-family base (Rva001DFEAABase.h).

// Retail VA 0x00BDD7CC (.rdata): a 5-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")();
extern "C" void __identifier("?doFXPos@CameraShakerVolumeFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z")();
extern "C" void __identifier("?doFXObj@CameraShakerVolumeFXNugget@@UBEXPBVObject@@0@Z")();
extern "C" void __identifier("??_GRva001E009E@@UAEPAXI@Z")();
extern "C" void __identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")();
extern "C" const void *const vtbl_00BDD7CC[] = {
	(const void *)&__identifier("??_GRva001E009E@@UAEPAXI@Z"),
	(const void *)&__identifier("?doFXPos@CameraShakerVolumeFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z"),
	(const void *)&__identifier("?doFXObj@CameraShakerVolumeFXNugget@@UBEXPBVObject@@0@Z"),
	(const void *)&__identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z"),
	(const void *)&__identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")
};

#include "../../Include/GameClient/Rva001DFEAABase.h"

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
	*(const void **)this = vtbl_00BDD7CC;
	m_radius = 0.0f;
	m_durationSeconds = 0.0f;
	m_amplitudeDegrees = 0.0f;
	m_fieldB4 = 0.0f;
	m_fieldB8 = 0.0f;
	m_fieldBC = 0.0f;
	m_nuggetType = 5;
}
