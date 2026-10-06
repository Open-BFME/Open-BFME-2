// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/w3droadbuffer /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?adjustStacking@W3DRoadBuffer@@IAEXHH@Z 0x000D4941 149B
// Donor: open-bfme-1/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp:2832
//   and ZH GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp:2712 (same body).
// Caller: ?insertCrossTypeJoins@W3DRoadBuffer@@IAEXXZ at 0x000DB594 directly calls this with road-type IDs.
// Layout (TU-local replica, mangles identically): RoadType stride 0x24 (vector dtor 0x0018E830),
//   uniqueID at +0x18, stacking at +0x20; retail places the 4B LOAD_TEST_ASSETS payload before uniqueID.
//   W3DRoadBuffer m_roadTypes at +0x00, m_initialized byte at +0x0C, m_maxRoadTypes at +0x40.
// Flags: /O1 /G7 /arch:SSE (G7 for retail imul-eax-0x24/imul-esi-0x24 vs lea+shl).
typedef int Int;
typedef unsigned char Bool;
#define DEBUG_ASSERTLOG(x, y) ((void)0)

class RoadType
{
protected:
	void *m_roadTexture;
	void *m_vertexRoad;
	void *m_indexRoad;
	Int m_numRoadVertices;
	Int m_numRoadIndices;
	void *m__retailPayload14;
	Int m_uniqueID;
	Bool m_isAutoLoaded;
	unsigned char _pad1D[3];
	Int m_stackingOrder;
public:
	Int getStacking(void) { return m_stackingOrder; }
	void setStacking(Int order) { m_stackingOrder = order; }
	Int getUniqueID(void) { return m_uniqueID; }
};

class W3DRoadBuffer
{
protected:
	void adjustStacking(Int topUniqueID, Int bottomUniqueID);
	RoadType *m_roadTypes;
	void *m_roads;
	Int m_numRoads;
	Bool m_initialized;
	unsigned char _padD[3];
	void *m_map;
	void *m_lightsIterator;
	Int m__unk18;
	Int m__unk1C;
	Int m__unk20;
	Int m__unk24;
	Int m_curUniqueID;
	Int m_curRoadType;
	Int m_maxUID;
	Int m_maxRoadSegments;
	Int m_maxRoadVertex;
	Int m_maxRoadIndex;
	Int m_maxRoadTypes;
};

//=============================================================================
// W3DRoadBuffer::adjustStacking
//=============================================================================
/** Adjusts the stacking order. */
//=============================================================================
void W3DRoadBuffer::adjustStacking(Int topUniqueID, Int bottomUniqueID)
{
	if (!*(Bool *)((char *)this + 0x0C))
		return;

	Int i, j;
	for (i=0; i<m_maxRoadTypes; i++) {
		if (m_roadTypes[i].getUniqueID() == topUniqueID) break;
	}
	DEBUG_ASSERTLOG(i<m_maxRoadTypes, ("***** Wrong unique id- john a should fix.\n"));
	if (i>=m_maxRoadTypes) return;

	for (j=0; j<m_maxRoadTypes; j++) {
		if (m_roadTypes[j].getUniqueID() == bottomUniqueID) break;
	}
	DEBUG_ASSERTLOG(j<m_maxRoadTypes, ("***** Wrong unique id- john a should fix.\n"));
	if (j>=m_maxRoadTypes) return;

	if (m_roadTypes[i].getStacking() > m_roadTypes[j].getStacking()) {
		return; // It's already on top.
	}
	Int newStacking = m_roadTypes[j].getStacking();
	for (j=0; j<m_maxRoadTypes; j++) {
		if (m_roadTypes[j].getStacking()>newStacking) {
			m_roadTypes[j].setStacking(m_roadTypes[j].getStacking()+1);
		}
	}
	m_roadTypes[i].setStacking(newStacking+1);

}
