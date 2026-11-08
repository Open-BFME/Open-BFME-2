// cl: /D_OPERATOR_NEW_DEFINED_ /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// stlport
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0006846A@BaseHeightMapRenderObjClass@@QAEXH@Z, retail 0x0006846a, 13 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Virtual forward through slot 0x224 with 0. Retail is mov eax [ecx]
// push 0 call [eax+0x224] ret 4. Evidence: unlock lane; caller at
// 0x0004472F passes TheTerrainRenderObject (BaseHeightMapRenderObjClass*)
// as this with push 1; siblings 0x00043785 0x000447FD same shape;
// abuts prev row 0x000683FF in Rva000683FF.cpp; flags copied from
// neighbours Rva000683FF.cpp and Disp32DwordClearers2.cpp (/O1).
// Owner proven by caller global type; param is generic int (ret 4).

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h"

void BaseHeightMapRenderObjClass::rva0006846A(int arg)
{
	vslot137(0);
}
