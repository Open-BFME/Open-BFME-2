// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport

// BFME2 terrain texture-class loading. Retail builds this family with /O1
// (frame-pointer prologue, push/pop materialization); the ZH-port sibling TU
// (WorldHeightMap.cpp) builds /G7, so the /O1 bodies live here.
//
// Layouts are retail-owned: TerrainType carries its name at +0x04 and its
// texture name at +0x08 with the next link at +0x20 (proven by the rowed
// TerrainTypeCollection::findTerrain in TerrainTypes_findTerrain.cpp, whose
// comment records the two by-value getters copying +0x08). TXTextureClass is
// the ZH struct (globalTextureClass, firstTile, numTiles, width,
// isBlendEdgeTile, name at +0x14, positionInTexture).

typedef int Int;
typedef bool Bool;

#include "ascii_string.h"

#include "../../../../GameEngine/Include/Common/TerrainType.h"

#include "../../../../GameEngine/Include/Common/TerrainTypeCollection.h"

extern TerrainTypeCollection *TheTerrainTypes;

// ?makeNrmTextureName@@ present-unmatched
AsciiString makeNrmTextureName(const AsciiString &in);

// ZH TerrainTypes.h getTexture: m_texture (+0x08) by value. Retail keeps it
// out of line at 0x000AF1DD, directly before getNrmTexture; Anim2DTemplate's
// identical name getter folds onto it.
AsciiString TerrainType::getTexture() const
{
	return m_texture;
}

AsciiString TerrainType::getNrmTexture() const
{
	return makeNrmTextureName(m_texture);
}
