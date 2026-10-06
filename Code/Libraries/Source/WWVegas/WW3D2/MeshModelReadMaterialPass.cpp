// cl: /DNDEBUG /MD /GX-
//
// ?read_material_pass@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018B400 (175 bytes).
// BFME1 meshmdlio.cpp read_material_pass port with BFME2 rewrites (all
// retail-measured from the 0x0018B400 body):
// - bool (AL) returns with a per-case `bool ok` local and `!= true` checks
//   that return ok (al passthrough, no mov); the seven identical case tails
//   fold to one shared `cmp al,1` check and default skips it.
// - Reader cases in retail code layout order: 0x39/0x3A/0x3F/0x3B/0x3C/
//   0x48/0x4A, with a linker jump table (masked DIR32). SCG (0x3E) closes
//   and advances like default, but is explicit to preserve retail's duplicate
//   jump-table slot. Chunk 0x3F is undefined in w3d_file.h; its reader is the
//   opaque pin.
// - CurTexStage at context+0x90 zeroed on entry (DWORD store), CurPass at
//   context+0x8C incremented on success (mem-add).
// Dedicated TU: the enum-typed meshmdlio.cpp cannot take rows (PostProcess
// precedent). Callees resolve via matched rows (vertex_material_ids,
// shader_ids, texture_stage, Rva00189B50) plus committed pins (dcg, dig,
// opaque 0x3F reader).

#ifndef NULL
#define NULL 0
#endif

class ChunkLoadClass
{
public:
	unsigned long Cur_Chunk_ID(void);
	bool Open_Chunk(void);
	bool Close_Chunk(void);
};

class MeshLoadContextClass
{
private:
	char m_pad0[0x8C];
public:
	int CurPass;
	int CurTexStage;
};

class MeshModelClass
{
protected:
	virtual ~MeshModelClass();
	bool read_material_pass(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_vertex_material_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_shader_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_dcg(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_dig(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_Rva00188AF0(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_texture_stage(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_Rva00189B50(ChunkLoadClass &cload, MeshLoadContextClass *context);
};

enum
{
	W3D_CHUNK_VERTEX_MATERIAL_IDS = 0x39,
	W3D_CHUNK_SHADER_IDS = 0x3A,
	W3D_CHUNK_DCG = 0x3B,
	W3D_CHUNK_DIG = 0x3C,
	W3D_CHUNK_SCG = 0x3E,
	W3D_CHUNK_TEXTURE_STAGE = 0x48,
	W3D_CHUNK_STAGE_TEXCOORDS = 0x4A
};

// ?read_material_pass@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_material_pass(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	context->CurTexStage = 0;
	while (cload.Open_Chunk()) {
		switch (cload.Cur_Chunk_ID()) {
		case W3D_CHUNK_VERTEX_MATERIAL_IDS: {
			bool ok = read_vertex_material_ids(cload, context);
			if (ok != true) {
				return ok;
			}
			break;
		}
		case W3D_CHUNK_SHADER_IDS: {
			bool ok = read_shader_ids(cload, context);
			if (ok != true) {
				return ok;
			}
			break;
		}
		case W3D_CHUNK_SCG:
			cload.Close_Chunk();
			continue;
		case 0x3F: {
			bool ok = read_Rva00188AF0(cload, context);
			if (ok != true) {
				return ok;
			}
			break;
		}
		case W3D_CHUNK_DCG: {
			bool ok = read_dcg(cload, context);
			if (ok != true) {
				return ok;
			}
			break;
		}
		case W3D_CHUNK_DIG: {
			bool ok = read_dig(cload, context);
			if (ok != true) {
				return ok;
			}
			break;
		}
		case W3D_CHUNK_TEXTURE_STAGE: {
			bool ok = read_texture_stage(cload, context);
			if (ok != true) {
				return ok;
			}
			break;
		}
		case W3D_CHUNK_STAGE_TEXCOORDS: {
			bool ok = read_Rva00189B50(cload, context);
			if (ok != true) {
				return ok;
			}
			break;
		}
		default:
			break;
		}
		cload.Close_Chunk();
	}
	context->CurPass++;
	return true;
}
