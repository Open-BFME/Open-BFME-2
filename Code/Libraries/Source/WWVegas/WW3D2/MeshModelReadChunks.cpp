// cl: /Ireference/shims/bfme2_meshmdlio /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeshader /Ireference/shims/meshmatdesclayout /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/meshgeom /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/shims/bfmecamera
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

#include "always.h"
#include <meshmatdesc.h>
#include "meshmdl.h"
#include "chunkio.h"
#include "w3d_file.h"

class MeshLoadContextClass
{
	friend class MeshModelClass;

	W3dMeshHeader3Struct Header;
	W3dTexCoordStruct *TexCoords;
	W3dMaterialInfoStruct MatInfo;
	uint32 PrelitChunkID;
	int CurPass;
	int CurTexStage;
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
			if (cload.Read(&context->MatInfo, sizeof(W3dMaterialInfoStruct)) != sizeof(W3dMaterialInfoStruct)) {
				error = false;
				break;
			}
			Set_Pass_Count(context->MatInfo.PassCount);
			error = true;
			break;
		case 0x29:
			error = read_shaders(cload, context);
			break;
		case 0x2A:
			error = read_vertex_materials(cload, context);
			break;
		case 0x50:
			error = read_fx_shaders(cload, context);
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
