// cl: /DNDEBUG /MD /GX-
//
// ?read_texture_stage@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018B080 (247 bytes: code through ret C2 08 00 at 0x18B0E9/0x18B11C,
// jump table at 0x18B120, case map at 0x18B130).
// BFME1 meshmdlio.cpp read_texture_stage port with BFME2 rewrites (all
// retail-measured from the 0x18B080 body):
// - Bool returns with direct `!= true` checks (no error variable; retail
//   tests al directly after each reader call).
// - PER_FACE arm is a BFME2-inline Seek-if-size-matches block (PolyCount*12
//   via [this+0x24], Seek pin at 0x6150C0), not BFME1's read_per_face call.
// - CurTexStage++ at context+0x90 via mem-add (/G7).
// - Chunk IDs: TEXCOORDS 0x05 (w3d_obsolete.h:55), TEXTURE_IDS 0x49,
//   STAGE_TEXCOORDS 0x4A, PER_FACE_TEXCOORD_IDS 0x4B.
// - read_texture_ids resolves via pin at 0x189140 (banked 0.75 stash; pin to
//   row coexistence on its landing); read_stage_texcoords via matched row;
//   Open_Chunk/Close_Chunk/Cur_Chunk_ID/Cur_Chunk_Length via matched rows.
// Dedicated TU: marker-less meshmdlio.cpp cannot take rows (PostProcess
// precedent). Frameless, no EH temps.

class ChunkLoadClass
{
public:
	bool Open_Chunk();
	unsigned long Cur_Chunk_ID();
	bool Close_Chunk();
	unsigned long Cur_Chunk_Length();
	unsigned long Seek(unsigned long pos);
};

class MeshLoadContextClass
{
	virtual ~MeshLoadContextClass();
	char m_pad0[0x90 - 4];
public:
	int CurTexStage;
};

class MeshModelClass
{
	virtual ~MeshModelClass();
	char m_pad0[0x24 - 4];
public:
	int PolyCount;
	int Get_Polygon_Count() const { return PolyCount; }
protected:
	bool read_texture_stage(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_texture_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_stage_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context);
};

enum MeshTextureStageChunkID
{
	W3D_CHUNK_TEXCOORDS = 0x05,
	W3D_CHUNK_TEXTURE_IDS = 0x49,
	W3D_CHUNK_STAGE_TEXCOORDS = 0x4A,
	W3D_CHUNK_PER_FACE_TEXCOORD_IDS = 0x4B
};

// ?read_texture_stage@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_texture_stage(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	while (cload.Open_Chunk()) {
		bool error = true;
		switch (cload.Cur_Chunk_ID()) {
		case W3D_CHUNK_TEXTURE_IDS:
			error = read_texture_ids(cload, context);
			break;
		case W3D_CHUNK_STAGE_TEXCOORDS:
		case W3D_CHUNK_TEXCOORDS:
			error = read_stage_texcoords(cload, context);
			break;
		case W3D_CHUNK_PER_FACE_TEXCOORD_IDS:
			{
				int size = Get_Polygon_Count() * 12;
				if (cload.Cur_Chunk_Length() == (unsigned long)size) {
					cload.Seek(size);
				} else {
					error = false;
				}
			}
			break;
		}
		if (error != true) {
			return error;
		}
		cload.Close_Chunk();
	}
	context->CurTexStage++;
	return true;
}
