// TerrainRoadCollection: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_TERRAINROADCOLLECTION_H
#define CANONICAL_TERRAINROADCOLLECTION_H

class AsciiString;
class TerrainRoadType;

class TerrainRoadCollection
{
public:
	TerrainRoadType *findBridge(AsciiString name);
	TerrainRoadType *findRoad(AsciiString name);
	TerrainRoadType *newBridge(AsciiString name);
	TerrainRoadType *newRoad(AsciiString name);
	TerrainRoadType *nextRoad(TerrainRoadType *road);
};

#endif // CANONICAL_TERRAINROADCOLLECTION_H
