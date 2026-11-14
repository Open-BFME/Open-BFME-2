// cl: /O1 /DNDEBUG /MD /arch:SSE /ICode/Libraries/Include
#include "Lib/ICoord2D.h"
//
// ??0TerrainScorchFXNugget@@QAE@XZ 60B @0x1E08D9: no-arg ctor called by
// TerrainScorchFXNugget::parse (0x001E171C) for the TerrainScorch FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDD8A0 (Type@0x148, Radius@0x14C,
// RandomRange@0x150, an ICoord2D holding min 0 / max 3) and the BFME1 donor
// (FXList.cpp: m_scorch(-1), m_radius(0)). Base 0x001DFEAA is a shared
// FXNugget-family base ctor (16 ctor-start callers with this undisplaced);
// pinned opaquely, do not name.

// The retail table at RVA 0x007DD828: 5 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva001E009E@@UAEPAXI@Z")();
void __identifier("?doFXPos@TerrainScorchFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z")();
void __identifier("?doFXObj@Rva001DFEAABase@@UBEXPBVObject@@0@Z")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")();
}
extern "C" const void *const vtbl_00BDD828[5] = {
	(const void *)&__identifier("??_GRva001E009E@@UAEPAXI@Z"), // slot 0 0x001E0A3B
	(const void *)&__identifier("?doFXPos@TerrainScorchFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z"), // slot 1 0x001E0915
	(const void *)&__identifier("?doFXObj@Rva001DFEAABase@@UBEXPBVObject@@0@Z"), // slot 2 0x001DFF1F
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 3 0x0050B238
	(const void *)&__identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z"), // slot 4 0x001DFF5D
};
#include "../../Include/GameClient/Rva001DFEAABase.h"

class TerrainScorchFXNugget : public Rva001DFEAABase
{
public:
	TerrainScorchFXNugget();
private:
	int m_scorchType; // +0x148, scorch lookup, default -1 (random)
	float m_radius; // +0x14C
	ICoord2D m_range; // +0x150
};

TerrainScorchFXNugget::TerrainScorchFXNugget()
{
	m_scorchType |= -1;
	*(unsigned int *)this = ((unsigned int)vtbl_00BDD828);
	m_radius = 0.0f;
	m_nuggetType = 7;
	ICoord2D range;
	range.x = 0;
	range.y = 3;
	m_range = range;
}
