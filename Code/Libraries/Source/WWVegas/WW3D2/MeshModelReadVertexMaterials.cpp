// cl: /Ireference/shims/bfme2_meshmdlio /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeshader /Ireference/shims/meshmatdesclayout /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/meshgeom /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/shims/bfmecamera
//
// ?read_vertex_materials@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018AD40 (237 bytes).
// BFME1 meshmdlio.cpp read_vertex_materials port with BFME2 rewrites (all
// retail-measured from the 0x0018AD40 body):
// - bool (AL) returns with a `bool ok` local and `!= true` checks.
// - EH frame (/EHsc): operator new at 0x2FDA0 may fail, so the body has an
//   fs prologue with scope table plus a state slot.
// - VertexMaterialClass is 0x6C bytes (vptr + RefCount at +0x4).
// - Add_Ref/Release_Ref are inlines around the refcount; the
//   disposal is a virtual slot-0 call taken only when the count reaches
//   zero (both the Load-fail and the success paths release inline, and
//   the fail path returns ok).
// - Add_Vertex_Material is an inline (Add_Ref plus indexed vector
//   Add, result ignored) over the DynamicVectorClass at context+0xC4 with
//   the same vptr-led layout as the landed MeshModelReadShaders.cpp unit
//   (VectorMax at +0x8, IsAllocated at +0xD, ActiveCount at +0x10,
//   GrowthStep at +0x14, virtual Resize at slot 2).
// New resolves via its matched row, the ctor via its matched
// row, Load_W3D via the harvested pin.

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

	int Add_Vertex_Material(VertexMaterialClass *vmat)
	{
		vmat->Add_Ref();
		int index = VertexMaterials.Count();
		VertexMaterials.Add(vmat);
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
	DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
};

// ?read_vertex_materials@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_vertex_materials(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	while (cload.Open_Chunk()) {
		VertexMaterialClass *vmat = ::new VertexMaterialClass();
		bool ok = vmat->Load_W3D(cload);
		if (ok != true) {
			vmat->Release_Ref();
			return ok;
		}
		context->Add_Vertex_Material(vmat);
		vmat->Release_Ref();
		cload.Close_Chunk();
	}
	return true;
}
