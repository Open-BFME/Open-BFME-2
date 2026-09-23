// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
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

class MeshClass
{
public:
    unsigned char opaque[0x304];
    MeshClass *NextVisibleSkin;
    MeshClass *Peek_Next_Visible_Skin()
    { return NextVisibleSkin; }
    void Set_Next_Visible_Skin(MeshClass *next)
    { NextVisibleSkin = next; }
};

class __declspec(novtable) DX8SkinFVFCategoryContainer
{
public:
    virtual ~DX8SkinFVFCategoryContainer();
private:
    void clearVisibleSkinList();
    unsigned char prefix[0xE4];
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
