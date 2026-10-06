// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
/*
** MeshModelClass::Load_W3D, retail 0x0018BA10 (875 bytes). Dedicated TU:
** marker-less meshmdlio.cpp cannot take rows (PostProcess precedent).
**
** Target facts (retail 0x18BA10, 875B, 2-ret, decoded via capstone):
** - Calls Open_Chunk 0x614F50, Cur_Chunk_ID 0x615020, Read 0x6151A0,
**   Close_Chunk 0x614FC0 (all matched chunkio.cpp rows).
** - push 0x24C + call 0x2FDA0 (scalar new, symbols pin ??2) + ctor 0x18B5F0
**   (matched MeshLoadContextCtor) for MeshLoadContext (sizeof 0x24C).
** - push 0x74 + Read + cmp 0x74 (sizeof W3dMeshHeader3Struct).
** - Reset call 0x171F70 with 4 pushes: NumTris [ebx+0x28], NumVertices
**   [ebx+0x2C], 1, skinBool from (Attributes&0xFF0000)==0x20000 (sete).
** - tmpname via push len + call 0x2FDE0 (array new ??_U pin), memset inlined
**   as rep stosd/stosb, strcpy/strcat inlined as rep movsd/movsb + "." word
**   from string literal, Set_Name call 0x16A6C0 (matched), delete[] via
**   0x2FD80 (??_V pin).
** - AlternateMatDesc stores to [ebx+0x128]/[ebx+0x12C] from VertexCount
**   [ebp+0x28]/PolyCount [ebp+0x24] (inlined Set_Vertex/Polygon_Count).
** - BoundBox/Sphere via movss (Vector3::Set inlined, /arch:SSE).
** - Flags ORs to [ebp+0x18..0x1A] matching FlagsType: 0x200 ALIGNED,
**   0x400+0x10000 SKIN+ALLOW_NPATCHES, 0x800 ORIENTED, 0x100 TWO_SIDED,
**   0x1000 CAST_SHADOW, 0x10000 ALLOW_NPATCHES (NPATCHABLE), 0x4000
**   PRELIT_LIGHTMAP_MULTI_PASS (obsolete 0x4000).
** - Prelit switch via mov eax,[0xDB5F88] (global, target G00DB5F88=1) with
**   sub/je chain, PrelitChunkID stores 0x26/0x25/0x24/0x23 to [ebx+0x88].
** - read_chunks call 0x18B790 (pinned, bool 2-arg, ret8) with this + cload
**   + context; pre-3.0 skin fixup via get_bone_links 0x16A0C0 (matched);
**   cull-tree via test [ebp+0x20]&0xFF0 + cmp [ebp+0x88],0 + call 0x16AD10.
** - install_materials call 0x18A070 (pinned, void 1-arg, ret4); dtor 0x18B180
**   (matched) + delete 0x2FD60 (??3 pin); post_process 0x189C60 (matched).
** - Early ret at +0x82 (Error, AL=0), main ret at +0x368 (AL=1), ret4.
**
** Donor facts (BFME1 6583b3c1, clean):
** - game/Libraries/Source/WWVegas/WW3D2/meshmdlio.cpp:244 Load_W3D body
**   (WW3DErrorType, 3-arg Reset, W3DNEWARRAY, Set_Name, AlternateMatDesc
**   Sets, BoundBox/Sphere Sets, Flags via Set_Flag, prelit via
**   WW3D Get_Prelit_Mode() switch with fall-through, read_chunks,
**   pre-3.0 bone fixup, cull-tree, install_materials, delete, post_process).
** - meshmdl.h:244+ Reset/Load_W3D/read_chunks/install_materials/post_process
**   decls; Def/Alternate/Cur/MatInfo tail order.
** - meshgeometry.h Flags enum + 0x8C base layout; w3d_file.h constants
**   (HEADER3 0x1F, PRELIT chunks 0x23-0x26, GEOM_MASK 0xFF0000/SKIN 0x20000,
**   COLL_MASK 0xFF0/SHIFT 4, TWO_SIDED 0x2000, CAST_SHADOW 0x8000,
**   NPATCHABLE 0x20000000, OBSOLETE 0x4000, PRELIT_MASK 0xF000000 etc.)
**   + W3dMeshHeader3Struct (sizeof 0x74); ww3d.h PrelitModeEnum +
**   inline Get_Prelit_Mode returning PrelitMode (init MULTI_PASS=1).
** - ZH GeneralsMD meshmdlio.cpp:239 same Load_W3D (semantic guide only,
**   never port source).
**
** Inferences (separate from facts above):
** - 0x18B790 is MeshModel::read_chunks-with-context: dispatcher shape with
**   jump tables calling 10+ known MeshModel/geometry readers (1896D0, 18A750,
**   16B020, 189790, 16B0E0, 188760, 16B1A0, 16B3C0, 18B4F0, 18AC90, 18AD40,
**   18AF70, 18AE50, 18B400, 16AF80, 16AF40, 1693A0, 16AFD0, 16AE70) + bool
**   ret8 ABI + call position after prelit (donor calls read_chunks there).
** - 0x18A070 is MeshModel::install_materials: calls install_alternate
**   0x188290 (matched), PRELIT_VERTEX flag test, Post_Load_Process 0x15BB00
**   x2, texture/material transfer loops via Peek 0x188700 + Add 0x16FBF0 +
**   vector virtuals, void ret4 ABI + call position after cull-tree (donor
**   calls install_materials there).
** - G00DB5F88 (target, 0xDB5F88=1) is WW3D::PrelitMode storage (donor);
**   direct global load in C++ reproduces inlined Get_Prelit_Mode().
** - Bool ABI (AL=1/0) replaces donor WW3DErrorType; 4-arg Reset with skin
**   bool replaces donor 3-arg; Set_Name at +0x10 (not Set_User_Text).
*/
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "sphere.h"
#include "multilist.h"
#include "w3d_file.h"
#include "chunkio.h"
#include "wwdebug.h"
#include <string.h>

class AABTreeClass;
typedef Vector3i16 TriIndex;

// Target-established prelit-mode storage at 0xDB5F88 (ConstGlobalGetters2
// G00DB5F88=1). Donor WW3D Get_Prelit_Mode() inlines to this load; direct
// reference reproduces retail's mov eax,[0xDB5F88] + sub/je chain.
extern int G00DB5F88;

class MeshMatDescClass
{
public:
	void Set_Vertex_Count(int v) { VertexCount = v; }
	void Set_Polygon_Count(int p) { PolyCount = p; }
	int PassCount;
	int VertexCount;
	int PolyCount;
	char m_pad[0x118 - 12];
};

typedef char MeshMatDescSizeCheck[sizeof(MeshMatDescClass) == 0x118 ? 1 : -1];

class MeshLoadContextClass
{
	friend class MeshModelClass;
private:
	MeshLoadContextClass(void);
	~MeshLoadContextClass(void);
public:
	W3dMeshHeader3Struct Header;
	char m_pad0[0x88 - 0x74];
	uint32 PrelitChunkID;
	char m_pad1[0x124 - 0x8C];
	MeshMatDescClass AlternateMatDesc;
	char m_pad2[0x24C - 0x124 - 0x118];
};

typedef char MeshLoadContextSizeCheck[sizeof(MeshLoadContextClass) == 0x24C ? 1 : -1];

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	enum FlagsType
	{
		DIRTY_BOUNDS = 0x00000001,
		DIRTY_PLANES = 0x00000002,
		DIRTY_VNORMALS = 0x00000004,
		SORT = 0x00000010,
		DISABLE_BOUNDING_BOX = 0x00000020,
		DISABLE_BOUNDING_SPHERE = 0x00000040,
		DISABLE_PLANE_EQ = 0x00000080,
		TWO_SIDED = 0x00000100,
		ALIGNED = 0x00000200,
		SKIN = 0x00000400,
		ORIENTED = 0x00000800,
		CAST_SHADOW = 0x00001000,
		PRELIT_MASK = 0x0000E000,
		PRELIT_VERTEX = 0x00002000,
		PRELIT_LIGHTMAP_MULTI_PASS = 0x00004000,
		PRELIT_LIGHTMAP_MULTI_TEXTURE = 0x00008000,
		ALLOW_NPATCHES = 0x00010000,
	};

	virtual bool Load_W3D(ChunkLoadClass &cload);
	void Set_Name(const char *newname);
	void Set_Flag(int flag, bool onoff) { if (onoff) { Flags |= flag; } else { Flags &= ~flag; } }
	int Get_Flag(int flag) { return Flags & flag; }
	int Get_Vertex_Count(void) { return VertexCount; }
protected:
	uint16 *get_bone_links(bool create = true);
	void Generate_Culling_Tree(void);
	ShareBufferClass<char> *MeshName;
	ShareBufferClass<char> *UserText;
	int Flags;
	char SortLevel;
	uint32 W3dAttributes;
	int PolyCount;
	int VertexCount;
	ShareBufferClass<TriIndex> *Poly;
	ShareBufferClass<Vector3> *Vertex;
	ShareBufferClass<Vector3> *VertexAlternate;
	ShareBufferClass<Vector3> *VertexNorm;
	ShareBufferClass<Vector3> *AlternateVertexNorm;
	ShareBufferClass<Vector3> *VertexTangents;
	ShareBufferClass<Vector3> *VertexBinormals;
	ShareBufferClass<Vector4> *PlaneEq;
	ShareBufferClass<uint32> *VertexShadeIdx;
	ShareBufferClass<uint16> *VertexBoneLink;
	ShareBufferClass<uint16> *UnknownBuffer54;
	ShareBufferClass<uint8> *PolySurfaceType;
	RefCountClass *UnknownBuffer5C;
	Vector3 BoundBoxMin;
	Vector3 BoundBoxMax;
	Vector3 BoundSphereCenter;
	float BoundSphereRadius;
	AABTreeClass *CullTree;
};

class MeshModelClass : public MeshGeometryClass
{
public:
	virtual bool Load_W3D(ChunkLoadClass &cload);
	void Reset(int polycount, int vertcount, int passcount, bool skinned);
protected:
	bool read_chunks(ChunkLoadClass &cload, MeshLoadContextClass *context);
	void install_materials(MeshLoadContextClass *context);
	void post_process(void);
};

bool MeshModelClass::Load_W3D(ChunkLoadClass &cload)
{
	MeshLoadContextClass *context = NULL;

	cload.Open_Chunk();

	if (cload.Cur_Chunk_ID() != W3D_CHUNK_MESH_HEADER3) {
		WWDEBUG_SAY(("Old format mesh mesh, no longer supported.\n"));
		goto Error;
	}

	context = new MeshLoadContextClass;

	if (cload.Read(&(context->Header), sizeof(W3dMeshHeader3Struct)) != sizeof(W3dMeshHeader3Struct)) {
		goto Error;
	}
	cload.Close_Chunk();

	char *tmpname;
	int namelen;

	Reset(context->Header.NumTris, context->Header.NumVertices, 1,
		(context->Header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK) == W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN);

	namelen = strlen(context->Header.ContainerName);
	namelen += strlen(context->Header.MeshName);
	namelen += 2;
	W3dAttributes = context->Header.Attributes;
	SortLevel = context->Header.SortLevel;
	tmpname = W3DNEWARRAY char[namelen];
	memset(tmpname, 0, namelen);

	if (strlen(context->Header.ContainerName) > 0) {
		strcpy(tmpname, context->Header.ContainerName);
		strcat(tmpname, ".");
	}
	strcat(tmpname, context->Header.MeshName);

	Set_Name(tmpname);

	delete[] tmpname;
	tmpname = NULL;

	context->AlternateMatDesc.Set_Vertex_Count(VertexCount);
	context->AlternateMatDesc.Set_Polygon_Count(PolyCount);

	BoundBoxMin.Set(context->Header.Min.X, context->Header.Min.Y, context->Header.Min.Z);
	BoundBoxMax.Set(context->Header.Max.X, context->Header.Max.Y, context->Header.Max.Z);

	BoundSphereCenter.Set(context->Header.SphCenter.X, context->Header.SphCenter.Y, context->Header.SphCenter.Z);
	BoundSphereRadius = context->Header.SphRadius;

	if (context->Header.Version >= W3D_MAKE_VERSION(4, 1)) {
		int geometry_type = context->Header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK;
		switch (geometry_type) {
		case W3D_MESH_FLAG_GEOMETRY_TYPE_NORMAL:
			break;
		case W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ALIGNED:
			Set_Flag(ALIGNED, true);
			break;
		case W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ORIENTED:
			Set_Flag(ORIENTED, true);
			break;
		case W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN:
			Set_Flag(SKIN, true);
			Set_Flag(ALLOW_NPATCHES, true);
			break;
		}
	}

	if (context->Header.Attributes & W3D_MESH_FLAG_TWO_SIDED) {
		Set_Flag(TWO_SIDED, true);
	}

	if (context->Header.Attributes & W3D_MESH_FLAG_CAST_SHADOW) {
		Set_Flag(CAST_SHADOW, true);
	}

	if (context->Header.Attributes & W3D_MESH_FLAG_NPATCHABLE) {
		Set_Flag(ALLOW_NPATCHES, true);
	}

	if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_MASK) {
		switch (G00DB5F88) {
		case 2:
			if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_LIGHTMAP_MULTI_TEXTURE) {
				context->PrelitChunkID = W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_TEXTURE;
				Set_Flag(PRELIT_LIGHTMAP_MULTI_TEXTURE, true);
				break;
			}
		case 1:
			if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_LIGHTMAP_MULTI_PASS) {
				context->PrelitChunkID = W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_PASS;
				Set_Flag(PRELIT_LIGHTMAP_MULTI_PASS, true);
				break;
			}
		case 0:
			if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_VERTEX) {
				context->PrelitChunkID = W3D_CHUNK_PRELIT_VERTEX;
				Set_Flag(PRELIT_VERTEX, true);
				break;
			}
		default:
			WWASSERT(context->Header.Attributes & W3D_MESH_FLAG_PRELIT_UNLIT);
			context->PrelitChunkID = W3D_CHUNK_PRELIT_UNLIT;
			break;
		}
	} else {
		if (context->Header.Attributes & OBSOLETE_W3D_MESH_FLAG_LIGHTMAPPED) {
			Set_Flag(PRELIT_LIGHTMAP_MULTI_PASS, true);
		}
	}

	read_chunks(cload, context);

	if ((context->Header.Version < W3D_MAKE_VERSION(3, 0)) && (Get_Flag(SKIN))) {
		uint16 *links = get_bone_links();
		WWASSERT(links);
		for (int bi = 0; bi < Get_Vertex_Count(); bi++) {
			links[bi] += 1;
		}
	}

	if ((((W3dAttributes & W3D_MESH_FLAG_COLLISION_TYPE_MASK) >> W3D_MESH_FLAG_COLLISION_TYPE_SHIFT) != 0) &&
		(CullTree == NULL)) {
		Generate_Culling_Tree();
	}

	install_materials(context);

	delete context;

	post_process();

	return true;

Error:
	return false;
}
