// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
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
typedef float Real;
typedef int Int;
typedef short Short;
typedef unsigned short UnsignedShort;

#define NULL 0
#define MAX_SHADOW_LIGHTS		1
#define MAX_SHADOW_CASTER_MESHES	160

class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z);
	__forceinline Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Vector3 &operator*=(Real k) { X *= k; Y *= k; Z *= k; return *this; }
	Vector3 &operator+=(const Vector3 &v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	Real X, Y, Z;
};

// Keep the subtraction local to each recovered algorithm. Their inline forms
// differ in evaluation order; both compute the same three component differences.
// No competing out-of-line Vector3 constructor or subtraction is emitted.
static __forceinline Vector3 VolumeSubtractDirect(const Vector3 &a, const Vector3 &b) { Vector3 result; result.X=a.X-b.X; result.Y=a.Y-b.Y; result.Z=a.Z-b.Z; return result; }
static __forceinline Vector3 VolumeMakePoint(Real x, Real y, Real z) { Vector3 result; result.X=x; result.Y=y; result.Z=z; return result; }
static __forceinline Vector3 VolumeSubtractArgs(const Vector3 &a, const Vector3 &b) { return VolumeMakePoint(a.X-b.X, a.Y-b.Y, a.Z-b.Z); }

struct VertexFormatXYZ
{
	float x;
	float y;
	float z;
};

class VertexBufferClass
{
public:
	class AppendLockClass
	{
	public:
		AppendLockClass(VertexBufferClass *vertex_buffer, unsigned start_index, unsigned index_range, int flags = 0);
		~AppendLockClass();
		void *Get_Vertex_Array(void) { return Vertices; }
	private:
		VertexBufferClass *VertexBuffer;
		void *Vertices;
		void *device_lock;
	};
};

class DX8VertexBufferClass : public VertexBufferClass
{
};

class IndexBufferClass
{
public:
	class AppendLockClass
	{
	public:
		AppendLockClass(IndexBufferClass *index_buffer, unsigned start_index, unsigned index_range, int flags = 0);
		~AppendLockClass();
		unsigned short *Get_Index_Array(void) { return indices; }
	private:
		IndexBufferClass *IndexBuffer;
		unsigned short *indices;
		void *device_lock;
	};
};

class DX8IndexBufferClass : public IndexBufferClass
{
};

class W3DBufferManager
{
public:
	enum VBM_FVF_TYPES
	{
		VBM_FVF_XYZ
	};
	struct W3DVertexBuffer
	{
		char m_pad[0x14];
		DX8VertexBufferClass *m_DX8VertexBuffer;
	};
	struct W3DIndexBuffer
	{
		char m_pad[0x10];
		DX8IndexBufferClass *m_DX8IndexBuffer;
	};
	struct W3DVertexBufferSlot
	{
		Int m_size;
		Int m_start;
		W3DVertexBuffer *m_VB;
	};
	struct W3DIndexBufferSlot
	{
		Int m_size;
		Int m_start;
		W3DIndexBuffer *m_IB;
	};
	W3DVertexBufferSlot *getSlot(VBM_FVF_TYPES fvfType, Int size);
	W3DIndexBufferSlot *getSlot(Int size);
	void releaseSlot(W3DVertexBufferSlot *vbSlot);
	void releaseSlot(W3DIndexBufferSlot *ibSlot);
};
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

class W3DShadowGeometryMesh
{
public:
	const Vector3 &GetVertex(Int index) const { return m_verts[index]; }
private:
	char m_pad0[8];
	Vector3 *m_verts;
	char m_pad1[0x28];
};

class W3DShadowGeometry
{
public:
	W3DShadowGeometryMesh *getMesh(Int index) { return &m_meshList[index]; }
private:
	char m_pad0[0x14];
	W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
};

class W3DVolumetricShadow
{
protected:
	void constructVolume(Vector3 *lightPosObject, Real shadowExtrudeDistance, Int volumeIndex, Int meshIndex);
	void constructVolumeVB(Vector3 *lightPosObject, Real shadowExtrudeDistance, Int volumeIndex, Int meshIndex);

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
