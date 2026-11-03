// cl: /DNDEBUG /MD /GX- C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?read_vertex_material_ids@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x001888F0 (187 bytes: ret C2 08 00 at 0x1889AB).
// BFME1 Code/Libraries/Source/WWVegas/WW3D2/MeshModelMaterialIds.cpp
// read_vertex_material_ids port (their 190B Open-BFME1 clean C++ row at
// 0x0096D300, same IAE_N bool shape). BFME2 adaptations (all retail-measured
// from the 0x1888F0 body):
// - MeshModel VertexCount at this+0x28, DefMatDesc at this+0x8C (vptr-ful,
//   texcoords-TU-honest layout).
// - MeshMatDesc Material[4] at +0xA8, MaterialArray[4] at +0xE8, size 0x118.
// - Context CurPass at +0x8C, VertexMaterials pointer array at +0xC8,
//   AlternateMatDesc at +0x124. Peek_Vertex_Material inlines as the array
//   read (no out-of-line body, no pin).
// - Callees resolve via matched rows (Cur_Chunk_Length 0x615030, Read
//   0x6151A0) and new pins (Set_Single_Material 0x15A760, Set_Material
//   0x15D2A0, both BFME1-matched manglings).
// Dedicated TU: marker-less meshmdlio.cpp cannot take rows (PostProcess
// precedent). Frameless, no EH temps (no BfmeHandleCX here).

class VertexMaterialClass;

#include "../WWLib/ChunkLoadClass.h"

class MeshMatDescClass
{
public:
	bool Has_Material_Data(int pass) { return Material[pass] != 0 || MaterialArray[pass] != 0; }
	void Set_Single_Material(VertexMaterialClass *material, int pass);
	void Set_Material(int index, VertexMaterialClass *material, int pass);

private:
	char m_pad0[0xA8];
	VertexMaterialClass *Material[4];
	char m_pad1[0xE8 - 0xB8];
	void *MaterialArray[4];
	char m_pad2[0x118 - 0xF8];
};

typedef char MeshMatDescSizeCheck[sizeof(MeshMatDescClass) == 0x118 ? 1 : -1];

class MeshLoadContextClass
{
	virtual ~MeshLoadContextClass();
	char m_pad0[0x88 - 4];
public:
	unsigned long PrelitChunkID;
	int CurPass;
	int CurTexStage;
private:
	char m_pad1[0xC8 - 0x94];
public:
	VertexMaterialClass **VertexMaterials;
private:
	char m_pad2[0x124 - 0xCC];
public:
	MeshMatDescClass AlternateMatDesc;
public:
	VertexMaterialClass *Peek_Vertex_Material(unsigned long index) { return VertexMaterials[index]; }
};

#include "MeshModelClass.h"

// ?read_vertex_material_ids@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_vertex_material_ids(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	unsigned long vmat;
	MeshMatDescClass *matdesc = DefMatDesc;

	if (matdesc->Has_Material_Data(context->CurPass)) {
		matdesc = &(context->AlternateMatDesc);
	}

	if (cload.Cur_Chunk_Length() == 1 * sizeof(unsigned long)) {
		cload.Read(&vmat, sizeof(vmat));
		matdesc->Set_Single_Material(context->Peek_Vertex_Material(vmat), context->CurPass);
	} else {
		for (int i = 0; i < Get_Vertex_Count(); i++) {
			cload.Read(&vmat, sizeof(unsigned long));
			matdesc->Set_Material(i, context->Peek_Vertex_Material(vmat), context->CurPass);
		}
	}

	return true;
}
