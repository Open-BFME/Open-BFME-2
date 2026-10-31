// cl: /Ireference/shims/bfme2_meshmdlio /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeshader /Ireference/shims/meshmatdesclayout /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/meshgeom /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/shims/bfmecamera
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
// Frameless, no EH temps.

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
