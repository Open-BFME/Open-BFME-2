// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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
// Donor: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/dx8renderer.h,
// DX8RigidFVFCategoryContainer::Add_Delayed_Visible_Material_Pass.
// Target evidence: the matched DX8RigidFVFCategoryContainer ctor at 0x145420
// installs table 0xBD3528, whose slot 5 (0xBD353C) points here, and clears
// the delayed list at +0xF0/+0xF4; base ctor 0x144E90 clears
// AnyDelayedPassesToRender at +0xE6. Retail MeshClass::Render (0x14BB90)
// calls slot +0x14 when the additional-passes-only override is set and the
// base's non-virtual Add_Visible_Material_Pass (0x144CB0) otherwise.
// Neighbouring slots 1 and 6 are matched Render at 0x148100 and
// Render_Delayed_Procedural_Material_Passes at 0x144DF0.
#include <stddef.h>

class MaterialPassClass { public: int vptr; int references; void Add_Ref() { ++references; } };
class MeshClass { public: int vptr; int references; void Add_Ref() { ++references; } };
struct MatPassTaskClass;
class MatPassTaskPoolClass { public: MatPassTaskClass *Allocate_Object_Memory(); };
extern MatPassTaskPoolClass MatPassTaskPool;

struct MatPassTaskClass
{
public:
    MatPassTaskClass(MaterialPassClass *pass, MeshClass *mesh)
        : MaterialPass(pass), Mesh(mesh), NextVisible(0)
    {
        MaterialPass->Add_Ref();
        Mesh->Add_Ref();
    }
    void Set_Next_Visible(MatPassTaskClass *task) { NextVisible = task; }
    static void *operator new(size_t) { return MatPassTaskPool.Allocate_Object_Memory(); }
private:
    MaterialPassClass *MaterialPass;
    MeshClass *Mesh;
    MatPassTaskClass *NextVisible;
};

class __declspec(novtable) DX8RigidFVFCategoryContainer
{
public:
    virtual ~DX8RigidFVFCategoryContainer(); // target vtable slot 0
    virtual void slot01()=0; virtual void slot02()=0; virtual void slot03()=0;
    virtual void slot04()=0;
    virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh);
    virtual void slot06()=0;
private:
    unsigned char prefix[0xE2];    // target this+4 through this+0xE5
    bool AnyDelayedPassesToRender; // target this+0xE6
    unsigned char gap[9];          // target list starts at this+0xF0
    MatPassTaskClass *delayed_matpass_head;
    MatPassTaskClass *delayed_matpass_tail;
};

void DX8RigidFVFCategoryContainer::Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh)
{
    MatPassTaskClass *new_mpr = new MatPassTaskClass(pass,mesh);
    if (delayed_matpass_head == 0) {
        delayed_matpass_head = new_mpr;
    } else {
        delayed_matpass_tail->Set_Next_Visible(new_mpr);
    }
    delayed_matpass_tail = new_mpr;
    AnyDelayedPassesToRender = true;
}
