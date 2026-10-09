// cl: /MD
// ?nextRoad@TerrainRoadCollection@@QAEPAVTerrainRoadType@@PAV2@@Z @0x00314C13 10B
// Zero Hour TerrainRoadCollection::nextRoad: W3DRoadBuffer::allocateRoadBuffers
// (0x000D77AE) walks the road list with this call, ecx = TheTerrainRoads, and
// the body returns the road's next link at +0x10 (BFME 2 TerrainRoadType, see
// TerrainRoads.cpp). The same 10 bytes are also slot 72 of vtable 0x007C7C90
// (an ICF fold), which is why the body sits away from TerrainRoads.cpp.
class TerrainRoadType
{
public:
	TerrainRoadType *friend_getNext( void ) { return m_next; }
private:
	char m_prefix[0x10];
	TerrainRoadType *m_next;	///< 0x10
};

class TerrainRoadCollection
{
public:
	TerrainRoadType *nextRoad( TerrainRoadType *road );
};

TerrainRoadType *TerrainRoadCollection::nextRoad( TerrainRoadType *road )
{
	return road->friend_getNext();
}
