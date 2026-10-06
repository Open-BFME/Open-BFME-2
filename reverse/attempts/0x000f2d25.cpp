// ?buildSilhouette@W3DVolumetricShadow@@QAEXHPAVVector3@@@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /arch:SSE2 /DNDEBUG /MD
// ?buildSilhouette@W3DVolumetricShadow@@QAEXHPAVVector3@@@Z @0x000F2D25 422B.
// W3DVolumetricShadow::buildSilhouette(Int meshIndex, Vector3 *lightPosObject):
// per-polygon light-facing test (dot < 0 sets POLY_VISIBLE) then silhouette
// edge walk over PolyNeighbor adjacency calling addSilhouetteEdge /
// addNeighborlessEdges, then books m_numIndicesPerMesh. Donor identity:
// Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/
// W3DVolumetricShadow.cpp W3DVolumetricShadow::buildSilhouette (same class,
// same 2-arg shape, same +0x6C geometry / +0x14 mesh-list / 0x34 stride /
// +0x10 normals / +0x1C count / +0x20 parentVerts / +0x24 neighbors /
// +0x28 neighbor-count mesh view, same status-bit loop). Target spells the
// facing dot Z-first with SSE (no Dot_Product call) and keeps the light
// pointer in a register, reusing the dead parameter slot.

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

struct BfmeTriIndex
{
	unsigned short I;
	unsigned short J;
	unsigned short K;
};

struct BfmeMeshTriData
{
	char m_beforePolys[0x0C];
	const BfmeTriIndex *m_polys;
};

struct NeighborEdge
{
	short neighborIndex;
	short neighborEdgeIndex[2];
};

struct PolyNeighbor
{
	short myIndex;
	unsigned char status;
	unsigned char pad03;
	NeighborEdge neighbor[3];
};

struct Rva007BDB70Record
{
	unsigned char bytes[22];
};

class Rva007BDB70ArrayOwner
{
public:
	Rva007BDB70Record *lookup(int index);
	void buildPolygonNormals(void);
	void GetPolygonIndex(long polyId, short *indexList) const;
	const Vector3 &GetPolygonNormal(int id) const { return m_polygonNormals[id]; }
	int GetNumPolygon(void) const { return m_numPolygons; }

public:
	BfmeMeshTriData *m_mesh; // +0x00
	int m_meshRobjIndex; // +0x04
	const Vector3 *m_verts; // +0x08
	int m_pad0C; // +0x0C
	Vector3 *m_polygonNormals; // +0x10
	int m_pad14[2]; // +0x14
	int m_numPolygons; // +0x1C
	unsigned short *m_parentVerts; // +0x20
	Rva007BDB70Record *m_records; // +0x24
	int m_numRecords; // +0x28
	int m_pad2C; // +0x2C
	char m_flag30; // +0x30
	char m_pad31[3]; // +0x31
};

struct BfmeShadowGeometryView
{
	char m_beforeMeshList[0x14];
	Rva007BDB70ArrayOwner m_meshList[160];
};

class W3DVolumetricShadow
{
public:
	void buildSilhouette(int meshIndex, Vector3 *lightPosObject);
	void addSilhouetteEdge(int meshIndex, PolyNeighbor *visible, PolyNeighbor *hidden);
	void addNeighborlessEdges(int meshIndex, PolyNeighbor *us);

private:
	char m_beforeGeometry[0x6C];
	BfmeShadowGeometryView *m_geometry; // +0x6C
	char m_beforeSilhouette[0x4400 - 0x70];
	short m_numSilhouetteIndices[160]; // +0x4400
	char m_beforeIndicesPerMesh[0x4680 - 0x4400 - 160 * 2];
	int m_numIndicesPerMesh[160]; // +0x4680
};

void W3DVolumetricShadow::buildSilhouette(int meshIndex, Vector3 *lightPosObject)
{
	PolyNeighbor *polyNeighbor;
	bool visibleNeighborless;
	int numPolys;
	Rva007BDB70ArrayOwner *geomMesh;
	int i;
	int j;
	int meshEdgeStart = 0;

	BfmeShadowGeometryView *geometry = m_geometry;
	Rva007BDB70ArrayOwner *mesh = &geometry->m_meshList[meshIndex];
	geomMesh = mesh;
	(void)geomMesh;
	if (!mesh->m_polygonNormals)
		mesh->buildPolygonNormals();

	meshEdgeStart = m_numSilhouetteIndices[meshIndex];

	numPolys = mesh->GetNumPolygon();
	for (i = 0; i < numPolys; i++) {
		short poly[3];

		polyNeighbor = (PolyNeighbor *)mesh->lookup(i);

		polyNeighbor->status = 0;

		const Vector3 &normal = mesh->GetPolygonNormal(i);

		mesh->GetPolygonIndex(i, poly);

		const Vector3 &vertex = mesh->m_verts[poly[0]];

		float dz = vertex.Z - lightPosObject->Z;
		float dy = vertex.Y - lightPosObject->Y;
		float dx = vertex.X - lightPosObject->X;
		float dot = normal.Z * dz + normal.Y * dy + normal.X * dx;
		if (dot < 0.0f)
			polyNeighbor->status = 0x01;
	}

	for (i = 0; i < numPolys; i++) {
		PolyNeighbor *otherNeighbor;

		polyNeighbor = (PolyNeighbor *)mesh->lookup(i);

		visibleNeighborless = false;

		for (j = 0; j < 3; j++) {
			otherNeighbor = 0;

			if (polyNeighbor->neighbor[j].neighborIndex != -1) {
				otherNeighbor = (PolyNeighbor *)mesh->lookup(polyNeighbor->neighbor[j].neighborIndex);

				if (otherNeighbor->status & 0x02)
					continue;
			}

			if (polyNeighbor->status & 0x01) {
				if (otherNeighbor == 0) {
					visibleNeighborless = true;
				} else if (!(otherNeighbor->status & 0x01)) {
					addSilhouetteEdge(meshIndex, polyNeighbor, otherNeighbor);
				}
			} else if (otherNeighbor != 0 && (otherNeighbor->status & 0x01)) {
				addSilhouetteEdge(meshIndex, otherNeighbor, polyNeighbor);
			}
		}

		if (visibleNeighborless) {
			addNeighborlessEdges(meshIndex, polyNeighbor);
		}

		polyNeighbor->status |= 0x02;
	}

	m_numIndicesPerMesh[meshIndex] = m_numSilhouetteIndices[meshIndex] - meshEdgeStart;
}
