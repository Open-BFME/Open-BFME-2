// TerrainTypeCollection: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_TERRAINTYPECOLLECTION_H
#define CANONICAL_TERRAINTYPECOLLECTION_H

class AsciiString;
class TerrainType;

class TerrainTypeCollection
{
public:
	TerrainType *findTerrain(AsciiString name);
	TerrainType *newTerrain(AsciiString name);
};

#endif // CANONICAL_TERRAINTYPECOLLECTION_H
