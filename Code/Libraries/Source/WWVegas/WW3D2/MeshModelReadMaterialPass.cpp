// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_meshmdlio /Ireference/shims/bfmeshader /Ireference/shims/meshmatdesclayout /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/meshgeom /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/shims/bfmecamera
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
// Callees resolve via matched rows (vertex_material_ids,
// shader_ids, texture_stage, Rva00189B50) plus committed pins (dcg, dig,
// opaque 0x3F reader).

// Header family: meshmdlio.cpp's (the approved TU), so the body composes
// with it; the context view keeps only the pass counters this reader uses
// (+0x8C CurPass, +0x90 CurTexStage, the TU's MeshLoadContextClass names).
#include "always.h"
#include <meshmatdesc.h>
#include "texture.h"
#include "meshgeometry.h"
#include "meshmdl.h"
#include "chunkio.h"
#include "w3d_file.h"

class MeshLoadContextClass
{
private:
	char m_pad0[0x8C];
public:
	int CurPass;
	int CurTexStage;
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
		case 0x3F: { // undefined in w3d_file.h
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
