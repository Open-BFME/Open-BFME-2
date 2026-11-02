// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Open-BFME7: VertexMaterialClass::Clone at 0x0092EF30 (94 B): allocate a
// 0x6c-byte VertexMaterialClass with the global operator new, default
// construct it (EH state around the raw allocation), copy-assign from this,
// return it. The ported vertmaterial.h spells the allocation through NEW_REF,
// which adds a registration call retail does not have.
#include "VertexMaterialClass.h"

inline VertexMaterialClass *VertexMaterialClass::Clone()
{
	VertexMaterialClass *mat = new VertexMaterialClass;
	*mat = *this;
	return mat;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeVertexMaterialClassInlineAnchor@@YAXPAVVertexMaterialClass@@@Z absent-from-retail
void _bfmeVertexMaterialClassInlineAnchor(VertexMaterialClass *vertexMaterial)
{
    vertexMaterial->Clone();
}
#pragma inline_depth()
