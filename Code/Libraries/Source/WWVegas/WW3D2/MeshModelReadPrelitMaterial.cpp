// cl: /DNDEBUG /MD /GX-
//
// ?read_prelit_material@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018B4F0 (249 bytes).
// BFME1 meshmdlio.cpp read_prelit_material port with BFME2 rewrites (all
// retail-measured from the 0x0018B4F0 body):
// - bool (AL) returns with a `bool error = true` local and direct
//   `!= true` checks, not WW3DErrorType (same idiom as the landed
//   MeshModelReadTextureStage.cpp unit; the whole MeshModel reader family
//   is bool in BFME2).
// - The MATERIAL_INFO arm is a BFME2-inline Read-plus-store block (16 bytes
//   into context MatInfo at +0x78, then CurMatDesc PassCount at this+0x94
//   from MatInfo PassCount), not BFME1's read_material_info call.
// - MatInfo at context+0x78 (PassCount/VertexMaterialCount/ShaderCount/
//   TextureCount), PrelitChunkID at context+0x88, CurMatDesc at this+0x94.
// - Switch over chunk IDs 0x28/0x29/0x2A/0x30/0x38 with a linker jump table
//   (masked DIR32); cases call the bool sibling readers.
// Dedicated TU: the enum-typed meshmdlio.cpp cannot take rows (PostProcess
// precedent). Pins for the three unlanded bool callees are harvested from
// the retail REL32 displacements at the switch cases (jump-table indices
// 2/3/4); read_shaders resolves via its matched row.

#ifndef NULL
#define NULL 0
#endif

typedef unsigned long ulong;
typedef unsigned int uint32;

struct W3dMaterialInfoStruct
{
	uint32 PassCount;
	uint32 VertexMaterialCount;
	uint32 ShaderCount;
	uint32 TextureCount;
};

class ChunkLoadClass
{
public:
	ulong Cur_Chunk_ID(void);
	bool Open_Chunk(void);
	bool Close_Chunk(void);
	ulong Read(void *dst, ulong size);
};

struct MeshMatDescClass
{
	int PassCount;
};

class MeshLoadContextClass
{
private:
	char m_pad0[0x78];
public:
	W3dMaterialInfoStruct MatInfo;
	uint32 PrelitChunkID;
};

class MeshModelClass
{
protected:
	virtual ~MeshModelClass();
	bool read_prelit_material(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_shaders(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_vertex_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_textures(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_material_pass(ChunkLoadClass &cload, MeshLoadContextClass *context);
	void Set_Pass_Count(int passes) { CurMatDesc->PassCount = passes; }

private:
	char m_pad[0x90];
	MeshMatDescClass *CurMatDesc;
};

enum
{
	W3D_CHUNK_MATERIAL_INFO = 0x28,
	W3D_CHUNK_SHADERS = 0x29,
	W3D_CHUNK_VERTEX_MATERIALS = 0x2A,
	W3D_CHUNK_TEXTURES = 0x30,
	W3D_CHUNK_MATERIAL_PASS = 0x38
};

// ?read_prelit_material@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_prelit_material(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	if (cload.Cur_Chunk_ID() == context->PrelitChunkID) {
		while (cload.Open_Chunk()) {
			bool error = true;
			switch (cload.Cur_Chunk_ID()) {
			case W3D_CHUNK_MATERIAL_INFO:
				if (cload.Read(&context->MatInfo, sizeof(W3dMaterialInfoStruct)) != sizeof(W3dMaterialInfoStruct)) {
					error = false;
				} else {
					Set_Pass_Count((int)context->MatInfo.PassCount);
					error = true;
				}
				break;
			case W3D_CHUNK_VERTEX_MATERIALS:
				error = read_vertex_materials(cload, context);
				break;
			case W3D_CHUNK_SHADERS:
				error = read_shaders(cload, context);
				break;
			case W3D_CHUNK_TEXTURES:
				error = read_textures(cload, context);
				break;
			case W3D_CHUNK_MATERIAL_PASS:
				error = read_material_pass(cload, context);
				break;
			default:
				break;
			}
			cload.Close_Chunk();
			if (error != true) {
				return error;
			}
		}
	}
	return true;
}
