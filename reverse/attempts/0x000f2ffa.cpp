// ?updateMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@ABVAABoxClass@@M@Z
// partial score=0.9534271239838147 date=2026-10-10
// ?updateMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@ABVAABoxClass@@M@Z
// partial score=0.93 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_VOLUMETRIC_DELETE_LAYOUT /Ireference/open-bfme-1/inputs/reference/shims/volumetricshadow /I. /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow
// stlport
#define Region3D DonorRegion3D
#define Matrix4x4 Matrix4  // BFME renamed it
// W3DVolumetricShadow::updateMeshVolume @0x000F2FFA.
// Donor: Open-BFME-1 W3DVolumetricShadow.cpp (updateMeshVolume matched at 0x007BE000);
// carried here with the BFME_VOLUMETRIC_DELETE_LAYOUT preamble of W3DVolumetricShadow.cpp.
#include <assert.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "always.h"
#include "GameClient/View.h"
#include "WW3D2/Camera.h"
#include "WW3D2/Light.h"
#define MESH_RENDER_SNAPSHOT_ENABLED
// BFME's index_count is a full 32-bit slot and its index-buffer constructor
// takes the count at full width; use the BFME declaration of DX8IndexBufferClass
// rather than the Zero Hour one the include path would otherwise find.
#define BFME_DYNAMIC_IB_UINT_CTOR_ABI
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h"
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h"
#undef MESH_RENDER_SNAPSHOT_ENABLED
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/HLod.h"
#include "WW3D2/mesh.h"
#include "WW3D2/meshmdl.h"
#include "Lib/BaseType.h"
#include "W3DDevice/GameClient/W3DGranny.h"
#include "W3DDevice/GameClient/Heightmap.h"
#include "D3dx8math.h"
#include "common/GlobalData.h"
#include "common/drawmodule.h"
#include "W3DDevice/GameClient/W3DVolumetricShadow.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "WW3D2/statistics.h"
#include "GameLogic/TerrainLogic.h"
#include "WW3D2/DX8Caps.h"
#include "GameClient/Drawable.h"
#include "wwshade/shdmesh.h"
#include "wwshade/shdsubmesh.h"

extern float g_Va00DEBE08;
#define cosAngleToCare g_Va00DEBE08
extern FrustumClass g_Va00DEBD00;
#define shadowCameraFrustum (&g_Va00DEBD00)
#define	SHADOW_EXTRUSION_BUFFER	0.1f
// Stand-ins for retail's folded/opaque callees (rowed under honest address names).
class Rva0007671F { public: Rva0007671F(); private: char m_bytes[0x40]; };
class Rva000F26DC { public: void rva000F074E(int, int); };
#undef Region3D
struct Region3D { Region3D(const Region3D &); float x_min,y_min,z_min,x_max,y_max,z_max; };
struct SHADOW_STATIC_VOLUME_VERTEX	//vertex structure passed to D3D
{
		float x,y,z;
}; 
#define SHADOW_STATIC_VOLUME_FVF	D3DFVF_XYZ

#ifdef SV_DEBUG	//in debug mode, dynamic shadows are rendered with random diffuse color
	struct SHADOW_DYNAMIC_VOLUME_VERTEX	//vertex structure passed to D3D
	{
			float x,y,z;
			DWORD diffuse;
	}; 
	#define SHADOW_DYNAMIC_VOLUME_FVF	D3DFVF_XYZ|D3DFVF_DIFFUSE
#else
	typedef struct SHADOW_STATIC_VOLUME_VERTEX	SHADOW_DYNAMIC_VOLUME_VERTEX;
	#define SHADOW_DYNAMIC_VOLUME_FVF	D3DFVF_XYZ
#endif

LPDIRECT3DVERTEXBUFFER8 shadowVertexBufferD3D=NULL;		///<D3D vertex buffer
LPDIRECT3DINDEXBUFFER8	shadowIndexBufferD3D=NULL;	///<D3D index buffer
int nShadowVertsInBuf=0;	//model vetices in vertex buffer
int nShadowStartBatchVertex=0;
int nShadowIndicesInBuf=0;	//model vetices in vertex buffer
int nShadowStartBatchIndex=0;
int SHADOW_VERTEX_SIZE=4096;
int SHADOW_INDEX_SIZE=8192;

//Rough bounding box around visible portion of the terrain
//useful for quick culling
static Real bcX;
static Real bcY;
static Real bcZ;
static Real beX;
static Real beY;
static Real beZ;

static LPDIRECT3DVERTEXBUFFER8 lastActiveVertexBuffer=NULL;

/** A simple structure to hold random geometry (vertices, polygons, etc.).  We'll use this
* to store shadow volumes. */
struct Geometry
{
	enum VisibleState {
		STATE_UNKNOWN = CollisionMath::BOTH,
		STATE_VISIBLE = CollisionMath::INSIDE,
		STATE_INVISIBLE = CollisionMath::OUTSIDE,
	};

	Geometry(void) : m_verts(NULL),m_indices(NULL),m_numPolygon(0),m_numVertex(0),m_flags(0) {}
	~Geometry(void) { Release();}

	Int Create( Int numVertices, Int numPolygons )
	{
		if (numVertices)
		{
			if (m_verts)
				delete [] m_verts;
			if((m_verts=NEW Vector3[numVertices]) == 0)
				return FALSE;
		}
		if (numPolygons)
		{
			if (m_indices)
				delete [] m_indices;
			if((m_indices=NEW UnsignedShort[numPolygons*3]) == 0)
				return FALSE;
		}
		m_numPolygon=numPolygons;
		m_numVertex=numVertices;
		m_numActivePolygon=0;
		m_numActiveVertex=0;
		return TRUE;
	}
	void Release(void)
	{	if (m_verts)
		{	delete [] m_verts;
			m_verts=NULL;
		}
		if (m_indices)
		{	delete [] m_indices;
			m_indices=NULL;
		}
		m_numActivePolygon=m_numPolygon=0;
		m_numActiveVertex=m_numVertex=0;
	}
	Int GetFlags (void) { return m_flags;}
	void SetFlags (Int flags) { m_flags = flags;}
	Int GetNumPolygon (void) { return m_numPolygon;}
	Int GetNumVertex (void)	{ return m_numVertex;}
	Int GetNumActivePolygon (void) { return m_numActivePolygon;}
	Int GetNumActiveVertex (void)	{ return m_numActiveVertex;}
	Int SetNumActivePolygon (Int numPolygons) { return m_numActivePolygon=numPolygons;}
	Int SetNumActiveVertex (Int numVertices)	{ return m_numActiveVertex=numVertices;}
	UnsignedShort *GetPolygonIndex (long dwPolyId, short *psIndexList) const
	{
		*psIndexList++ = m_indices[dwPolyId*3];
		*psIndexList++ = m_indices[dwPolyId*3+1];
		*psIndexList++ = m_indices[dwPolyId*3+2];
		return &m_indices[dwPolyId];
	}
	Int SetPolygonIndex (long dwPolyId, short *psIndexList)
	{
		m_indices[dwPolyId*3]=psIndexList[0];
		m_indices[dwPolyId*3+1]=psIndexList[1];
		m_indices[dwPolyId*3+2]=psIndexList[2];
		return 3;
	}
	Vector3 *GetVertex (int dwVertId)
	{
		return &m_verts[dwVertId];
	}
	const Vector3 *SetVertex (int dwVertId, const Vector3 *pvVertex)
	{
		m_verts[dwVertId]=*pvVertex;
		return 	pvVertex;
	}
	///Find a vertex within given range
	Int	FindVertexInRange (Int start, Int end, Vector3 *pvVertex)
	{
		for (Int i=start; i<end; i++)
		{
			if ((m_verts[i]-*pvVertex).Length2() == 0)
				return i;
		}
		return -1;
	}

	AABoxClass &getBoundingBox(void) {return m_boundingBox;}
	void	setBoundingBox(const AABoxClass &box)	{m_boundingBox=box;}
	void	setBoundingSphere(const SphereClass &sphere) {m_boundingSphere=sphere;}
	SphereClass &getBoundingSphere(void) {return m_boundingSphere;}
	void	setVisibleState(VisibleState state)	{m_visibleState=state;}
	VisibleState	getVisibleState(void) {return m_visibleState;}

private:
	Vector3	*m_verts;
	UnsignedShort *m_indices;
	Int m_numPolygon;
	Int m_numVertex;
	Int m_numActivePolygon;	///<number of polygons filled with valid data
	Int m_numActiveVertex;		///<number of vertices filled with valid data
	Int	m_flags;				///<geometry attribute flags - static vs. dynamic, etc.
	AABoxClass m_boundingBox;	///<object space bounding box of shadow volume
	SphereClass m_boundingSphere;	///<object space bounding sphere of shadow volume
	VisibleState	m_visibleState;		///<flag if this geometry was visible in this frame.
};

// CONST //////////////////////////////////////////////////////////////////////
const Int MAX_POLYGON_NEIGHBORS = 3;  // we use nothing but triangles for 
																			// geometry polygons so we have at 
																			// most 3 neighbors
const Int NO_NEIGHBOR = -1;  // entry value for neighbor when there isn't one

const Byte POLY_VISIBLE	  = 0x01;  // polygon is visible from light
const Byte POLY_PROCESSED = 0x02;  // this poly has been processed

// STRUCT /////////////////////////////////////////////////////////////////////

// NeighborEdge ---------------------------------------------------------------
typedef struct _NeighborEdge
{

	Short neighborIndex;  // index of polygon who is our neighbor, if there is
												// not a neighbor it contains NO_NEIGHBOR
	Short neighborEdgeIndex[ 2 ];  // the two vertex indices that represent the
																 // shared edge

} NeighborEdge;

// PolygonNeighbor ------------------------------------------------------------
struct  PolyNeighbor
{

	Short myIndex;  // our polygon index so we know who we are
	Byte status;  // status flags used when processing neighbors
	NeighborEdge neighbor[ MAX_POLYGON_NEIGHBORS ];

};

/**This class holds original mesh specific data and geometry.  The meshes stored in this
class have been cleaned to remove replicated vertices and also cache mesh data needed for
faster silhouette computation.  A model can contain many meshes for which we need to store
separate data so they can move relative to each other.*/
class W3DShadowGeometryMesh
{
	//for the sake of speed, give direct access to classes that need this data.
	friend class W3DShadowGeometry;
	friend class W3DVolumetricShadow;
	
public:
	W3DShadowGeometryMesh::W3DShadowGeometryMesh( void );
#ifdef DO_TERRAIN_SHADOW_VOLUMES
	virtual
#endif
	W3DShadowGeometryMesh::~W3DShadowGeometryMesh( void );

	/// @todo: Cache/Store face normals someplace so they are not recomputed when lights move.
	const Vector3& GetPolygonNormal(long dwPolyNormId) const
	{
		WWASSERT(m_polygonNormals);
		return m_polygonNormals[dwPolyNormId];
	}
	int GetNumPolygon (void) const {return m_numPolygons;}
	/// given loaded geometry this builds the polygon neighbor information
	void buildPolygonNeighbors( void );
	void buildPolygonNormals(void)
	{
		if (!m_polygonNormals)
		{	//need to allocate storage
			Vector3 *tempVec = NEW Vector3[m_numPolygons];
			for (int i=0; i<m_numPolygons; i++)
			{
				buildPolygonNormal(i,&tempVec[i]);
			}
			m_polygonNormals = tempVec;
		}
	}
protected:
	Vector3 *buildPolygonNormal (long dwPolyNormId, Vector3 *pvNorm) const
	{
		if (m_polygonNormals)
			return &(*pvNorm=m_polygonNormals[dwPolyNormId]);
		short indexList[3];
//		Vector3 vertexList[3];
		//get vertex indices for this polygon
		GetPolygonIndex(dwPolyNormId,indexList);
		//get the vertices	
//		GetVertex(indexList[0],&vertexList[0]);
//		GetVertex(indexList[1],&vertexList[1]);
//		GetVertex(indexList[2],&vertexList[2]);
		const Vector3& v0=GetVertex(indexList[0]);
		const Vector3& v1=GetVertex(indexList[1]);
		const Vector3& v2=GetVertex(indexList[2]);

		//compute triangle normal by crossing 2 edges
		Vector3 edge1=v1-v0;
		Vector3 edge2=v1-v2;
#ifdef ALLOW_TEMPORARIES
		*pvNorm=Vector3::Cross_Product(edge2,edge1);
		pvNorm->Normalize();
#else
		Vector3::Normalized_Cross_Product(edge2,edge1, pvNorm);
#endif
		return pvNorm;
	}

	/// creating and deleting storage for the polygon neighbors
	Bool allocateNeighbors( Int numPolys );
	void deleteNeighbors( void );

	// geometry shadow data access
	PolyNeighbor *GetPolyNeighbor( Int polyIndex );
	int GetNumVertex (void)	const {	return m_numVerts;}
	///Get indices to the 3 vertices of this face.
#ifdef DO_TERRAIN_SHADOW_VOLUMES
	virtual
#endif
	void GetPolygonIndex (long dwPolyId, short *psIndexList) const
	{	const TriIndex *polyi=&m_polygons[dwPolyId];
		*psIndexList++ = m_parentVerts[polyi->I];
		*psIndexList++ = m_parentVerts[polyi->J];
		*psIndexList++ = m_parentVerts[polyi->K];
	}
#ifdef DO_TERRAIN_SHADOW_VOLUMES
	virtual
#endif
	const Vector3& GetVertex (int dwVertId) const
	{
		return m_verts[dwVertId];
	}

	MeshClass *m_mesh;	///< W3D mesh for this geometry
	Int m_meshRobjIndex;	///<index of this mesh within hlod robj
	const Vector3	*m_verts;		///<array of vertices
	Vector3	*m_polygonNormals;	///<array of face normals
	Int m_numVerts;	 ///< number of actual vertices after duplicates are removed.
	Int m_numPolygons; ///<number of polygons in source geometry
	const TriIndex	*m_polygons;	///<array of 3 vertex indices per face
	UnsignedShort *m_parentVerts;	///<array of parent vertex indices for each vertex.
	/// the neighbor info indexed by polygon id
	PolyNeighbor *m_polyNeighbors;
	Int m_numPolyNeighbors;  // length of m_polyNeighbors and the number of polygons
							 // in our current geometry.
	W3DShadowGeometry *m_parentGeometry; // mesh hierarchy containing this mesh.

};	//end of meshInfo

// BFME's MeshClass has two render-object view slots after Class_ID; the
// recovered HLOD path uses the later slot, which the Zero Hour headers omit.
class BfmeMeshRenderObjView
{
public:
	virtual void Slot_00(void);
	virtual void Slot_04(void);
	virtual void Slot_08(void);
	virtual int Class_ID(void) const;
	virtual RenderObjClass *Mesh_View_10(void);
	virtual RenderObjClass *Mesh_View_14(void);
};

#define BFME_HLOD_EIGHT_SLOTS(a, b, c, d, e, f, g, h) \
	virtual void Slot_##a(void); virtual void Slot_##b(void); \
	virtual void Slot_##c(void); virtual void Slot_##d(void); \
	virtual void Slot_##e(void); virtual void Slot_##f(void); \
	virtual void Slot_##g(void); virtual void Slot_##h(void);

class BfmeHLodRenderObjView
{
public:
	BFME_HLOD_EIGHT_SLOTS(000, 001, 002, 003, 004, 005, 006, 007)
	BFME_HLOD_EIGHT_SLOTS(008, 009, 010, 011, 012, 013, 014, 015)
	BFME_HLOD_EIGHT_SLOTS(016, 017, 018, 019, 020, 021, 022, 023)
	BFME_HLOD_EIGHT_SLOTS(024, 025, 026, 027, 028, 029, 030, 031)
	BFME_HLOD_EIGHT_SLOTS(032, 033, 034, 035, 036, 037, 038, 039)
	BFME_HLOD_EIGHT_SLOTS(040, 041, 042, 043, 044, 045, 046, 047)
	BFME_HLOD_EIGHT_SLOTS(048, 049, 050, 051, 052, 053, 054, 055)
	BFME_HLOD_EIGHT_SLOTS(056, 057, 058, 059, 060, 061, 062, 063)
	BFME_HLOD_EIGHT_SLOTS(064, 065, 066, 067, 068, 069, 070, 071)
	BFME_HLOD_EIGHT_SLOTS(072, 073, 074, 075, 076, 077, 078, 079)
	virtual int Get_LOD_Count(void) const;
	BFME_HLOD_EIGHT_SLOTS(081, 082, 083, 084, 085, 086, 087, 088)
	BFME_HLOD_EIGHT_SLOTS(089, 090, 091, 092, 093, 094, 095, 096)
	BFME_HLOD_EIGHT_SLOTS(097, 098, 099, 100, 101, 102, 103, 104)
	BFME_HLOD_EIGHT_SLOTS(105, 106, 107, 108, 109, 110, 111, 112)
	BFME_HLOD_EIGHT_SLOTS(113, 114, 115, 116, 117, 118, 119, 120)
	BFME_HLOD_EIGHT_SLOTS(121, 122, 123, 124, 125, 126, 127, 128)
	BFME_HLOD_EIGHT_SLOTS(129, 130, 131, 132, 133, 134, 135, 136)
	virtual void Slot_137(void);
	virtual int Get_Lod_Model_Count(int lod_index) const;
	virtual RenderObjClass *Peek_Lod_Model(int lod_index, int model_index) const;
};

#undef BFME_HLOD_EIGHT_SLOTS

class BfmeW3DShadowGeometryLayout
{
public:
	unsigned char m_opaque[0x2094];
	Int m_meshCount;
	Int m_numTotalsVerts;
};

/** This class will wrap any shadow casting geometry with additional
data needed for efficient shadow volume generation.  The W3DVolumetricShadowManager
will allocate these structures and hash them for quick re-use on other
models sharing the same geometry.*/
class W3DShadowGeometry : public RefCountClass, public	HashableClass
{

	public:

	W3DShadowGeometry( void );
		~W3DShadowGeometry( void ) { };

		virtual	const char * Get_Key( void )	{ return m_namebuf;	}

		Int init (RenderObjClass *robj);
		Int initFromHLOD (RenderObjClass *robj);	///<initialize the geometry from a W3D HLOD object.
		Int initFromMesh (RenderObjClass *robj);///<initialize the geometry from a W3D Mesh object.
		Int initFromMesh (RenderObjClass *robj, Int mesh_index, W3DShadowGeometry *parent_geometry);

		const char *		Get_Name(void) const	{ return m_namebuf;}
		void				Set_Name(const char *name)
		{	memset(m_namebuf,0,sizeof(m_namebuf));	//pad with zero so always ends with null character.
			strncpy(m_namebuf,name,sizeof(m_namebuf)-1);
		}
		Int					getMeshCount(void)	{ return m_meshCount;}
		W3DShadowGeometryMesh	*getMesh(Int index)	{ return &m_meshList[index];}

		
		int GetNumTotalVertex (void)	{	return m_numTotalsVerts;}	///<total number of vertices in all meshes of this geometry

	private:

		char m_namebuf[2*W3D_NAME_LEN];	///<name of model hierarchy

		W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES]; ///<collection of meshes for this geometry.
		Int m_meshCount;							///<number of meshes in hierarchy
		Int m_numTotalsVerts;						///<number of verts in entire hierarchy
};
  
#define MAX_SHADOW_VOLUME_VERTS 16384

void W3DVolumetricShadow::updateMeshVolume(Int meshIndex, Int lightIndex, const Matrix3D *meshXform, const AABoxClass &meshBox, float floorZ )
{
	Vector3 lightPosObject;
	Rva0007671F worldToObject;
	Vector3 objectCenter;
	Vector3 toLight;
	Vector3 toPrevLight;
	Vector3 lightPosWorld;
	//Figuring out if mesh has rotated is cheaper (no normalization) than figuring out if light angle has changed.
	//So we divide the 2 tests.  Also, our light (sun) almost never moves so no second test needed at all.
	Bool isMeshRotating = false;	//flag if mesh has rotated since last update. Translation doesn't matter for infinite light source.
	Bool isLightMoving = false;	//flag if light has moved since last update.

	Matrix4x4 objectToWorld(*meshXform);
	Matrix4x4 *prevXForm=&m_objectXformHistory[ lightIndex ][meshIndex];
	struct Rva007BE000MeshRecordView
	{
		unsigned char m_beforeFlag[0x30];
		unsigned char m_field30;
		unsigned char m_tail[3];
	};
	struct Rva007BE000GeometryView
	{
		unsigned char m_beforeMeshes[0x14];
		Rva007BE000MeshRecordView m_meshes[MAX_SHADOW_CASTER_MESHES];
	};
	Rva007BE000GeometryView *geometryView = (Rva007BE000GeometryView *)
		((W3DVolumetricShadow *)((char *)this + 0x30))->m_geometry;
	Int allocationFlags = 0;
	if (*(unsigned char *)(meshIndex * sizeof(Rva007BE000MeshRecordView) + (unsigned int)geometryView + 0x44))
	{
		allocationFlags = 1;
		isMeshRotating = true;
	}
	else
	{

	//
	// build the shadow silhouette and construct shadow volume from
	// this light location.  The for loop wrapped around this is 
	// theoretical code for future enhancements of multiple lights that
	// cast shadows
	//

#ifdef CNC3 //(gth) numerical error requires that the axis vectors be normalized...

	//When dealing with infinite light sources, we can assume that the shadow doesn't
	//change much based on object position.  Only the orientation to light matters.
	Vector3 va = (Vector3 &)(*prevXForm)[0];
	Vector3 vb = (Vector3 &)objectToWorld[0];
	va.Normalize();
	vb.Normalize();
	Real cosAngle = WWMath::Fabs(Vector3::Dot_Product(va,vb));

	if (cosAngle >= cosAngleToCare)
	{	
		
		va = (Vector3 &)(*prevXForm)[1];
		vb = (Vector3 &)objectToWorld[1];
		va.Normalize();
		vb.Normalize();
		cosAngle = WWMath::Fabs(Vector3::Dot_Product(va,vb));

		if (cosAngle >= cosAngleToCare)
		{
			va = (Vector3 &)(*prevXForm)[2];
			vb = (Vector3 &)objectToWorld[2];
			va.Normalize();
			vb.Normalize();
			cosAngle = WWMath::Fabs(Vector3::Dot_Product(va,vb));
			if (cosAngle < cosAngleToCare)
				isMeshRotating=true;
		}
		else
			isMeshRotating =true;
	}
	else
		isMeshRotating =true;


#else // CNC3 (old generals code)

#ifdef ASSUME_NEAR_LIGHTSOURCE
	if (memcmp(&objectToWorld,prevXForm,sizeof(objectToWorld)))
		isMeshRotating = true; //mesh transform has not changed since last update.
#else
	//When dealing with infinite light sources, we can assume that the shadow doesn't
	//change much based on object position.  Only the orientation to light matters.
	Real cosAngle = fabs (Vector3::Dot_Product((Vector3 &)(prevXForm->operator [](0)),(Vector3 &)(objectToWorld.operator [](0))));
	if (cosAngle >= cosAngleToCare)
	{	cosAngle = fabs (Vector3::Dot_Product((Vector3 &)(prevXForm->operator [](1)),(Vector3 &)(objectToWorld.operator [](1))));
		if (cosAngle >= cosAngleToCare)
		{
			cosAngle = fabs (Vector3::Dot_Product((Vector3 &)(prevXForm->operator [](2)),(Vector3 &)(objectToWorld.operator [](2))));
			if (cosAngle < cosAngleToCare)
				isMeshRotating=true;
		}
		else
			isMeshRotating =true;
	}
	else
		isMeshRotating =true;
#endif	//near light source
#endif // CNC3
	}

	// get the light
	lightPosWorld = TheW3DShadowManager->getLightPosWorld(lightIndex);

	// get the object
	meshXform->Get_Translation(&objectCenter);	//current mesh position

	// check if object has a limit/clamp on shadow length and adjust light
	// position of necessary.
	if (((W3DVolumetricShadow *)((char *)this + 0x30))->m_shadowLengthScale)
	{	//Find light's distance from origin in xy plane
		Real lightXYDistance = sqrt(lightPosWorld.X*lightPosWorld.X + lightPosWorld.Y * lightPosWorld.Y);
		Real newZ=lightXYDistance*((W3DVolumetricShadow *)((char *)this + 0x30))->m_shadowLengthScale;

		if (newZ > lightPosWorld.Z)
		{	//clamped z component is higher than actual light position allows so adjust it.
			lightPosWorld.Z = newZ;
		}
	}

	if (lightPosWorld != m_lightPosHistory[ lightIndex ][meshIndex])
	{	//Light position has moved, see if enough to matter

		// compute vector from the light to the current object position
		toLight = objectCenter - lightPosWorld;
		toLight.Normalize();

		// compute vector from the previous light to the object position
		toPrevLight = objectCenter - m_lightPosHistory[ lightIndex ][meshIndex];
		toPrevLight.Normalize();

		Real cosAngle = fabs (Vector3::Dot_Product(toLight,toPrevLight));
		if (cosAngle < cosAngleToCare)	//less than 45 degree change
			isLightMoving =true;
	}
	else
	///@todo: Find a better way to deal with this - use maximum extrusion once!  Also avoid hit for units climbing hills.
	if (fabs(objectCenter.Z - prevXForm->operator [](2).W) > SHADOW_EXTRUSION_BUFFER)
		isLightMoving = true;	//treat model rising just like rotation since volume needs update for longer extrusion.

	// reconstruct if needed
	if (isLightMoving || isMeshRotating)
	{
		//
		// transform the light in the world to object space, we
		// care only about the rotation of components for the coordinate
		// system change, not the translations
		//
		Real det;
		D3DXMatrixInverse((D3DXMATRIX*)&worldToObject, &det, (D3DXMATRIX*)&objectToWorld);

		// find out light position in object space
		Matrix4x4::Transform_Vector(*(Matrix4x4 *)&worldToObject,lightPosWorld,&lightPosObject);

		//Updating shadow volumes is expensive, so verify that this volume is even visible.

		//Generate bounding box around shadow volume by extruding AABB corners
		Region3D boxCopy(*(const Region3D *)&meshBox);
		AABoxClass &box = *(AABoxClass *)&boxCopy;	//copy current mesh bounding box (will be smaller than shadow box).
		SphereClass sphere;			//rough bounding sphere of shadow volume - based on box.
		Vector3 Corners[8];
		Vector3 lightRay;
		Real vectorScale,vectorScaleTemp, vectorScaleMax;
		Real length;

		//Get vertices of top of bounding box
		Corners[0]=box.Center+box.Extent;	//top right corner
		Corners[1]=Corners[0];
		Corners[1].X -= 2.0f*box.Extent.X;		//top left corner
		Corners[2]=Corners[1];
		Corners[2].Y -= 2.0f*box.Extent.Y;		//bottom left corner
		Corners[3]=Corners[2];
		Corners[3].X += 2.0f*box.Extent.X;		//bottom right corner

		//Project top volume corners onto ground plane
		lightRay = Corners[0] - lightPosWorld;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScaleMax=vectorScale=(Real)fabs((Corners[0].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[4]=Corners[0]+lightRay*vectorScale;
		vectorScaleMax *= length;

		lightRay = Corners[1] - lightPosWorld;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScaleTemp=(Real)fabs((Corners[1].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[5]=Corners[1]+lightRay*vectorScaleTemp;
		vectorScaleTemp *= length;

		if (vectorScaleTemp > vectorScaleMax)
			vectorScaleMax=vectorScaleTemp;	//keep track of maximum required extrusion length.

		lightRay = Corners[2] - lightPosWorld;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScale=(Real)fabs((Corners[2].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[6]=Corners[2]+lightRay*vectorScale;
		vectorScale *= length;

		if (vectorScale > vectorScaleMax)
			vectorScaleMax=vectorScale;	//keep track of maximum required extrusion length.

		lightRay = Corners[3] - lightPosWorld;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScaleTemp=(Real)fabs((Corners[3].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[7]=Corners[3]+lightRay*vectorScaleTemp;
		vectorScaleTemp *= length;

		if (vectorScaleTemp > vectorScaleMax)
			vectorScaleMax=vectorScaleTemp;	//keep track of maximum required extrusion length.

		box.Init(Corners, 8);	//generate a new bounding box
		sphere.Init(box.Center,box.Extent.Length());	//generate object space bounding sphere containing box.

		CollisionMath::OverlapType result=CollisionMath::Overlap_Test(*shadowCameraFrustum,sphere);
		if (result == CollisionMath::OVERLAPPED)	//do a more accurate test
			result=CollisionMath::Overlap_Test(*shadowCameraFrustum, box);
		
		if (result != CollisionMath::OUTSIDE)
		{
			//
			// reset the silhouette data and build a new one from this light
			// source perspective
			//

			if (m_numSilhouetteIndices[meshIndex] != 0)
			{	//this silhouette was built before and is being updated.
				//this probably means it will change again in the future.
				//make future updates faster by pre-caching face normals.
			((W3DShadowGeometryMesh *)(meshIndex * sizeof(Rva007BE000MeshRecordView) +
				(unsigned int)((W3DVolumetricShadow *)((char *)this + 0x30))->m_geometry + 0x14))->buildPolygonNormals();
			}
			m_numSilhouetteIndices[meshIndex] = 0;
			buildSilhouette(meshIndex, &lightPosObject);

			//
			// in a multiple shadow situation we would be allocating a volume
			// for this current shadow light, not the 0 index volume all the time
			//
			if (!m_shadowVolume[ lightIndex ][meshIndex])
				allocateShadowVolume( lightIndex,meshIndex, allocationFlags );
			if( m_shadowVolumeVB[ lightIndex ][meshIndex] )
			{	//Updating an existing vertex buffer shadow volume.  This means we're
				//probably dealing with an animated mesh.  Update flags to reflect this fact.
				if (isMeshRotating || isLightMoving)
				{
					if (isMeshRotating)
					{	//rotating meshes will most likely need updates each frame, so stop using static vertex buffers.
						m_shadowVolume[ lightIndex ][meshIndex]->SetFlags(
							m_shadowVolume[ lightIndex ][meshIndex]->GetFlags() | SHADOW_DYNAMIC);
					}
					//release memory used to store vertices/polygons
					((Rva000F26DC *)this)->rva000F074E( lightIndex,meshIndex );	//free vertex buffers since not used for dynamic.
					//Resize the shadow volume since we'll need room to store the vertices in memory instead of VB.
					allocateShadowVolume( lightIndex,meshIndex, 0 );
				}
			}

			//
			// construct the shadow volume at this light position in the
			// passed shadow volume geometry index
			//
			if (m_shadowVolume[ lightIndex ][meshIndex]->GetFlags() & SHADOW_DYNAMIC)
				constructVolume( &lightPosObject, vectorScaleMax, lightIndex, meshIndex );
			else
				constructVolumeVB( &lightPosObject, vectorScaleMax, lightIndex, meshIndex );

			//
			// store the current light position and orientation that
			// we constructed shadow info at
			//
			m_objectXformHistory[ lightIndex ][meshIndex] = objectToWorld;
			m_lightPosHistory[lightIndex][meshIndex] = lightPosWorld;

			box.Translate(-objectCenter);	//translate box to object space.
			m_shadowVolume[ lightIndex ][meshIndex]->setBoundingBox(box);
			sphere.Center -= objectCenter;
			m_shadowVolume[ lightIndex ][meshIndex]->setBoundingSphere(sphere);
			m_shadowVolume[ lightIndex ][meshIndex]->setVisibleState(Geometry::STATE_VISIBLE);	//this volume needs rendering.
		}//end if inside view frustum
		else
		if (m_shadowVolume[ lightIndex ][meshIndex])
		{	//outside view frustum, shadow wasn't updated.
			box.Translate(-objectCenter);	//translate box to object space.
			m_shadowVolume[ lightIndex ][meshIndex]->setBoundingBox(box);
			sphere.Center -= objectCenter;
			m_shadowVolume[ lightIndex ][meshIndex]->setBoundingSphere(sphere);
			m_shadowVolume[ lightIndex ][meshIndex]->setVisibleState(Geometry::STATE_INVISIBLE);
		}
	}  // end if
	else
	{	//not reconstructing volume, so don't know if visible or not.
		if (m_shadowVolume[ lightIndex ][meshIndex])
			m_shadowVolume[ lightIndex ][meshIndex]->setVisibleState(Geometry::STATE_UNKNOWN);
	}
}
