// cl: /Ireference/shims/bfme2_meshmdlio /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeshader /Ireference/shims/meshmatdesclayout /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/meshgeom /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/shims/bfmecamera
// platformsdk
// dxsdk
//
// ?read_vertex_colors@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x00188760 (392 bytes, Ghidra FUN_00588760 389B truncated omits final ret8; retail full 392 incl ret8; next body 0x001888F0).
// BFME1 MeshModelVertexColors.cpp read_vertex_colors (their 373B at
// 0x0096D140) port with BFME2 rewrites (all retail-measured from the
// 0x00188760 body):
// - bool (AL) returns, not WW3DErrorType; ret8 ABI; false arm returns 0.
// - Guard on CurMatDesc (+0x94) ColorArray[0] at matdesc+0x50 (the +0x50
//   anchor is retail-proven by matched Get_Color_Array 0xD1FBD's TU view;
//   donor checks Has_Color_Array(0), same cmp shape as ReadDcg/ReadDig).
// - Per-vertex 4-byte Read via matched ChunkLoadClass::Read 0x6151A0 with the
//   donor's checked-size early-false return (ReadDig arm1 ignores the
//   return; the check here follows the donor and the retail jne fail arm).
// - R/G/B unpack through call-free SSE (cvtsi2ss times the shared 1/255
//   constant, W = 1.0f) exactly like landed ReadDig arm1; the donor's
//   `/ 255.0f` spelling would emit divss, so the ReadDig `* (1/255)`
//   product form is used (retail mulss).
// - The pack is the ZH (Vector3, float) Convert_Color with its hand-written
//   fstcw/chop/fistp asm spliced inline, shared verbatim with the landed
//   ReadDcg/ReadDig TUs (sub esp,20 frame, 255.0f scale, 1.0f alpha).
// - DCGSource lives at matdesc+0x58; COLOR1 == 1 stored by direct member
//   write (same tail as read_dcg/read_dig).
// - W3dRGBStruct is 4 bytes (R,G,B,pad) per the genuine w3d_file.h shape
//   ("padded to an even 4 bytes"), so sizeof(color) == 4 matches the retail
//   push 4; the pad byte is unread, as retail only samples AL/AH/[ebp-2].
// Get_Color_Array resolves via matched row 0xD1FBD; Read via matched row 0x6151A0.

#define BFME_MESHMATDESC_COLOR_ARRAY_EXTERNAL
#include "always.h"
#include <meshmatdesc.h>
#include "meshmdl.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "dx8wrapper.h"

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

// ?read_vertex_colors@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_vertex_colors(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	if (CurMatDesc->Has_Color_Array(0) == false) {
		W3dRGBStruct color;
		unsigned *dcg = CurMatDesc->Get_Color_Array(0);
		for (int i = 0; i < VertexCount; i++) {
			if (cload.Read(&color, sizeof(color)) != sizeof(color)) {
				return false;
			}
			Vector4 col;
			col.X = (float)color.R * (1.0f / 255.0f);
			col.Y = (float)color.G * (1.0f / 255.0f);
			col.Z = (float)color.B * (1.0f / 255.0f);
			col.W = 1.0f;
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	}
	CurMatDesc->Set_DCG_Source(context->CurPass,VertexMaterialClass::COLOR1);
	return true;
}
