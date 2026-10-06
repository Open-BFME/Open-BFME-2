// cl: /DNDEBUG /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp,
// DX8SkinFVFCategoryContainer::clearVisibleSkinList. Target evidence: matched
// Reset at 0x1444B0 calls this helper; retail fields are head+F0, tail+F4,
// vertex count+E8 and mesh next-visible+304. Ghidra's 67-byte extent is three
// bytes short of the full ret-terminated body; retail returns at 0x143CA5 and
// the following CC starts at 0x143CA6.
#include <stddef.h>

// Check_If_Mesh_Fits reads the polygon count through the pointer at +0x94
// and the pass count at +0x24 (the BFME1 donor reads the same pair at
// +0x9C/+0x24 in its image).
struct MeshPolygonCount
{
    int Count;
};

class MeshModelClass
{
public:
    unsigned char pad[0x24];
    int PassCount;
    int VertexCount;
    unsigned char pad1[0x94 - 0x2C];
    MeshPolygonCount *PolygonCount;
    int Get_Vertex_Count() const
    { return VertexCount; }
    int Get_Pass_Count() const
    { return PassCount; }
    int Get_Polygon_Count() const
    { return PolygonCount->Count; }
};

// Only the index count matters here: BFME's is a full unsigned at +0x0C (the
// retail compare is unsigned), where Zero Hour's header has an unsigned short.
class IndexBufferClass
{
public:
    unsigned char pad[0x0C];
    unsigned index_count;
    unsigned Get_Index_Count() const
    { return index_count; }
};

class MeshClass
{
public:
    unsigned char pad0[0xC4];
    MeshModelClass *Model;
    unsigned char pad1[0x23C];
    MeshClass *NextVisibleSkin;
    MeshClass *Peek_Next_Visible_Skin()
    { return NextVisibleSkin; }
    void Set_Next_Visible_Skin(MeshClass *next)
    { NextVisibleSkin = next; }
    MeshModelClass *Peek_Model()
    { return Model; }
};

class __declspec(novtable) DX8SkinFVFCategoryContainer
{
public:
    virtual ~DX8SkinFVFCategoryContainer();
    virtual bool Check_If_Mesh_Fits(MeshModelClass *mmc);
    void Add_Visible_Skin(MeshClass *mesh);
private:
    void clearVisibleSkinList();
    unsigned char prefix[0xCC];
    IndexBufferClass *index_buffer;	// +0xD0
    unsigned used_indices;			// +0xD4
    unsigned char prefix1[0x10];
    unsigned VisibleVertexCount;
    unsigned VisibleSkinCount;
    MeshClass *VisibleSkinHead;
    MeshClass *VisibleSkinTail;
};

void DX8SkinFVFCategoryContainer::clearVisibleSkinList()
{
    while (VisibleSkinHead != NULL) {
        MeshClass *next = VisibleSkinHead->Peek_Next_Visible_Skin();
        VisibleSkinHead->Set_Next_Visible_Skin(NULL);
        VisibleSkinHead = next;
    }
    VisibleSkinHead = NULL;
    VisibleSkinTail = NULL;
    VisibleVertexCount = 0;
    VisibleSkinCount = 0;
}

void DX8SkinFVFCategoryContainer::Add_Visible_Skin(MeshClass *mesh)
{
    if (mesh->Peek_Next_Visible_Skin() != NULL || mesh == VisibleSkinTail)
        return;
    if (VisibleSkinHead == NULL)
        VisibleSkinTail = mesh;
    mesh->Set_Next_Visible_Skin(VisibleSkinHead);
    VisibleSkinHead = mesh;
    VisibleVertexCount += mesh->Peek_Model()->Get_Vertex_Count();
}

// ?Check_If_Mesh_Fits@DX8SkinFVFCategoryContainer@@UAE_NPAVMeshModelClass@@@Z
// Retail 0x00143C20, 54 bytes: slot 4 of the container vtable 0x007D3544, in
// Zero Hour's DX8FVFCategoryContainer order (~, Render, Add_Mesh, Log,
// Check_If_Mesh_Fits, then the two Delayed passes; the rigid container's table
// just before it has the same shape). Aligning that table against lotrbfme.exe
// names this slot DX8SkinFVFCategoryContainer::Check_If_Mesh_Fits, and the body
// sits right before the rowed clearVisibleSkinList. It is Zero Hour's body
// minus the gap-filler branch, which BFME's skin container does not have
// (BFME1 matched the same shape at 55 bytes).
bool DX8SkinFVFCategoryContainer::Check_If_Mesh_Fits(MeshModelClass* mmc)
{
    if (!index_buffer) return true;	// No IB created - mesh will fit as a new ib will be created when inserting
    int required_polygons=mmc->Get_Polygon_Count();

    if ((required_polygons*3*mmc->Get_Pass_Count())<=index_buffer->Get_Index_Count()-used_indices) {
        return true;
    }
    return false;
}
