// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?Check_If_Mesh_Fits@DX8RigidFVFCategoryContainer@@UAE_NPAVMeshModelClass@@@Z,
// retail 0x00143A20 (75 bytes, RET 4). Donor: Zero Hour dx8renderer.cpp.
// BFME 2 has no gap filler; the vertex buffer's count is the
// unsigned short at +0x0C, the index buffer's the full unsigned at +0x0C (as
// in DX8SkinClearVisibleList.cpp). Fields: vertex buffer +0xE8 with used
// vertices +0xEC, index buffer +0xD0 with used indices +0xD4; the mesh model
// keeps its polygon count at +0x24, its vertex count at +0x28 and its pass
// count in CurMatDesc (+0x94).
#include "MeshMatDescClass.h"
#include "MeshModelClass.h"
inline int MeshModelClass::Get_Pass_Count() const { return CurMatDesc->PassCount; }

#include "VertexBufferClass.h"

#include "IndexBufferClass.h"

class __declspec(novtable) DX8FVFCategoryContainer
{
public:
	virtual ~DX8FVFCategoryContainer();
	virtual bool Check_If_Mesh_Fits(MeshModelClass *mmc) = 0;
};

class __declspec(novtable) DX8RigidFVFCategoryContainer : public DX8FVFCategoryContainer
{
public:
	virtual bool Check_If_Mesh_Fits(MeshModelClass *mmc);
private:
	unsigned char prefix[0xCC];
	IndexBufferClass *index_buffer;		// +0xD0
	unsigned used_indices;			// +0xD4
	unsigned char middle[0x10];
	VertexBufferClass *vertex_buffer;	// +0xE8
	unsigned used_vertices;			// +0xEC
};

bool DX8RigidFVFCategoryContainer::Check_If_Mesh_Fits(MeshModelClass *mmc)
{
	if (!vertex_buffer) return true;	// No VB created - mesh will fit as a new vb will be created when inserting
	unsigned required_vertices=mmc->Get_Vertex_Count();
	unsigned available_vertices=vertex_buffer->Get_Vertex_Count()-used_vertices;
	unsigned required_polygons=mmc->Get_Polygon_Count();
	unsigned required_indices=required_polygons*3*mmc->Get_Pass_Count();
	unsigned available_indices=index_buffer->Get_Index_Count()-used_indices;
	if (
		required_vertices<=available_vertices &&
		(required_indices)<=available_indices) {
		return true;
	}
	return false;
}
