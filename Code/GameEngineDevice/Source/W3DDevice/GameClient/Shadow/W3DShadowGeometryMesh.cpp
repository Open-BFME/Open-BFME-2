// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// W3DShadowGeometryMesh: per-mesh shadow geometry, face normals and the
// polygon neighbour table the silhouette walk reads.
//   ??1W3DShadowGeometryMesh@@QAE@XZ                       @0x000F11C0  82B
//   ?buildPolygonNeighbors@W3DShadowGeometryMesh@@QAEXXZ   @0x000F2963 542B
//   ?buildPolygonNormals@W3DShadowGeometryMesh@@QAEXXZ     @0x000F28C3 160B
//   ?buildPolygonNormal@W3DShadowGeometryMesh@@IBEPAVVector3@@JPAV2@@Z @0x000F1D24 292B
//   ?GetPolygonIndex@W3DShadowGeometryMesh@@IBEXJPAF@Z     @0x000F0FCD  67B
//   ?allocateNeighbors@W3DShadowGeometryMesh@@IAE_NH@Z     @0x000EFD77  41B
//   ?deleteNeighbors@W3DShadowGeometryMesh@@IAEXXZ         @0x000EFDA0  27B
//   ?GetPolyNeighbor@W3DShadowGeometryMesh@@IAEPAUPolyNeighbor@@H@Z @0x000F2CFC 41B
//
// Target evidence: the 0x34-byte mesh record of W3DShadowGeometry (from
// +0x14, as initFromMesh 0x000F1018 fills it): index and vertex share
// buffers at +0/+4 (released through slot 0 when their count at +4 drops
// to zero), vertices +8, face normals +0x10, polygon count +0x1C, parent
// vertex map +0x20, neighbour array/count +0x24/+0x28, and the flag at
// +0x30 that initFromMesh copies from the mesh model's SKIN bit (0x400).
// PolyNeighbor is 22 bytes (imul 0x16) with the neighbour edges from +4.
// buildPolygonNeighbors is reached from GetPolyNeighbor's lazy build; it
// calls buildPolygonNormals, deleteNeighbors, allocateNeighbors,
// GetPolygonIndex and CRT abs/fabs (0.01f at 0x00BCF628, 1.0f at
// 0x00BBB8D8). buildPolygonNormals calls buildPolygonNormal per polygon,
// with operator new[] (0x0002FDE0) and the vector constructor iterator over
// the empty Vector3 constructor for unskinned meshes. Retail has no EH
// state reset between the iterator and the per-polygon calls, so
// buildPolygonNormal is declared throw() here; the cl 7.1 build otherwise
// stores state -1 after the iterator.
// For a skinned mesh the normals are written into a shared 12-byte-element
// DynamicVectorClass at 0x00DEBE24, grown by its Resize (0x000F0CF9). That
// address carries the ICF-folded DynamicVectorClass<TCBClass> name, and
// Rva000F1A32Ctor.cpp defines the global under that element type, so this
// unit uses the same stand-in and casts its storage to Vector3.
// Donor: ZH/Open-BFME-1 W3DVolumetricShadow.cpp W3DShadowGeometryMesh
// (buildPolygonNeighbors, buildPolygonNormals, buildPolygonNormal,
// GetPolygonIndex, allocate/deleteNeighbors, GetPolyNeighbor, dtor).
// BFME 2 differences: the share-buffer references and their releases, and
// the skinned-mesh normal buffer.
#include <math.h>
#include <stdlib.h>

typedef float Real;
typedef int Int;
typedef short Short;
typedef unsigned short UnsignedShort;
typedef unsigned char Byte;
typedef bool Bool;
#define TRUE 1
#define FALSE 0
#define NULL 0
#define NEW new

void * __cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *p);

#define MAX_POLYGON_NEIGHBORS 3
#define NO_NEIGHBOR -1

class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z);
	__forceinline Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	__forceinline Real Length2(void) const { return X*X + Y*Y + Z*Z; }
	__forceinline void Normalize(void);
	static __forceinline Real Dot_Product(const Vector3 &a, const Vector3 &b) { return a.X*b.X + a.Y*b.Y + a.Z*b.Z; }
	static __forceinline void Normalized_Cross_Product(const Vector3 &a, const Vector3 &b, Vector3 *set_result);
	Real X, Y, Z;
};
// Inline component arithmetic avoids emitting unused, conflicting Vector3 COMDAT copies.
static __forceinline Vector3 ShadowSubtract(const Vector3 &a, const Vector3 &b) { Vector3 result; result.X=a.X-b.X; result.Y=a.Y-b.Y; result.Z=a.Z-b.Z; return result; }

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};

__forceinline void Vector3::Normalize(void)
{
	Real len2 = Length2();
	if (len2 != 0.0f)
	{
		Real oolen = WWMath::Inv_Sqrt(len2);
		X *= oolen;
		Y *= oolen;
		Z *= oolen;
	}
}

__forceinline void Vector3::Normalized_Cross_Product(const Vector3 &a, const Vector3 &b, Vector3 *set_result)
{
	set_result->X = (a.Y * b.Z - a.Z * b.Y);
	set_result->Y = (a.Z * b.X - a.X * b.Z);
	set_result->Z = (a.X * b.Y - a.Y * b.X);
	set_result->Normalize();
}

class TCBSpline3DClass
{
public:
	class TCBClass;
};
class TCBSpline3DClass::TCBClass
{
public:
	Real Tension;
	Real Continuity;
	Real Bias;
};

template<class T> class VectorClass
{
public:
	virtual bool Resize(int newsize, T const *array = 0);
	T &operator[](int index) { return Vector[index]; }
	int Length(void) const { return VectorMax; }
protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
};
template<class T> class DynamicVectorClass : public VectorClass<T>
{
public:
	virtual bool Resize(int newsize, T const *array = 0);
protected:
	int ActiveCount;
	int GrowthStep;
};
extern DynamicVectorClass<TCBSpline3DClass::TCBClass> g_00DEBE24;

struct TriIndex
{
	UnsignedShort I, J, K;
};

class RefCountClass
{
public:
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }
	virtual void Delete_This(void);
protected:
	int NumRefs;
};

template<class T> class ShareBufferClass : public RefCountClass
{
public:
	T *Get_Array(void) { return Array; }
protected:
	char m_pad08[4];
	T *Array;
};

#define REF_PTR_RELEASE(x) if (x != NULL) { x->Release_Ref(); x = NULL; }

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
	W3DShadowGeometryMesh(void);
	~W3DShadowGeometryMesh( void );

	const Vector3& GetPolygonNormal(long dwPolyNormId) const
	{
		return m_polygonNormals[dwPolyNormId];
	}
	int GetNumPolygon (void) const {return m_numPolygons;}
	void buildPolygonNeighbors( void );
	void buildPolygonNormals(void)
	{
		if (!m_polygonNormals)
		{
			Vector3 *tempVec;
			if (m_skinned)
			{
				if (g_00DEBE24.Length() < m_numPolygons)
					g_00DEBE24.Resize(m_numPolygons);
				tempVec = (Vector3 *)&g_00DEBE24[0];
			}
			else
				tempVec = NEW Vector3[m_numPolygons];
			for (int i=0; i<m_numPolygons; i++)
			{
				buildPolygonNormal(i,&tempVec[i]);
			}
			m_polygonNormals = tempVec;
		}
	}
protected:
	Vector3 *buildPolygonNormal (long dwPolyNormId, Vector3 *pvNorm) const throw()
	{
		if (m_polygonNormals)
			return &(*pvNorm=m_polygonNormals[dwPolyNormId]);
		short indexList[3];
		GetPolygonIndex(dwPolyNormId,indexList);
		const Vector3& v0=GetVertex(indexList[0]);
		const Vector3& v1=GetVertex(indexList[1]);
		const Vector3& v2=GetVertex(indexList[2]);
		Vector3 edge1=ShadowSubtract(v1,v0);
		Vector3 edge2=ShadowSubtract(v1,v2);
		Vector3::Normalized_Cross_Product(edge2,edge1, pvNorm);
		return pvNorm;
	}
	Bool allocateNeighbors( Int numPolys );
	void deleteNeighbors( void );
	PolyNeighbor *GetPolyNeighbor( Int polyIndex );
	void GetPolygonIndex (long dwPolyId, short *psIndexList) const
	{	const TriIndex *polyi=&m_polygonArray->Get_Array()[dwPolyId];
		*psIndexList++ = m_parentVerts[polyi->I];
		*psIndexList++ = m_parentVerts[polyi->J];
		*psIndexList++ = m_parentVerts[polyi->K];
	}
	const Vector3& GetVertex (int dwVertId) const
	{
		return m_verts[dwVertId];
	}

	ShareBufferClass<TriIndex> *m_polygonArray;
	ShareBufferClass<Vector3> *m_vertexArray;
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

W3DShadowGeometryMesh::~W3DShadowGeometryMesh( void )
{
	deleteNeighbors();
	if (m_parentVerts)
		delete [] m_parentVerts;
	if (m_polygonNormals && !m_skinned)
		delete [] m_polygonNormals;
	REF_PTR_RELEASE(m_polygonArray);
	REF_PTR_RELEASE(m_vertexArray);
}

void W3DShadowGeometryMesh::buildPolygonNeighbors( void )
{
	Int numPolys;
	Int i, j;
	buildPolygonNormals();
	numPolys = GetNumPolygon();
	if( numPolys == 0 )
	{
		if( m_numPolyNeighbors != 0 )
			deleteNeighbors();
		return;
	}
	if( numPolys != m_numPolyNeighbors )
	{
		deleteNeighbors();
		if( allocateNeighbors( numPolys ) == FALSE )
			return;
	}
	for( i = 0; i < m_numPolyNeighbors; i++ )
	{
		m_polyNeighbors[ i ].myIndex = i;
		for( j = 0; j < MAX_POLYGON_NEIGHBORS; j++ )
			m_polyNeighbors[ i ].neighbor[ j ].neighborIndex = NO_NEIGHBOR;
	}
	for( i = 0; i < m_numPolyNeighbors; i++ )
	{
		Short poly[ 3 ];
		Short otherPoly[ 3 ];
		GetPolygonIndex( i, poly );
		const Vector3& vNorm=GetPolygonNormal(i);
		for( j = 0; j < m_numPolyNeighbors; j++ )
		{
			Int a, b;
			Int index1, index2;
			Int index1Pos[2];
			Int diff1,diff2;
			if( i == j )
				continue;
			GetPolygonIndex( j, otherPoly );
			index1 = -1;
			index2 = -1;
			for( a = 0; a < 3; a++ )
				for( b = 0; b < 3; b++ )
					if( poly[ a ] == otherPoly[ b ] )
					{
						if( index1 == -1 )
						{	index1 = poly[ a ];
							index1Pos[0]=a;
							index1Pos[1]=b;
						}
						else if( index2 == -1 )
						{
							diff1 = a-index1Pos[0];
							diff2 = b-index1Pos[1];
							if ( ((diff1&0x80000000)^((abs(diff1)&2)<<30)) != ((diff2&0x80000000)^((abs(diff2)&2)<<30)))
							{
								const Vector3& vOtherNorm=GetPolygonNormal(j);
								if (fabs(Vector3::Dot_Product(vOtherNorm,vNorm) + 1.0f) <= 0.01f)
									continue;
								index2 = poly[ a ];
							}
							else
								continue;
						}
						else
						{
							index1=index2=-1;
							continue;
						}
					}
			if( index1 != -1 && index2 != -1  )
			{
				for( a = 0; a < MAX_POLYGON_NEIGHBORS; a++ )
					if( m_polyNeighbors[ i ].neighbor[ a ].neighborIndex == NO_NEIGHBOR )
					{
						m_polyNeighbors[ i ].neighbor[ a ].neighborIndex = j;
						m_polyNeighbors[ i ].neighbor[ a ].neighborEdgeIndex[ 0 ] = index1;
						m_polyNeighbors[ i ].neighbor[ a ].neighborEdgeIndex[ 1 ] = index2;
						break;
					}
			}
		}
	}
}

Bool W3DShadowGeometryMesh::allocateNeighbors( Int numPolys )
{
	m_polyNeighbors = NEW PolyNeighbor[ numPolys ];
	if( m_polyNeighbors == NULL )
		return FALSE;
	m_numPolyNeighbors = numPolys;
	return TRUE;
}

void W3DShadowGeometryMesh::deleteNeighbors( void )
{
	if( m_polyNeighbors )
	{
		delete [] m_polyNeighbors;
		m_polyNeighbors = NULL;
		m_numPolyNeighbors = 0;
	}
}

PolyNeighbor *W3DShadowGeometryMesh::GetPolyNeighbor( Int polyIndex )
{
	if (!m_polyNeighbors)
		buildPolygonNeighbors();
	if( polyIndex < 0 || polyIndex >= m_numPolyNeighbors )
		return NULL;
	return &m_polyNeighbors[ polyIndex ];
}

// Native EFD4B..EFD77: W3DShadowGeometry ctor F1E48 passes this entry to
// the array ctor iterator at F1E85, stride 0x34, count 160. It initializes
// the same record whose fields initFromMesh and the mesh methods establish.
// BFME 1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f supplies the
// mesh-constructor purpose; the extra stores and sentinel come from retail.
W3DShadowGeometryMesh::W3DShadowGeometryMesh(void)
{
 m_polygonArray=0; m_vertexArray=0; m_verts=0; m_meshRobjIndex=-1;
 m_polygonNormals=0; m_numVerts=0; m_numVertsTotal=0; m_numPolygons=0;
 m_parentVerts=0; m_polyNeighbors=0; m_numPolyNeighbors=0; m_parentGeometry=0; m_skinned=false;
}
