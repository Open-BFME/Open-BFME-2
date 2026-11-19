// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// platformsdk
// W3DVolumetricShadow silhouette tools.
// Native F17CA..F185F149 RET8: visible noinline GetPolygonIndex67 closes
// EBX=this/EDI=inner index; standalone declaration swapped both registers.
// Donor ZH/BF1 silhouette semantics; layouts and calls established below.
//   ?addSilhouetteIndices@W3DVolumetricShadow@@IAEXHFF@Z   @0x000EFDBB  59B
//   ?addSilhouetteEdge@W3DVolumetricShadow@@IAEXHPAUPolyNeighbor@@0@Z @0x000F1735 149B
//   ?buildSilhouette@W3DVolumetricShadow@@IAEXHPAVVector3@@@Z @0x000F2D25 422B
//
// Target evidence: silhouette index lists at +0x4180 (Short *[160]) with
// their counts at +0x4400 and the per-mesh index total at +0x4680; mesh
// records 0x34 bytes from m_geometry (+0x6C) +0x14. buildSilhouette calls
// W3DShadowGeometryMesh::buildPolygonNormals (0x000F28C3) when the normals
// are missing, GetPolyNeighbor (0x000F2CFC), GetPolygonIndex (0x000F0FCD),
// addSilhouetteEdge and addNeighborlessEdges (0x000F17CA, unrowed);
// addSilhouetteEdge ends in addSilhouetteIndices. addNeighborlessEdges keeps
// the public mangling of its pin until it is rowed.
// Donor: ZH/Open-BFME-1 W3DVolumetricShadow.cpp silhouette tools, protected
// as in the ZH header. BFME 2 differences: the polygon indices come from the
// out-of-line GetPolygonIndex, and a light-facing polygon's status is
// assigned POLY_VISIBLE (mov, not or) right after being cleared.
typedef float Real;
#include "../../../../../GameEngine/Include/Common/ScalarTypes/Int.h"
#include "../../../../../GameEngine/Include/Common/ScalarTypes/Short.h"
#include "../../../../../GameEngine/Include/Common/ScalarTypes/UnsignedShort.h"
typedef unsigned char Byte;
#include "../../../../../GameEngine/Include/Common/ScalarTypes/Bool.h"
#include <windows.h>

#define MAX_POLYGON_NEIGHBORS 3
#define NO_NEIGHBOR -1
#define MAX_SHADOW_CASTER_MESHES 160
#define POLY_VISIBLE 0x01
#define POLY_PROCESSED 0x02
#define BitSet( x, i ) ( (x) |= (i) )
#define BitTest( x, i ) ( ( (x) & (i) ) != 0 )

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
// Inline component arithmetic avoids emitting unused, conflicting Vector3 COMDAT copies.
static __forceinline Vector3 ShadowSubtract(const Vector3 &lhs, const Vector3 &rhs) { Vector3 result; result.X=lhs.X-rhs.X; result.Y=lhs.Y-rhs.Y; result.Z=lhs.Z-rhs.Z; return result; }

struct NeighborEdge
{
	Short neighborIndex;
	Short neighborEdgeIndex[ 2 ];
};

struct PolyNeighbor
{
	Short myIndex;
	Byte status;
	NeighborEdge neighbor[ MAX_POLYGON_NEIGHBORS ];
};

class W3DShadowGeometry;

class W3DShadowGeometryMesh
{
	friend class W3DShadowGeometry;
	friend class W3DVolumetricShadow;

public:
	const Vector3& GetPolygonNormal(long dwPolyNormId) const
	{
		return m_polygonNormals[dwPolyNormId];
	}
	int GetNumPolygon (void) const {return m_numPolygons;}
	void buildPolygonNormals(void);
protected:
	PolyNeighbor *GetPolyNeighbor( Int polyIndex );
	inline __declspec(noinline) void GetPolygonIndex (long dwPolyId, short *psIndexList) const {
 struct TriIndex {UnsignedShort I,J,K;};const TriIndex *polyi=&(*(TriIndex**)((char*)m_polygonArray+0xc))[dwPolyId];
 *psIndexList++=m_parentVerts[polyi->I];*psIndexList++=m_parentVerts[polyi->J];*psIndexList++=m_parentVerts[polyi->K];
 }

	void *m_polygonArray;
	void *m_vertexArray;
	const Vector3 *m_verts;
	Int m_meshRobjIndex;
	Vector3 *m_polygonNormals;
	Int m_numVerts;
	Int m_numVertsTotal;
	Int m_numPolygons;
	UnsignedShort *m_parentVerts;
	PolyNeighbor *m_polyNeighbors;
	Int m_numPolyNeighbors;
	W3DShadowGeometry *m_parentGeometry;
	Bool m_skinned;
};

class W3DShadowGeometry
{
	friend class W3DVolumetricShadow;
	char m_pad0[0x14];
	W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
};

class W3DVolumetricShadow
{
	friend void bfmeEmitShadowSilhouette(W3DVolumetricShadow *, Vector3 *);
public:
	// Existing public provider mangling retained.
	void addNeighborlessEdges(Int meshIndex, PolyNeighbor *us );
protected:
	__declspec(noinline) inline void buildSilhouette(Int meshIndex, Vector3 *lightPosWorld);
	void addSilhouetteEdge(Int meshIndex, PolyNeighbor *visible, PolyNeighbor *hidden );
	void addSilhouetteIndices(Int meshIndex, Short edgeStart, Short edgeEnd );

	char m_pad0[0x6c];
	W3DShadowGeometry *m_geometry;
	char m_pad70[0x4180 - 0x70];
	Short *m_silhouetteIndex[MAX_SHADOW_CASTER_MESHES];
	Short m_numSilhouetteIndices[MAX_SHADOW_CASTER_MESHES];
	char m_pad4540[0x4680 - 0x4540];
	Int m_numIndicesPerMesh[MAX_SHADOW_CASTER_MESHES];
};

void W3DVolumetricShadow::addSilhouetteIndices(Int meshIndex, Short edgeStart, Short edgeEnd )
{
	m_silhouetteIndex[meshIndex][ m_numSilhouetteIndices[meshIndex]++ ] = edgeStart;
	m_silhouetteIndex[meshIndex][ m_numSilhouetteIndices[meshIndex]++ ] = edgeEnd;
}

void W3DVolumetricShadow::addSilhouetteEdge(Int meshIndex, PolyNeighbor *visible, PolyNeighbor *hidden )
{
	Int i;
	Int neighborIndex = 0;
	Short visibleIndexList[ 3 ];
	Short edgeStart, edgeEnd;
	W3DShadowGeometryMesh *geomMesh = &m_geometry->m_meshList[meshIndex];

	for( i = 0; i < MAX_POLYGON_NEIGHBORS; i++ )
	{
		if( visible->neighbor[ i ].neighborIndex == hidden->myIndex )
		{
			neighborIndex = i;
			break;
		}
	}
	geomMesh->GetPolygonIndex( visible->myIndex, visibleIndexList );
	if( (visibleIndexList[ 0 ] != visible->neighbor[ neighborIndex ].neighborEdgeIndex[ 0 ]) &&
			(visibleIndexList[ 0 ] != visible->neighbor[ neighborIndex ].neighborEdgeIndex[ 1 ]) )
	{
		edgeStart = visibleIndexList[ 1 ];
		edgeEnd = visibleIndexList[ 2 ];
	}
	else if( (visibleIndexList[ 1 ] != visible->neighbor[ neighborIndex ].neighborEdgeIndex[ 0 ]) &&
					 (visibleIndexList[ 1 ] != visible->neighbor[ neighborIndex ].neighborEdgeIndex[ 1 ]) )
	{
		edgeStart = visibleIndexList[ 2 ];
		edgeEnd = visibleIndexList[ 0 ];
	}
	else
	{
		edgeStart = visibleIndexList[ 0 ];
		edgeEnd = visibleIndexList[ 1 ];
	}
	addSilhouetteIndices(meshIndex, edgeStart, edgeEnd );
}

void W3DVolumetricShadow::buildSilhouette(Int meshIndex, Vector3 *lightPosObject)
{
	PolyNeighbor *polyNeighbor;
	Vector3 lightVector;
	Bool visibleNeighborless;
	Int numPolys;
	W3DShadowGeometryMesh *geomMesh;
	Int i, j;
	Int meshEdgeStart=0;

	geomMesh = &m_geometry->m_meshList[meshIndex];
	if (!geomMesh->m_polygonNormals)
		geomMesh->buildPolygonNormals();

	meshEdgeStart=m_numSilhouetteIndices[meshIndex];

	numPolys = geomMesh->GetNumPolygon();
	for( i = 0; i < numPolys; i++ )
	{
		Short poly[ 3 ];
		polyNeighbor = geomMesh->GetPolyNeighbor( i );
		polyNeighbor->status = 0;
		const Vector3& normal=geomMesh->GetPolygonNormal(i);
		geomMesh->GetPolygonIndex( i, poly );
		const Vector3& vertex=geomMesh->m_verts[poly[ 0 ]];
		lightVector= ShadowSubtract(vertex,*lightPosObject);
		if( Vector3::Dot_Product( lightVector, normal ) < 0.0f )
			polyNeighbor->status = POLY_VISIBLE;
	}

	for( i = 0; i < numPolys; i++ )
	{
		PolyNeighbor *otherNeighbor;
		polyNeighbor = geomMesh->GetPolyNeighbor( i );
		visibleNeighborless = FALSE;
		for( j = 0; j < MAX_POLYGON_NEIGHBORS; j++ )
		{
			otherNeighbor = NULL;
			if( polyNeighbor->neighbor[ j ].neighborIndex != NO_NEIGHBOR )
			{
				otherNeighbor = geomMesh->GetPolyNeighbor( polyNeighbor->neighbor[ j ].neighborIndex );
				if( BitTest( otherNeighbor->status, POLY_PROCESSED ) )
					continue;
			}
			if( BitTest( polyNeighbor->status, POLY_VISIBLE ) )
			{
				if( otherNeighbor == NULL )
				{
					visibleNeighborless = TRUE;
				}
				else if( BitTest( otherNeighbor->status, POLY_VISIBLE ) == FALSE )
				{
					addSilhouetteEdge(meshIndex, polyNeighbor, otherNeighbor );
				}
			}
			else if( otherNeighbor != NULL &&
							 BitTest( otherNeighbor->status, POLY_VISIBLE ) )
			{
				addSilhouetteEdge(meshIndex, otherNeighbor, polyNeighbor );
			}
		}
		if( visibleNeighborless == TRUE )
		{
			addNeighborlessEdges(meshIndex, polyNeighbor );
		}
		BitSet( polyNeighbor->status, POLY_PROCESSED );
	}
	m_numIndicesPerMesh[meshIndex] = m_numSilhouetteIndices[meshIndex] - meshEdgeStart;
}

void W3DVolumetricShadow::addNeighborlessEdges(Int meshIndex, PolyNeighbor *us )
{
	Short vertexIndexList[ 3 ];
	Int i, j;
	Short edgeStart, edgeEnd;
	Bool addEdge;
	W3DShadowGeometryMesh *geomMesh = &m_geometry->m_meshList[meshIndex];

	geomMesh->GetPolygonIndex( us->myIndex, vertexIndexList );
	for( i = 0; i < 3; i++ )
	{
		edgeStart = vertexIndexList[ i ];
		if( i == 2 )
			edgeEnd = vertexIndexList[ 0 ];
		else
			edgeEnd = vertexIndexList[ i + 1 ];
		addEdge = TRUE;
		for( j = 0; j < MAX_POLYGON_NEIGHBORS; j++ )
		{
			if( us->neighbor[ j ].neighborIndex != NO_NEIGHBOR )
			{
				if( (us->neighbor[ j ].neighborEdgeIndex[ 0 ] == edgeStart &&
						 us->neighbor[ j ].neighborEdgeIndex[ 1 ] == edgeEnd) ||
						(us->neighbor[ j ].neighborEdgeIndex[ 1 ] == edgeStart &&
						 us->neighbor[ j ].neighborEdgeIndex[ 0 ] == edgeEnd) )
				{
					addEdge = FALSE;
					break;
				}
			}
		}
		if( addEdge == TRUE )
		{
			addSilhouetteIndices(meshIndex, edgeStart, edgeEnd );
		}
	}
}

// Keep the retail SELECT_ANY body emitted in its owning unit. No runtime caller.
// ?bfmeEmitShadowSilhouette absent-from-retail
void bfmeEmitShadowSilhouette(W3DVolumetricShadow *shadow, Vector3 *light)
{
	shadow->buildSilhouette(0, light);
}
