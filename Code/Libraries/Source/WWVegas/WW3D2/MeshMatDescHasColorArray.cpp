// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?Has_Color_Array@MeshMatDescClass@@QAE_NH@Z, retail 0x00187F70 (14 bytes plus 2 padding), the header inline
// between the rowed Has_UV (0x00187F50) and Has_Texture_Data (0x00187F80): whether the
// per-vertex colour array (+0x50) of the given index is present, as in Zero Hour meshmatdesc.h.
class VertexMaterialClass;

// Use BFME2 debug declarations before the WWLib ownership include closure.
#include "../../debug/debug.h"
#include "MeshMatDescClass.h"

// Select-any like the meshmdlio.cpp copy (this retail body comes first in link
// order, so it is the copy the link keeps); the anchor keeps the body emitted.
inline bool MeshMatDescClass::Has_Color_Array(int array)
{
	return ColorArray[array] != 0;
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitMeshMatDescHasColorArray@@YAXPAVMeshMatDescClass@@H@Z absent-from-retail
void bfmeEmitMeshMatDescHasColorArray(MeshMatDescClass *meshMatDesc, int array)
{
	meshMatDesc->MeshMatDescClass::Has_Color_Array(array);
}

// ?rva00188010@MeshMatDescClass@@QAEXHH@Z, retail 0x00188010 (15 bytes, RET 8), the inline
// placed after Has_Texture_Data's neighbours: stores a per-pass value into the four-entry
// array at +0x58 (canonical DCGSource); the setter identity remains address-derived.
void MeshMatDescClass::rva00188010(int pass, int value)
{
	DCGSource[pass] = static_cast<VertexMaterialClass::ColorSourceType>(value);
}
