// cl: /Ireference/shims/bfme2_meshmdlio /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeshader /Ireference/shims/meshmatdesclayout /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/meshgeom /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/shims/bfmecamera
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
// Pins for the three unlanded bool callees are harvested from
// the retail REL32 displacements at the switch cases (jump-table indices
// 2/3/4); read_shaders resolves via its matched row.

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
