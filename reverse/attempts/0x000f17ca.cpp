// ?addNeighborlessEdges@W3DVolumetricShadow@@QAEXHPAUPolyNeighbor@@@Z
// partial score=0.95 date=2026-10-06
// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -DBFME_VOLUMETRIC_DELETE_LAYOUT -Ireference/open-bfme-1/inputs/reference/shims/volumetricshadow -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os /G7 -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow
// ?addNeighborlessEdges@W3DVolumetricShadow@@QAEXHPAUPolyNeighbor@@@Z @0x000F17CA 149B
// Named pin, BFME1 donor game/.../W3DVolumetricShadow.cpp:2380. Same view structs plus GetPolygonIndex plus rowed rva000EFDBB tail as sibling addSilhouetteEdge.
typedef int Int;
typedef short Short;
typedef unsigned short UnsignedShort;
struct BFMEShadowGeometryMeshData;
struct BFMEShadowGeometryMeshView
{
	BFMEShadowGeometryMeshData *m_mesh;
	char m_afterMesh[0x1c];
	UnsignedShort *m_parentVerts;
	char m_afterParentVerts[0x10];
};
struct BFMEShadowGeometryView
{
	char m_beforeMeshList[0x14];
	BFMEShadowGeometryMeshView m_meshList[4];
};
struct BFMEVolumetricShadowView
{
	char m_beforeGeometry[0x6c];
	BFMEShadowGeometryView *m_geometry;
};
struct PolyNeighborEdge
{
	Short neighborIndex;
	Short neighborEdgeIndex[2];
};
struct PolyNeighbor
{
	Short myIndex;
	Short m_pad02;
	PolyNeighborEdge neighbor[3];
};
class Rva007BDB70ArrayOwner
{
public:
	void GetPolygonIndex(long idx, Short *out) const;
};
class Rva000EFDBB
{
public:
	void rva000EFDBB(int idx, unsigned short a, unsigned short b);
};
class W3DVolumetricShadow
{
public:
	void addNeighborlessEdges(int meshIndex, PolyNeighbor *us);
};
void W3DVolumetricShadow::addNeighborlessEdges(int meshIndex, PolyNeighbor *us)
{
	Int i, j;
	Short vertexIndexList[3];
	Short edgeStart, edgeEnd;
	BFMEVolumetricShadowView *shadow = (BFMEVolumetricShadowView *)this;
	BFMEShadowGeometryView *geometry = shadow->m_geometry;
	BFMEShadowGeometryMeshView *geomMesh = &geometry->m_meshList[meshIndex];
	((Rva007BDB70ArrayOwner *)geomMesh)->GetPolygonIndex(us->myIndex, vertexIndexList);
	for (i = 0; i < 3; i++)
	{
		edgeStart = vertexIndexList[i];
		if (i == 2)
			edgeEnd = vertexIndexList[0];
		else
			edgeEnd = vertexIndexList[i + 1];
		for (j = 0; j < 3; j++)
		{
			if (us->neighbor[j].neighborIndex != -1)
			{
				if ((us->neighbor[j].neighborEdgeIndex[0] == edgeStart &&
					us->neighbor[j].neighborEdgeIndex[1] == edgeEnd) ||
					(us->neighbor[j].neighborEdgeIndex[1] == edgeStart &&
					us->neighbor[j].neighborEdgeIndex[0] == edgeEnd))
					goto next_edge;
			}
		}
		((Rva000EFDBB *)this)->rva000EFDBB(meshIndex, edgeStart, edgeEnd);
	next_edge: ;
	}
}
