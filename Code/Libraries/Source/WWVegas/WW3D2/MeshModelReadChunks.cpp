// cl: /O2 /G7 /DNDEBUG /MD /GX-
//
// ?read_chunks@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018B790 (code through ret C2 08 00 at 0x18B965/0x18B96E, jump
// tables at 0x18B974/0x18B9CC with case maps at 0x18B9A4/0x18B9E4).
// BFME1 MeshModelReadChunks.cpp port (their 516B row at 0x0096FF70) with BFME2
// rewrites (all retail-measured from the 0x18B790 body):
// - Bool returns with direct `error` idiom (bl preset 1 per chunk, assigned
//   from each reader call, tested after Close_Chunk).
// - MATERIAL_INFO (0x28) is an inlined 16B Read into context+0x78 whose first
//   dword lands at [this+0x94]->+0, not a read_material_info call.
// - Normals/vertices alternate formats 0xC00/0xC01 pass true; id 0x03 shares
//   the 0xC01 tail with a pushed false.
// - Extra BFME2 arms over ZH: 0x50 (opaque context reader), 0x60/0x61
//   (rowed Rva0016AF80/Rva0016AFD0 vertex readers), 0x90 AABTREE.
// - No SURRENDER_NORMALS/obsolete-material assert arms (release build).
// Dedicated TU: marker-less meshmdlio.cpp cannot take rows (PostProcess precedent).

#ifndef NULL
#define NULL 0
#endif

class ChunkLoadClass
{
public:
	bool Open_Chunk();
	unsigned long Cur_Chunk_ID();
	bool Close_Chunk();
	unsigned long Read(void *dst, unsigned long size);
};

class MeshLoadContextClass
{
private:
	virtual ~MeshLoadContextClass();
	char m_pad0[0x78 - 4];
public:
	unsigned long MatInfo[4];
};

class MeshGeometryClass
{
private:
	virtual ~MeshGeometryClass();
protected:
	bool read_vertices(ChunkLoadClass &cload, bool alternate_format);
	bool read_vertex_normals(ChunkLoadClass &cload, bool alternate_format);
	bool read_triangles(ChunkLoadClass &cload);
	bool read_user_text(ChunkLoadClass &cload);
	bool read_vertex_influences(ChunkLoadClass &cload);
	bool read_vertex_shade_indices(ChunkLoadClass &cload);
	bool read_aabtree(ChunkLoadClass &cload);
};

class Rva0016AF80
{
public:
	bool rva0016AF80(ChunkLoadClass &cload);
};

class Rva0016AFD0
{
public:
	bool rva0016AFD0(ChunkLoadClass &cload);
};

class MeshModelClass : public MeshGeometryClass
{
protected:
	bool read_chunks(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_v3_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_per_tri_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_vertex_colors(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_shaders(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_vertex_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_textures(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_material_pass(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_prelit_material(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_Rva0018AF70(ChunkLoadClass &cload, MeshLoadContextClass *context);

private:
	char m_pad0[0x94 - 4];
	unsigned long *CurMatDesc;
};

// ?read_chunks@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_chunks(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	while (cload.Open_Chunk()) {
		bool error = true;
		switch (cload.Cur_Chunk_ID()) {
		case 0x02:
			error = read_vertices(cload, false);
			break;
		case 0x03:
			error = read_vertex_normals(cload, false);
			break;
		case 0x05:
			error = read_texcoords(cload, context);
			break;
		case 0x15:
			error = read_v3_materials(cload, context);
			break;
		case 0x20:
			error = read_triangles(cload);
			break;
		case 0x21:
			error = read_per_tri_materials(cload, context);
			break;
		case 0x0C:
			error = read_user_text(cload);
			break;
		case 0x0D:
			error = read_vertex_colors(cload, context);
			break;
		case 0x0E:
			error = read_vertex_influences(cload);
			break;
		case 0x22:
			error = read_vertex_shade_indices(cload);
			break;
		case 0x23:
		case 0x24:
		case 0x25:
		case 0x26:
			read_prelit_material(cload, context);
			break;
		case 0x28:
			if (cload.Read(context->MatInfo, 16) != 16) {
				error = false;
				break;
			}
			*CurMatDesc = context->MatInfo[0];
			error = true;
			break;
		case 0x29:
			error = read_shaders(cload, context);
			break;
		case 0x2A:
			error = read_vertex_materials(cload, context);
			break;
		case 0x50:
			error = read_Rva0018AF70(cload, context);
			break;
		case 0x30:
			error = read_textures(cload, context);
			break;
		case 0x38:
			error = read_material_pass(cload, context);
			break;
		case 0x60:
			error = ((Rva0016AF80 *)this)->rva0016AF80(cload);
			break;
		case 0x90:
			read_aabtree(cload);
			break;
		case 0x61:
			error = ((Rva0016AFD0 *)this)->rva0016AFD0(cload);
			break;
		case 0xC00:
			error = read_vertices(cload, true);
			break;
		case 0xC01:
			error = read_vertex_normals(cload, true);
			break;
		default:
			break;
		}
		cload.Close_Chunk();
		if (error != true) {
			return error;
		}
	}
	return true;
}
