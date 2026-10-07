// cl: /O1 /DNDEBUG /MD
// ?loadRoadSegment@W3DRoadBuffer@@QAEXPAGPAUVertexFormatXYZDUV1@@PAVRoadSegment@@@Z
// @0x000D487E 101B.
// ZH W3DRoadBuffer::loadRoadSegment. Unique id at road +0x50 must match
// buffer +0x2C and the visible byte at +0x54 must be set. Vertex copies
// use stride 0x24 through pinned GetVertices; indices use rowed GetIndices.

typedef int Int;

struct VertexFormatXYZDUV1
{
	char m_bytes[0x24];
};

class RoadSegment
{
public:
	char m_pad[0x50];
	Int m_uniqueID;
	unsigned char m_visible;
	char m_pad55[3];
	Int m_numVertex;
	void *m_vb;
	Int m_numIndex;

	Int GetVertices(VertexFormatXYZDUV1 *destination, Int numToCopy);
	Int GetIndices(unsigned short *destination, Int numToCopy, Int offset);
};

class W3DRoadBuffer
{
public:
	void loadRoadSegment(unsigned short *ib, VertexFormatXYZDUV1 *vb, RoadSegment *road);

	char m_pad[0x2C];
	Int m_curUniqueID;
	char m_pad30[8];
	Int m_maxRoadVertex;
	Int m_maxRoadIndex;
	char m_pad40[4];
	Int m_curNumRoadVertices;
	Int m_curNumRoadIndices;
};

void W3DRoadBuffer::loadRoadSegment(unsigned short *ib, VertexFormatXYZDUV1 *vb, RoadSegment *road)
{
	if (road->m_uniqueID != m_curUniqueID)
		return;
	if (road->m_visible == 0)
		return;
	Int curVertex = m_curNumRoadVertices;
	if (curVertex + road->m_numVertex >= m_maxRoadVertex)
		return;
	Int numIndex = road->m_numIndex;
	if (numIndex + m_curNumRoadIndices >= m_maxRoadIndex)
		return;
	m_curNumRoadVertices += road->GetVertices(vb + curVertex, road->m_numVertex);
	numIndex = road->m_numIndex;
	m_curNumRoadIndices += road->GetIndices(ib + m_curNumRoadIndices, numIndex, curVertex);
}
