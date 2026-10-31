// cl: /Ireference/shims/bfme2_meshmdlio /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeshader /Ireference/shims/meshmatdesclayout /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/meshgeom /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/shims/bfmecamera
//
// ?read_shaders@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018AC90 (160 bytes).
// BFME1 meshmdlio.cpp read_shaders port (W3dShaderStruct loop over
// MatInfo.ShaderCount with bulk Read, Convert_Shader, Add_Shader). BFME2
// adaptations (all retail-measured from the 0x18AC90 body):
// - bool (AL) returns, not WW3DErrorType.
// - ShaderCount at context+0x80; Shaders DynamicVectorClass<ShaderClass> at
//   context+0xAC (Vector+4/VectorMax+8/IsValid+0xC/IsAllocated+0xD/
//   ActiveCount+0x10/GrowthStep+0x14, matching vector.h ordering).
// - ShaderClass DWORD defaulting to 0x10441B (retail stashes the default to
//   the Convert dst slot).
// - Add_Shader inlines as DynamicVectorClass::Add (ActiveCount-vs-Length
//   guard, IsAllocated/!VectorMax/GrowthStep grow checks, virtual Resize at
//   slot 2 with (total, NULL), then ActiveCount++ store); no out-of-line call.
// - Callee-clean thiscalls (Read, Resize) emit no caller cleanup; the static
//   Convert_Shader is cdecl (caller add-esp-8). The Convert dst reuses the
//   dead context-arg slot.
// No new pins (Read + Convert_Shader resolve via matched rows).

#include "always.h"
#include <meshmatdesc.h>
#include "meshmdl.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "shader.h"
#include "vertmaterial.h"
#include "w3d_util.h"

class MeshLoadContextClass
{
	friend class MeshModelClass;

	int Add_Shader(ShaderClass shader)
	{
		int index = Shaders.Count();
		Shaders.Add(shader);
		return index;
	}

	struct LegacyMaterialClass;

	W3dMeshHeader3Struct Header;
	W3dTexCoordStruct *TexCoords;
	W3dMaterialInfoStruct MatInfo;
	uint32 PrelitChunkID;
	int CurPass;
	int CurTexStage;
	DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
	DynamicVectorClass<ShaderClass> Shaders;
};

// ?read_shaders@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_shaders(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	W3dShaderStruct shader;
	for (unsigned int i = 0; i < context->MatInfo.ShaderCount; i++) {
		if (cload.Read(&shader, sizeof(shader)) != sizeof(shader)) {
			return false;
		}
		ShaderClass newshader;
		W3dUtilityClass::Convert_Shader(shader, &newshader);

		int index = context->Add_Shader(newshader);
		(void)index;
	}
	return true;
}
