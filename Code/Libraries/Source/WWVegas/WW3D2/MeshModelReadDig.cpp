// cl: /Ireference/shims/bfme2_meshmdlio /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeshader /Ireference/shims/meshmatdesclayout /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/meshgeom /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/shims/bfmecamera
// platformsdk
// dxsdk
//
// ?read_dig@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x00188DF0 (848 bytes).
// BFME1 MeshModelVertexColors.cpp read_dig port with BFME2 rewrites (all
// retail-measured from the 0x00188DF0 body):
// - bool (AL) returns, not WW3DErrorType.
// - LoadedDIG flag at context+0x248 selects DefMatDesc vs AlternateMatDesc
//   (set true on entry); no DCGSource check like read_dcg.
// - First arm (no color array yet): per-vertex 4-byte Read; R/G/B unpack
//   through call-free SSE (cvtsi2ss times the shared 1/255 constant, W =
//   1.0f), and the pack is the ZH (Vector3, float) Convert_Color with its
//   hand-written fstcw/chop/fistp asm spliced inline (sub esp,20 frame,
//   255.0f scale and 1.0f alpha hoisted to the loop preheader).
// - Second arm (array present): per-vertex 4-byte Read; the packed color
//   decomposes through the ZH unsigned Convert_Color inline (x87 fild
//   batch with the 2^32 fixup), each channel multiplied by the fresh byte
//   over 255, then the same asm pack.
// - DCGSource lives at matdesc+0x58; COLOR1 == 1 is stored back by an
//   inlined Set (same tail as read_dcg).
// Get_Color_Array and Read resolve via matched rows.

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

	void Notify_Loaded_DIG_Chunk(bool onoff = true) { LoadedDIG = onoff; }
	bool Already_Loaded_DIG(void) { return LoadedDIG; }

	W3dMeshHeader3Struct Header;
	W3dTexCoordStruct *TexCoords;
	W3dMaterialInfoStruct MatInfo;
	uint32 PrelitChunkID;
	int CurPass;
	int CurTexStage;
	char m_pad94[0x124 - 0x94];
	MeshMatDescClass AlternateMatDesc;
	char m_pad23C[0x248 - 0x23C];
	bool LoadedDIG;
};

// ?read_dig@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_dig(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	MeshMatDescClass *matdesc = DefMatDesc;
	if (context->Already_Loaded_DIG()) {
		matdesc = &context->AlternateMatDesc;
	}
	context->Notify_Loaded_DIG_Chunk(true);

	if (matdesc->Has_Color_Array(0) == false) {
		W3dRGBAStruct color;
		unsigned *dcg = matdesc->Get_Color_Array(0);
		for (int i = 0; i < VertexCount; i++) {
			cload.Read(&color, sizeof(color));
			Vector4 col;
			col.X = (float)color.R * (1.0f / 255.0f);
			col.Y = (float)color.G * (1.0f / 255.0f);
			col.Z = (float)color.B * (1.0f / 255.0f);
			col.W = 1.0f;
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	} else {
		W3dRGBAStruct color;
		unsigned *dcg = matdesc->Get_Color_Array(0);
		for (int i = 0; i < VertexCount; i++) {
			cload.Read(&color, sizeof(color));
			Vector4 col = DX8Wrapper::Convert_Color(dcg[i]);
			col.X *= (float)color.R * (1.0f / 255.0f);
			col.Y *= (float)color.G * (1.0f / 255.0f);
			col.Z *= (float)color.B * (1.0f / 255.0f);
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	}

	matdesc->Set_DCG_Source(context->CurPass,VertexMaterialClass::COLOR1);
	return true;
}
