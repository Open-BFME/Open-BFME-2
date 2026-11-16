// cl: /O1 /DNDEBUG /MD
//
// ??0ViewShakeFXNugget@@QAE@XZ 35B @0x1E07DF: no-arg ctor called by
// ViewShakeFXNugget::parse (0x001E1611) for the ViewShake FXList keyword;
// class name from BFME1. Member names and offsets from the retail FieldParse
// table 0x00BDD7F4 (Type@0x148) and the BFME1 donor (m_shake plus
// FXNugget::m_field04 type id 6).
// Base 0x001DFEAA is the shared FXNugget-family base (Rva001DFEAABase.h).

// Retail VA 0x00BDD7E0 (.rdata): a 5-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?doFXObj@Rva001DFEAABase@@UBEXPBVObject@@0@Z")();
extern "C" void __identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")();
extern "C" void __identifier("?doFXPos@ViewShakeFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z")();
extern "C" void __identifier("??_GRva001E009E@@UAEPAXI@Z")();
extern "C" void __identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")();
extern "C" const void *const vtbl_00BDD7E0[] = {
	(const void *)&__identifier("??_GRva001E009E@@UAEPAXI@Z"),
	(const void *)&__identifier("?doFXPos@ViewShakeFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z"),
	(const void *)&__identifier("?doFXObj@Rva001DFEAABase@@UBEXPBVObject@@0@Z"),
	(const void *)&__identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z"),
	(const void *)&__identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")
};

#include "../../Include/GameClient/Rva001DFEAABase.h"

class ViewShakeFXNugget : public Rva001DFEAABase
{
public:
	ViewShakeFXNugget();
private:
	int m_shake; // +0x148
};

// ??0ViewShakeFXNugget@@QAE@XZ
inline ViewShakeFXNugget::ViewShakeFXNugget()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BDD7E0);
	m_shake = 1;
	m_nuggetType = 6;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeViewShakeFXNuggetInlineAnchor@@YAXPAVViewShakeFXNugget@@@Z absent-from-retail
void _bfmeViewShakeFXNuggetInlineAnchor(ViewShakeFXNugget *viewShakeFXNugget)
{
    viewShakeFXNugget->ViewShakeFXNugget::ViewShakeFXNugget();
}
#pragma inline_depth()
