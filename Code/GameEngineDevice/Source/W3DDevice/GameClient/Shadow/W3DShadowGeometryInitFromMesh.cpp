// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?initFromMesh@W3DShadowGeometry@@QAEHPAVRenderObjClass@@HPAV1@@Z @0x000F1018 424B.
//
// W3DShadowGeometry::initFromMesh: appends one mesh to the shadow geometry,
// taking references on the mesh model's vertex and polygon arrays and
// folding duplicate vertices onto their first instance. Target evidence:
// retail 0x000F1018..0x000F11C0 (0x800C stack-probed frame, ret 0xC),
// called from initFromHLOD (0x000F1F60) per LOD sub-mesh and from
// W3DShadowGeometryManager::Load_Geom (0x000F27D3) for a bare mesh. Layout
// read from retail: mesh model at robj+0xC4 (flags +0x18, polygon/vertex
// counts +0x24/+0x28, index/vertex arrays +0x2C/+0x30), mesh records 0x34
// bytes from +0x14, m_meshCount/m_numTotalsVerts at +0x2094/+0x2098; the
// duplicate test compares against the 0.0f at 0x00BBAEAC; operator new[]
// is 0x0002FDE0.
// Donor: Open-BFME-1 W3DVolumetricShadow.cpp initFromMesh(RenderObjClass *,
// Int, W3DShadowGeometry *) (0x007BA2B0), the ZH body grown the BFME array
// references, alpha flag and per-mesh robj index; BFME 2 keeps the BFME 1
// statements and the ZH 0xffffffff memset fill.
#include <string.h>
typedef float Real;
typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;
#define FALSE 0
#define TRUE 1
#define NEW new

void * __cdecl operator new[](unsigned int size);
#define MAX_SHADOW_CASTER_MESHES	160
#define MAX_SHADOW_VOLUME_VERTS	16384

class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z);
	__forceinline Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Real Length2(void) const { return X*X + Y*Y + Z*Z; }
	Real X, Y, Z;
};
// Preserve retail SSE scheduling through the component setter without emitting conflicting Vector3 copies.
static __forceinline void ShadowSetPoint(Vector3 *v,Real x,Real y,Real z) { v->X=x; v->Y=y; v->Z=z; }
static __forceinline Vector3 ShadowSubtract(const Vector3 &a, const Vector3 &b) { Vector3 result; ShadowSetPoint(&result,a.X-b.X,a.Y-b.Y,a.Z-b.Z); return result; }

class RenderObjClass;
class W3DShadowGeometry;

struct MeshArrayView
{
	void *m_vtable;
	Int m_references;
	char m_opaque[4];
	const Vector3 *m_vertices;
};
struct MeshModelView
{
	char m_beforeFlags[0x18];
	unsigned int m_flags;
	char m_beforePolygonCount[8];
	Int m_polygonCount;
	Int m_vertexCount;
	MeshArrayView *m_indexArray;
	MeshArrayView *m_vertexArray;
};
struct MeshRenderView
{
	char m_beforeModel[0xc4];
	MeshModelView *m_model;
};

class W3DShadowGeometryMesh
{
public:
	MeshArrayView *m_indexArray;
	MeshArrayView *m_vertexArray;
	const Vector3 *m_verts;
	Int m_meshRobjIndex;
	char m_pad10[4];
	Int m_numVerts;
	Int m_numVertsTotal;
	Int m_numPolygons;
	UnsignedShort *m_parentVerts;
	char m_pad24[8];
	W3DShadowGeometry *m_parentGeometry;
	Bool m_alpha;
};

class W3DShadowGeometry
{
public:
	Int initFromMesh(RenderObjClass *robj, Int mesh_index, W3DShadowGeometry *parent_geometry);
private:
	char m_pad0[0x14];
	W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
	Int m_meshCount;
	Int m_numTotalsVerts;
};

Int W3DShadowGeometry::initFromMesh(RenderObjClass *robj, Int mesh_index, W3DShadowGeometry *parent_geometry)
{
	UnsignedShort vertParent[MAX_SHADOW_VOLUME_VERTS];
	W3DShadowGeometryMesh *mesh = &m_meshList[m_meshCount];
	mesh->m_meshRobjIndex = mesh_index;
	unsigned int flags = ((MeshRenderView *)robj)->m_model->m_flags;
	if (!(flags & 0x1000))
		return FALSE;
	mesh->m_alpha = (flags >> 10) & 1;
	MeshModelView *model = ((MeshRenderView *)robj)->m_model;
	mesh->m_numVertsTotal = model->m_vertexCount;
	MeshArrayView *vertexArray = model->m_vertexArray;
	if (vertexArray != 0)
		++vertexArray->m_references;
	mesh->m_vertexArray = vertexArray;
	mesh->m_verts = mesh->m_vertexArray->m_vertices;
	mesh->m_numPolygons = model->m_polygonCount;
	++model->m_indexArray->m_references;
	mesh->m_indexArray = model->m_indexArray;
	if (mesh->m_numVertsTotal > MAX_SHADOW_VOLUME_VERTS)
		return FALSE;

	memset(vertParent, 0xffffffff, sizeof(vertParent));
	Int uniqueCount = mesh->m_numVertsTotal;
	for (Int j = 0; j < mesh->m_numVertsTotal; ++j)
	{
		if (vertParent[j] != 0xffff)
			continue;
		const Vector3 *vertex = &mesh->m_verts[j];
		for (Int k = j + 1; k < mesh->m_numVertsTotal; ++k)
		{
			Vector3 delta(ShadowSubtract(*vertex,mesh->m_verts[k]));
			if (delta.Length2() == 0)
			{
				vertParent[k] = j;
				--uniqueCount;
			}
		}
		vertParent[j] = j;
	}

	mesh->m_parentVerts = NEW UnsignedShort[mesh->m_numVertsTotal];
	memcpy(mesh->m_parentVerts, vertParent, sizeof(UnsignedShort) * mesh->m_numVertsTotal);
	mesh->m_numVerts = uniqueCount;
	m_numTotalsVerts += uniqueCount;
	mesh->m_parentGeometry = parent_geometry;
	if (((MeshRenderView *)robj)->m_model->m_flags & 0x400)
		mesh->m_verts = 0;
	m_numTotalsVerts += uniqueCount;
	++m_meshCount;
	return TRUE;
}
