// ?Load_W3D@MeshModelClass@@IAE_NAAVChunkLoadClass@@@Z
// partial score=0.9 date=2026-10-05
// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?Load_W3D@MeshModelClass@@IAE_NAAVChunkLoadClass@@@Z, retail 0x0018BA10
// (code through ret C2 04 00 at 0x18BD78).
// BFME1 MeshModelClass_Load_W3D.cpp port (their 0x00970340 row) with BFME2
// rewrites (all retail-measured from the 0x18BA10 body):
// - Bool returns; Error paths return false with no Close_Chunk.
// - Reset takes (NumTris, NumVertices, 1, type == SKIN) per the matched
//   ?Reset@MeshModelClass@@QAEXHHH_N@Z row; the skin bit feeds Flags byte19/2.
// - Set_Name (matched 0x16A6C0), not Set_User_Text; no AlternateMatDesc
//   setter calls -- VertexCount/PolyCount land directly at context+0x128/+0x12C.
// - Bounding volumes are direct float stores (movss), no .Set calls.
// - Single Flags dword at this+0x18 with byte-sized ors (union view):
//   ALIGNED type -> byte19|=2, SKIN type -> dword|=0x10400, ORIENTED type ->
//   byte19|=8, TWO_SIDED -> byte19|=1, CAST_SHADOW -> byte19|=0x10,
//   NPATCHABLE -> byte1A|=1, PRELIT_MULTI_TEXTURE -> dword|=0x8000,
//   PRELIT_MULTI_PASS -> byte19|=0x40, PRELIT_VERTEX -> dword|=0x2000,
//   OBSOLETE_LIGHTMAPPED -> byte19|=0x40; SKIN test is byte19&4.
// - Prelit mode switch with ZH fallthrough; mode global via WW3D::PrelitMode.
// - Tail: bone-link fixup (get_bone_links() default true), culling-tree
//   generation, install_materials pin 0x18A070, context delete, post_process.
// Dedicated TU: marker-less meshmdlio.cpp cannot take rows (PostProcess precedent).

#include <string.h>

#ifndef NULL
#define NULL 0
#endif

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int sint32;
typedef float float32;

#define W3D_NAME_LEN 16
#define W3D_MAKE_VERSION(major, minor) (((major) << 16) | (minor))

#define W3D_MESH_FLAG_TWO_SIDED 0x00002000
#define OBSOLETE_W3D_MESH_FLAG_LIGHTMAPPED 0x00004000
#define W3D_MESH_FLAG_CAST_SHADOW 0x00008000
#define W3D_MESH_FLAG_GEOMETRY_TYPE_MASK 0x00FF0000
#define W3D_MESH_FLAG_GEOMETRY_TYPE_NORMAL 0x00000000
#define W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ALIGNED 0x00010000
#define W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN 0x00020000
#define W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ORIENTED 0x00060000
#define W3D_MESH_FLAG_PRELIT_MASK 0x0F000000
#define W3D_MESH_FLAG_PRELIT_LIGHTMAP_MULTI_TEXTURE 0x08000000
#define W3D_MESH_FLAG_PRELIT_LIGHTMAP_MULTI_PASS 0x04000000
#define W3D_MESH_FLAG_PRELIT_VERTEX 0x02000000
#define W3D_MESH_FLAG_NPATCHABLE 0x20000000
#define W3D_MESH_FLAG_COLLISION_TYPE_MASK 0x00000FF0
#define W3D_MESH_FLAG_COLLISION_TYPE_SHIFT 4

#define W3D_CHUNK_MESH_HEADER3 0x1F
#define W3D_CHUNK_PRELIT_UNLIT 0x23
#define W3D_CHUNK_PRELIT_VERTEX 0x24
#define W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_PASS 0x25
#define W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_TEXTURE 0x26

struct W3dVectorStruct
{
	float32 X;
	float32 Y;
	float32 Z;
};

struct W3dMeshHeader3Struct
{
	uint32 Version;
	uint32 Attributes;
	char MeshName[W3D_NAME_LEN];
	char ContainerName[W3D_NAME_LEN];
	uint32 NumTris;
	uint32 NumVertices;
	uint32 NumMaterials;
	uint32 NumDamageStages;
	sint32 SortLevel;
	uint32 PrelitVersion;
	uint32 FutureCounts[1];
	uint32 VertexChannels;
	uint32 FaceChannels;
	W3dVectorStruct Min;
	W3dVectorStruct Max;
	W3dVectorStruct SphCenter;
	float32 SphRadius;
};

struct Vector3
{
	float X;
	float Y;
	float Z;
};

class ChunkLoadClass
{
public:
	bool Open_Chunk();
	unsigned long Cur_Chunk_ID();
	unsigned long Read(void *dst, unsigned long size);
	bool Close_Chunk();
};

class MeshLoadContextClass
{
	friend class MeshModelClass;
	MeshLoadContextClass();
	~MeshLoadContextClass();
public:
	W3dMeshHeader3Struct Header;
	char m_pad74[0x88 - 0x74];
	uint32 PrelitChunkID;
	char m_pad8C[0x128 - 0x8C];
	int AltVertexCount;
	int AltPolyCount;
	char m_tail[0x24C - 0x130];
};

class MeshGeometryClass
{
private:
	virtual ~MeshGeometryClass();
public:
	void Set_Name(const char *newname);
protected:
	uint16 *get_bone_links(bool create = true);
	void Generate_Culling_Tree();
	int Get_Vertex_Count() const { return VertexCount; }

	void *MeshNamePtr;
	void *UserTextPtr;
	union {
		unsigned Flags;
		unsigned char FlagBytes[4];
	};
	char SortLevel;
	char m_pad1D[3];
	uint32 W3dAttributes;
	int PolyCount;
	int VertexCount;
	char m_pad2C[0x60 - 0x2C];
	Vector3 BoundBoxMin;
	Vector3 BoundBoxMax;
	Vector3 BoundSphereCenter;
	float BoundSphereRadius;
	void *CullTree;
};

class MeshModelClass : public MeshGeometryClass
{
public:
	void Reset(int polycount, int vertcount, int passcount, bool skinned);
protected:
	bool Load_W3D(ChunkLoadClass &cload);
	bool read_chunks(ChunkLoadClass &cload, MeshLoadContextClass *context);
	void install_materials(MeshLoadContextClass *context);
	void post_process();
};

class WW3D
{
public:
	enum PrelitModeEnum {
		PRELIT_MODE_VERTEX,
		PRELIT_MODE_LIGHTMAP_MULTI_PASS,
		PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE
	};
	static PrelitModeEnum PrelitMode;
	static PrelitModeEnum Get_Prelit_Mode() { return PrelitMode; }
};

// ?Load_W3D@MeshModelClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshModelClass::Load_W3D(ChunkLoadClass &cload)
{
	cload.Open_Chunk();
	MeshLoadContextClass *context = NULL;
	char *tmpname;
	int namelen;

	if (cload.Cur_Chunk_ID() != W3D_CHUNK_MESH_HEADER3) {
		goto Error;
	}

	context = new MeshLoadContextClass;
	if (cload.Read(&(context->Header), sizeof(W3dMeshHeader3Struct)) != sizeof(W3dMeshHeader3Struct)) {
		goto Error;
	}
	cload.Close_Chunk();

	Reset(context->Header.NumTris, context->Header.NumVertices, 1,
		(context->Header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK) == W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN);

	namelen = strlen(context->Header.ContainerName);
	namelen += strlen(context->Header.MeshName);
	namelen += 2;
	W3dAttributes = context->Header.Attributes;
	SortLevel = context->Header.SortLevel;
	tmpname = new char[namelen];
	memset(tmpname, 0, namelen);

	if (strlen(context->Header.ContainerName) > 0) {
		strcpy(tmpname, context->Header.ContainerName);
		strcat(tmpname, ".");
	}
	strcat(tmpname, context->Header.MeshName);

	Set_Name(tmpname);
	delete[] tmpname;
	tmpname = NULL;

	context->AltVertexCount = VertexCount;
	context->AltPolyCount = PolyCount;

	BoundBoxMin.X = context->Header.Min.X;
	BoundBoxMin.Y = context->Header.Min.Y;
	BoundBoxMin.Z = context->Header.Min.Z;
	BoundBoxMax.X = context->Header.Max.X;
	BoundBoxMax.Y = context->Header.Max.Y;
	BoundBoxMax.Z = context->Header.Max.Z;
	BoundSphereCenter.X = context->Header.SphCenter.X;
	BoundSphereCenter.Y = context->Header.SphCenter.Y;
	BoundSphereCenter.Z = context->Header.SphCenter.Z;
	BoundSphereRadius = context->Header.SphRadius;

	if (context->Header.Version >= W3D_MAKE_VERSION(4, 1)) {
		int geometry_type = context->Header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK;
		switch (geometry_type) {
		case W3D_MESH_FLAG_GEOMETRY_TYPE_NORMAL:
			break;
		case W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ALIGNED:
			FlagBytes[1] |= 2;
			break;
		case W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN:
			Flags |= 0x10400;
			break;
		case W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ORIENTED:
			FlagBytes[1] |= 8;
			break;
		}
	}

	if (context->Header.Attributes & W3D_MESH_FLAG_TWO_SIDED) {
		FlagBytes[1] |= 1;
	}
	if (context->Header.Attributes & W3D_MESH_FLAG_CAST_SHADOW) {
		FlagBytes[1] |= 0x10;
	}
	if (context->Header.Attributes & W3D_MESH_FLAG_NPATCHABLE) {
		FlagBytes[2] |= 1;
	}

	if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_MASK) {
		switch (WW3D::Get_Prelit_Mode()) {
		case WW3D::PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE:
			if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_LIGHTMAP_MULTI_TEXTURE) {
				context->PrelitChunkID = W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_TEXTURE;
				Flags |= 0x8000;
				break;
			}
		case WW3D::PRELIT_MODE_LIGHTMAP_MULTI_PASS:
			if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_LIGHTMAP_MULTI_PASS) {
				context->PrelitChunkID = W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_PASS;
				FlagBytes[1] |= 0x40;
				break;
			}
		case WW3D::PRELIT_MODE_VERTEX:
			if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_VERTEX) {
				context->PrelitChunkID = W3D_CHUNK_PRELIT_VERTEX;
				Flags |= 0x2000;
				break;
			}
		default:
			context->PrelitChunkID = W3D_CHUNK_PRELIT_UNLIT;
			break;
		}
	} else {
		if (context->Header.Attributes & OBSOLETE_W3D_MESH_FLAG_LIGHTMAPPED) {
			FlagBytes[1] |= 0x40;
		}
	}

	read_chunks(cload, context);

	if ((context->Header.Version < W3D_MAKE_VERSION(3, 0)) && (FlagBytes[1] & 4)) {
		uint16 *links = get_bone_links();
		for (int bi = 0; bi < VertexCount; bi++) {
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
