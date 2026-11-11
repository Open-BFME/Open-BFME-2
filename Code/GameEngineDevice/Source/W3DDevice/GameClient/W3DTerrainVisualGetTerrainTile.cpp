// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?getTerrainTile@W3DTerrainVisual@@UAEPAVTerrainType@@MM@Z, retail 0x00092512, 104 bytes.
// Zero Hour's W3DTerrainVisual::getTerrainTile (W3DTerrainVisual.cpp), the
// non-seismic branch: when m_logicHeightMap is set, take its terrain name at
// (x, y) and look it up through TheTerrainTypes->findTerrain. Evidence: the
// findTerrain call reads the rowed TerrainTypeCollection::findTerrain at
// 0x00317D18 with ecx loaded from the global at 0x00E01CDC, the name comes
// back by value from a thiscall on the +0x1C member through 0x000AEC4E, and
// the temporary is copied and torn down through the rowed StringBase copy
// ctor 0x000365F0 and the folded string dtor 0x00036410. In BFME2 the height
// map sits at +0x1C, not Zero Hour's +0x18, so it lives apart from the ported
// W3DTerrainVisual.cpp; only the member this body reads is declared.

#include "string_base.h"

#include "ascii_string.h"

typedef float Real;

class TerrainType;

#include "../../../../GameEngine/Include/Common/TerrainTypeCollection.h"

// TheTerrainTypes: matched references place it at VA 0xe01cdc (retail .data initial value 0).
TerrainTypeCollection * TheTerrainTypes = 0;

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

#include "../../../Include/W3DDevice/GameClient/W3DTerrainVisualClass.h"

TerrainType *W3DTerrainVisual::getTerrainTile(Real x, Real y)
{
	TerrainType *tile = 0;
	if (m_logicHeightMap)
	{
		AsciiString tileName = m_logicHeightMap->getTerrainNameAt(x, y);
		tile = TheTerrainTypes->findTerrain(tileName);
	}
	return tile;
}
