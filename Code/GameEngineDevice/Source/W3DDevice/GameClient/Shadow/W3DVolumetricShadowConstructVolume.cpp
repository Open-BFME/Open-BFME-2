// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep -ICode/Libraries/Source/WWVegas/WW3D2
// platformsdk
// ?constructVolume@W3DVolumetricShadow@@IAEXPAVVector3@@MHH@Z @0x000EFDF6 1115B.
// ?constructVolumeVB@W3DVolumetricShadow@@IAEXPAVVector3@@MHH@Z @0x000F0251 1277B.
// ?SetPolygonIndex@Geometry@@QAEHJPAF@Z @0x000EFCB7 55B.
//
// W3DVolumetricShadow::constructVolume / constructVolumeVB: extrude the
// current silhouette away from the light into shadow volume triangles,
// either into the Geometry's system-memory arrays (dynamic casters) or
// straight into a W3DBufferManager vertex/index slot pair (static casters).
// Target evidence: retail 0x000EFDF6..0x000F0251 (plain frame, ret 0x10)
// and 0x000F0251..0x000F074E (EH frame, ret 0x10), both called from the
// per-mesh volume updater at 0x000F3B03/0x000F3B0A. Layout read from
// retail: m_geometry at +0x6C (mesh records 0x34 bytes from +0x14, vertex
// array at mesh+8), m_shadowVolume/VB/IB at +0x80/+0x300/+0x580 (one light,
// 160 meshes), m_silhouetteIndex at +0x4180, two Short arrays at
// +0x4400/+0x4540 and m_numIndicesPerMesh at +0x4680. Callees:
// Geometry::SetPolygonIndex (0x000EFCB7, emitted here from the ZH inline;
// six calls from constructVolume), W3DBufferManager::getSlot/releaseSlot
// (0x001163F1/0x00116434/0x00116113/0x0011629A) on TheW3DBufferManager
// (0x00DEC3C0), and the append lock classes (0x001395B0, 0x001388C0, dtors
// 0x00139530/0x00138840) with BFME's fourth flags argument.
// Donor: Open-BFME-1 W3DVolumetricShadow.cpp constructVolume (0x007B82A0)
// and constructVolumeVB (0x007B8980), themselves the ZH bodies; BFME 2
// takes them unchanged apart from inlining Geometry::SetVertex and the
// layout above.
#include <windows.h>

typedef float Real;
typedef int Int;
typedef short Short;
typedef unsigned short UnsignedShort;

#define MAX_SHADOW_LIGHTS		1
#define MAX_SHADOW_CASTER_MESHES	160

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

// Keep the subtraction local to each recovered algorithm. Their inline forms
// differ in evaluation order; both compute the same three component differences.
// No competing out-of-line Vector3 constructor or subtraction is emitted.
static __forceinline Vector3 VolumeSubtractDirect(const Vector3 &lhs, const Vector3 &rhs) { Vector3 result; result.X=lhs.X-rhs.X; result.Y=lhs.Y-rhs.Y; result.Z=lhs.Z-rhs.Z; return result; }
static __forceinline Vector3 VolumeMakePoint(Real x, Real y, Real z) { Vector3 result; result.X=x; result.Y=y; result.Z=z; return result; }
static __forceinline Vector3 VolumeSubtractArgs(const Vector3 &lhs, const Vector3 &rhs) { return VolumeMakePoint(lhs.X-rhs.X, lhs.Y-rhs.Y, lhs.Z-rhs.Z); }

struct VertexFormatXYZ
{
	float x;
	float y;
	float z;
};

#include "../../../../../Libraries/Source/WWVegas/WW3D2/VertexBufferClass.h"

class DX8VertexBufferClass : public VertexBufferClass
{
};

#include "../../../../../Libraries/Source/WWVegas/WW3D2/IndexBufferClass.h"

#include "../../../../../Libraries/Source/WWVegas/WW3D2/DX8IndexBufferClass.h"

#include "../../../../Include/W3DDevice/GameClient/W3DBufferManagerClass.h"
extern W3DBufferManager *TheW3DBufferManager;

class Geometry
{
public:
	Int SetNumActivePolygon(Int numPolygons) { return m_numActivePolygon=numPolygons; }
	Int SetNumActiveVertex(Int numVertices) { return m_numActiveVertex=numVertices; }
	Int SetPolygonIndex(long dwPolyId, short *psIndexList)
	{
		m_indices[dwPolyId*3]=psIndexList[0];
		m_indices[dwPolyId*3+1]=psIndexList[1];
		m_indices[dwPolyId*3+2]=psIndexList[2];
		return 3;
	}
	const Vector3 *SetVertex(int dwVertId, const Vector3 *pvVertex)
	{
		m_verts[dwVertId]=*pvVertex;
		return pvVertex;
	}
private:
	Vector3 *m_verts;
	UnsignedShort *m_indices;
	Int m_numPolygon;
	Int m_numVertex;
	Int m_numActivePolygon;
	Int m_numActiveVertex;
};

#include "../../../../Include/W3DDevice/GameClient/W3DShadowGeometryMesh.h"

#include "../../../../Include/W3DDevice/GameClient/W3DShadowGeometry.h"

class W3DVolumetricShadow
{
	friend void bfmeEmitShadowVolumes(W3DVolumetricShadow *, Vector3 *);
protected:
	__declspec(noinline) inline void constructVolume(Vector3 *lightPosObject, Real shadowExtrudeDistance, Int volumeIndex, Int meshIndex);
	__declspec(noinline) inline void constructVolumeVB(Vector3 *lightPosObject, Real shadowExtrudeDistance, Int volumeIndex, Int meshIndex);

	char m_pad0[0x6c];
	W3DShadowGeometry *m_geometry;
	char m_pad1[0x80 - 0x70];
	Geometry *m_shadowVolume[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DVertexBufferSlot *m_shadowVolumeVB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DIndexBufferSlot *m_shadowVolumeIB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	char m_pad2[0x4180 - 0x800];
	Short *m_silhouetteIndex[MAX_SHADOW_CASTER_MESHES];
	Short m_numSilhouetteIndices[MAX_SHADOW_CASTER_MESHES];
	Short m_maxSilhouetteEntries[MAX_SHADOW_CASTER_MESHES];
	Int m_numIndicesPerMesh[MAX_SHADOW_CASTER_MESHES];
};

void W3DVolumetricShadow::constructVolume( Vector3 *lightPosObject,Real shadowExtrudeDistance, Int volumeIndex, Int meshIndex )
{
	Geometry *shadowVolume;
	Vector3 extrude2;
	Short indexList[ 3 ];
	Int i,k;
	Int vertexCount;
	Int polygonCount;
	Int indicesPerMesh;
	W3DShadowGeometryMesh *geomMesh;

	if( volumeIndex < 0 ||
			volumeIndex >= MAX_SHADOW_LIGHTS ||
			lightPosObject == NULL )
	{
		return;
	}

	shadowVolume = m_shadowVolume[ volumeIndex ][meshIndex];

	if( shadowVolume == NULL )
	{
		return;
	}

	vertexCount = 0;
	polygonCount = 0;

	indicesPerMesh=m_numIndicesPerMesh[meshIndex];
	if (!indicesPerMesh)
		return;

	geomMesh = m_geometry->getMesh(meshIndex);

	shadowVolume->SetNumActivePolygon(0);
	shadowVolume->SetNumActiveVertex(0);

	Short *silhouetteIndices=m_silhouetteIndex[meshIndex];

	Short stripStartIndex=silhouetteIndices[ 0 ];
	Short stripStartVertex=0;

	const Vector3& ev2=
		geomMesh->GetVertex( silhouetteIndices[ 0 ] );

	extrude2 = VolumeSubtractDirect(ev2, *lightPosObject);
	extrude2 *= shadowExtrudeDistance;
	extrude2 += ev2;

	shadowVolume->SetVertex( vertexCount, &ev2 );
	shadowVolume->SetVertex( vertexCount + 1, &extrude2 );

	vertexCount=2;
	Int lastEdgeVertex2Index=0;
	Int lastExtrude2Index=1;

	for( i = 0; i < indicesPerMesh; i += 2 )
	{
		Short currentEdgeEnd=silhouetteIndices[i+1];

		for (k=i+2; k<indicesPerMesh; k+=2)
			if (silhouetteIndices[k]==currentEdgeEnd)
			{
				Int tempIndex=*(Int *)(&silhouetteIndices[i+2]);
				*(Int *)&silhouetteIndices[i+2]=*(Int *)&silhouetteIndices[k];
				*(Int *)&silhouetteIndices[k]=tempIndex;
				break;
			}

		if (k >= indicesPerMesh)
		{
			if (currentEdgeEnd == stripStartIndex)
			{
				indexList[ 0 ] = lastEdgeVertex2Index;
				indexList[ 1 ] = lastExtrude2Index;
				indexList[ 2 ] = stripStartVertex;
				shadowVolume->SetPolygonIndex( polygonCount, indexList );

				indexList[ 0 ] = stripStartVertex;
				indexList[ 1 ] = lastExtrude2Index;
				indexList[ 2 ] = stripStartVertex+1;
				shadowVolume->SetPolygonIndex( polygonCount + 1, indexList );
			}
			else
			{
				const Vector3& ev=geomMesh->GetVertex(currentEdgeEnd);
				shadowVolume->SetVertex( vertexCount, &ev );

				indexList[ 0 ] = lastEdgeVertex2Index;
				indexList[ 1 ] = lastExtrude2Index;
				indexList[ 2 ] = vertexCount;
				shadowVolume->SetPolygonIndex( polygonCount, indexList );

				extrude2 = VolumeSubtractDirect(ev, *lightPosObject);
				extrude2 *= shadowExtrudeDistance;
				extrude2 += ev;
				shadowVolume->SetVertex( vertexCount + 1, &extrude2 );

				indexList[ 0 ] = vertexCount;
				indexList[ 1 ] = lastExtrude2Index;
				indexList[ 2 ] = vertexCount+1;
				shadowVolume->SetPolygonIndex( polygonCount + 1, indexList );

				lastEdgeVertex2Index=vertexCount;
				lastExtrude2Index=vertexCount+1;
				vertexCount += 2;
			}

			if ((i+2) >= indicesPerMesh)
			{
				polygonCount += 2;
				break;
			}

			const Vector3& ev=geomMesh->GetVertex( silhouetteIndices[ i+2 ] );
			extrude2 = VolumeSubtractDirect(ev, *lightPosObject);
			extrude2 *= shadowExtrudeDistance;
			extrude2 += ev;

			lastEdgeVertex2Index=vertexCount;
			lastExtrude2Index=vertexCount + 1;
			stripStartIndex=silhouetteIndices[ i+2 ];
			stripStartVertex=lastEdgeVertex2Index;

			shadowVolume->SetVertex( lastEdgeVertex2Index, &ev );
			shadowVolume->SetVertex( lastExtrude2Index, &extrude2 );
			vertexCount += 2;

			polygonCount += 2;
			continue;
		}
		else
		{
			const Vector3& ev=geomMesh->GetVertex( currentEdgeEnd );
			shadowVolume->SetVertex( vertexCount, &ev );
			indexList[ 0 ] = lastEdgeVertex2Index;
			indexList[ 1 ] = lastExtrude2Index;
			indexList[ 2 ] = vertexCount;
			shadowVolume->SetPolygonIndex( polygonCount, indexList );

			extrude2 = VolumeSubtractDirect(ev, *lightPosObject);
			extrude2 *= shadowExtrudeDistance;
			extrude2 += ev;

			shadowVolume->SetVertex( vertexCount + 1, &extrude2 );

			indexList[ 0 ] = vertexCount;
			indexList[ 1 ] = lastExtrude2Index;
			indexList[ 2 ] = vertexCount+1;
			shadowVolume->SetPolygonIndex( polygonCount + 1, indexList );

			lastEdgeVertex2Index=vertexCount;
			lastExtrude2Index=vertexCount+1;

			vertexCount += 2;
			polygonCount += 2;
		}
	}

	shadowVolume->SetNumActivePolygon(polygonCount);
	shadowVolume->SetNumActiveVertex(vertexCount);
}

void W3DVolumetricShadow::constructVolumeVB( Vector3 *lightPosObject,Real shadowExtrudeDistance, Int volumeIndex, Int meshIndex )
{
	Geometry *shadowVolume;
	Vector3 extrude2;
	Vector3 edgeVertex2;
	Int i,k;
	Int vertexCount;
	Int polygonCount;
	Int indicesPerMesh;
	W3DShadowGeometryMesh *geomMesh;

	W3DBufferManager::W3DVertexBufferSlot *vbSlot;
	W3DBufferManager::W3DIndexBufferSlot *ibSlot;

	if( volumeIndex < 0 ||
			volumeIndex >= MAX_SHADOW_LIGHTS ||
			lightPosObject == NULL )
	{
		return;
	}

	shadowVolume = m_shadowVolume[ volumeIndex ][meshIndex];

	if( shadowVolume == NULL )
	{
		return;
	}

	{
		vertexCount = 0;
		polygonCount = 0;

		indicesPerMesh=m_numIndicesPerMesh[meshIndex];
		if (!indicesPerMesh)
			return;

		Short *silhouetteIndices=m_silhouetteIndex[meshIndex];

		Short stripStartIndex=silhouetteIndices[ 0 ];
		Short stripStartVertex=0;

		vertexCount=2;
		Int lastEdgeVertex2Index=0;
		Int lastExtrude2Index=1;

		for( i = 0; i < indicesPerMesh; i += 2 )
		{
			Short currentEdgeEnd=silhouetteIndices[i+1];

			for (k=i+2; k<indicesPerMesh; k+=2)
				if (silhouetteIndices[k]==currentEdgeEnd)
				{
					Int tempIndex=*(Int *)(&silhouetteIndices[i+2]);
					*(Int *)&silhouetteIndices[i+2]=*(Int *)&silhouetteIndices[k];
					*(Int *)&silhouetteIndices[k]=tempIndex;
					break;
				}

			if (k >= indicesPerMesh)
			{
				if (currentEdgeEnd == stripStartIndex)
				{
				}
				else
				{
					lastEdgeVertex2Index=vertexCount;
					lastExtrude2Index=vertexCount+1;
					vertexCount += 2;
				}

				if ((i+2) >= indicesPerMesh)
				{
					polygonCount += 2;
					break;
				}

				lastEdgeVertex2Index=vertexCount;
				lastExtrude2Index=vertexCount + 1;
				stripStartIndex=silhouetteIndices[ i+2 ];
				stripStartVertex=lastEdgeVertex2Index;

				vertexCount += 2;

				polygonCount += 2;
				continue;
			}
			else
			{
				lastEdgeVertex2Index=vertexCount;
				lastExtrude2Index=vertexCount+1;

				vertexCount += 2;
				polygonCount += 2;
			}
		}
	}

	vbSlot=m_shadowVolumeVB[ volumeIndex ][meshIndex] = TheW3DBufferManager->getSlot(W3DBufferManager::VBM_FVF_XYZ,
		vertexCount);

	ibSlot=m_shadowVolumeIB[ volumeIndex ][meshIndex] = TheW3DBufferManager->getSlot(polygonCount*3);

	if (!ibSlot || !vbSlot)
	{
		if (ibSlot)
			TheW3DBufferManager->releaseSlot(ibSlot);
		if (vbSlot)
			TheW3DBufferManager->releaseSlot(vbSlot);

		m_shadowVolumeIB[ volumeIndex ][meshIndex]=NULL;
		m_shadowVolumeVB[ volumeIndex ][meshIndex]=NULL;
		return;
	}

	geomMesh = m_geometry->getMesh(meshIndex);

	VertexBufferClass::AppendLockClass lockVtxBuffer(vbSlot->m_VB->m_DX8VertexBuffer,vbSlot->m_start,vertexCount);
	VertexFormatXYZ *vb = (VertexFormatXYZ*)lockVtxBuffer.Get_Vertex_Array();

	if (vb == NULL)
		return;

	IndexBufferClass::AppendLockClass lockIdxBuffer(ibSlot->m_IB->m_DX8IndexBuffer,ibSlot->m_start,polygonCount*3);
	UnsignedShort *ib = (UnsignedShort*)lockIdxBuffer.Get_Index_Array();

	if (ib == NULL)
		return;

	shadowVolume->SetNumActivePolygon(polygonCount);
	shadowVolume->SetNumActiveVertex(vertexCount);

	Short *silhouetteIndices=m_silhouetteIndex[meshIndex];

	Short stripStartIndex=silhouetteIndices[ 0 ];
	Short stripStartVertex=0;

	const Vector3& ev=geomMesh->GetVertex( silhouetteIndices[ 0 ] );

	extrude2 = VolumeSubtractArgs(ev, *lightPosObject);
	extrude2 *= shadowExtrudeDistance;
	extrude2 += ev;

	*vb++ = *(VertexFormatXYZ *)&ev;
	*vb++ = *(VertexFormatXYZ *)&extrude2;

	vertexCount=2;
	polygonCount=0;
	Int lastEdgeVertex2Index=0;
	Int lastExtrude2Index=1;

	for( i = 0; i < indicesPerMesh; i += 2 )
	{
		Short currentEdgeEnd=silhouetteIndices[i+1];

		if (((i+2) >= indicesPerMesh) || silhouetteIndices[i+2] != currentEdgeEnd)
		{
			if (currentEdgeEnd == stripStartIndex)
			{
				ib[ 0 ] = lastEdgeVertex2Index;
				ib[ 4 ] = ib[ 1 ] = lastExtrude2Index;
				ib[ 3 ] = ib[ 2 ] = stripStartVertex;
				ib[ 5 ] = stripStartVertex+1;
				ib += 6;
			}
			else
			{
				const Vector3& ev=geomMesh->GetVertex( currentEdgeEnd );
				*vb++ = *(VertexFormatXYZ *)&ev;

				ib[ 0 ] = lastEdgeVertex2Index;
				ib[ 4 ] = ib[ 1 ] = lastExtrude2Index;
				ib[ 3 ] = ib[ 2 ] = vertexCount;
				ib[ 5 ] = vertexCount+1;
				ib += 6;

				extrude2 = VolumeSubtractArgs(ev, *lightPosObject);
				extrude2 *= shadowExtrudeDistance;
				extrude2 += ev;
				*vb++ = *(VertexFormatXYZ *)&extrude2;

				lastEdgeVertex2Index=vertexCount;
				lastExtrude2Index=vertexCount+1;
				vertexCount += 2;
			}

			if ((i+2) >= indicesPerMesh)
			{
				polygonCount += 2;
				break;
			}

			const Vector3& evb=geomMesh->GetVertex( silhouetteIndices[ i+2 ] );
			extrude2 = VolumeSubtractArgs(evb, *lightPosObject);
			extrude2 *= shadowExtrudeDistance;
			extrude2 += evb;

			lastEdgeVertex2Index=vertexCount;
			lastExtrude2Index=vertexCount + 1;
			stripStartIndex=silhouetteIndices[ i+2 ];
			stripStartVertex=lastEdgeVertex2Index;

			*vb++ = *(VertexFormatXYZ *)&evb;
			*vb++ = *(VertexFormatXYZ *)&extrude2;
			vertexCount += 2;

			polygonCount += 2;
			continue;
		}
		else
		{
			const Vector3& ev=geomMesh->GetVertex( currentEdgeEnd );
			*vb++ = *(VertexFormatXYZ *)&ev;
			ib[ 0 ] = lastEdgeVertex2Index;
			ib[ 4 ] = ib[ 1 ] = lastExtrude2Index;
			ib[ 3 ] = ib[ 2 ] = vertexCount;
			ib[ 5 ] = vertexCount+1;
			ib += 6;

			extrude2 = VolumeSubtractArgs(ev, *lightPosObject);
			extrude2 *= shadowExtrudeDistance;
			extrude2 += ev;

			*vb++ = *(VertexFormatXYZ *)&extrude2;

			lastEdgeVertex2Index=vertexCount;
			lastExtrude2Index=vertexCount+1;

			vertexCount += 2;
			polygonCount += 2;
		}
	}
}

// Keep both retail SELECT_ANY bodies emitted in their owning unit. No runtime caller.
// ?bfmeEmitShadowVolumes absent-from-retail
void bfmeEmitShadowVolumes(W3DVolumetricShadow *shadow, Vector3 *light)
{
	shadow->constructVolume(light, 0.0f, 0, 0);
	shadow->constructVolumeVB(light, 0.0f, 0, 0);
}
