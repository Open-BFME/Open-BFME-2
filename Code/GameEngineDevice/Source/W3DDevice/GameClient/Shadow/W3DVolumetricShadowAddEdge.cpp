// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -DBFME_VOLUMETRIC_DELETE_LAYOUT -Ireference/open-bfme-1/inputs/reference/shims/volumetricshadow -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os /G7 -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow
// ?addSilhouetteEdge@W3DVolumetricShadow@@QAEXHPAUPolyNeighbor@@0@Z @0x000F1735 149B
// Named pin, BFME1 donor game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp:2271.
// Evidence: same 3-neighbor loop plus 3-case edge plus addSilhouetteIndices tail; rowed rva000EFDBB 0x000EFDBB is addSilhouetteIndices; pinned GetPolygonIndex 0x000F0FCD fills visible list; caller 0x000F2E7F; flags from neighbour W3DVolumetricShadow.cpp.
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
	void addSilhouetteEdge(int meshIndex, PolyNeighbor *visible, PolyNeighbor *hidden);
};
void W3DVolumetricShadow::addSilhouetteEdge(int meshIndex, PolyNeighbor *visible, PolyNeighbor *hidden)
{
	Int i;
	Int neighborIndex = 0;
	Short visibleIndexList[3];
	Short edgeStart, edgeEnd;
	BFMEVolumetricShadowView *shadow = (BFMEVolumetricShadowView *)this;
	BFMEShadowGeometryView *geometry = shadow->m_geometry;
	BFMEShadowGeometryMeshView *geomMesh = &geometry->m_meshList[meshIndex];
	for (i = 0; i < 3; i++)
	{
		if (visible->neighbor[i].neighborIndex == hidden->myIndex)
		{
			neighborIndex = i;
			break;
		}
	}
	((Rva007BDB70ArrayOwner *)geomMesh)->GetPolygonIndex(visible->myIndex, visibleIndexList);
	if ((visibleIndexList[0] != visible->neighbor[neighborIndex].neighborEdgeIndex[0]) &&
		(visibleIndexList[0] != visible->neighbor[neighborIndex].neighborEdgeIndex[1]))
	{
		edgeStart = visibleIndexList[1];
		edgeEnd = visibleIndexList[2];
	}
	else if ((visibleIndexList[1] != visible->neighbor[neighborIndex].neighborEdgeIndex[0]) &&
		(visibleIndexList[1] != visible->neighbor[neighborIndex].neighborEdgeIndex[1]))
	{
		edgeStart = visibleIndexList[2];
		edgeEnd = visibleIndexList[0];
	}
	else
	{
		edgeStart = visibleIndexList[0];
		edgeEnd = visibleIndexList[1];
	}
	((Rva000EFDBB *)this)->rva000EFDBB(meshIndex, edgeStart, edgeEnd);
}
