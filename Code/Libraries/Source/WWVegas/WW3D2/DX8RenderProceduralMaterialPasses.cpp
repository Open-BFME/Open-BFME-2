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
// Retail returns the task-deletion flag in AL. The donor's void signature
// and volatile flag are replaced by a normal Boolean result.
// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp.
// Target 0x00146130 /165 is directly tail-called by matched rigid Render at
// 0x00148100; target head/tail/index-buffer accesses are +0xC8/+0xCC/+0xD0.
// Those target offsets are independently initialized by the matched base
// constructor at 0x00144E90 and the matched Add_Delayed body at 0x00144CB0.
#include <stddef.h>

class IndexBufferClass;
class RefCountClass
{
public:
    void Add_Ref() { ++references; }
    void Release_Ref() { if (--references == 0) Delete_This(); }
    virtual void Delete_This();
protected:
    virtual ~RefCountClass();
public:
    int references;
};

class MaterialPassClass : public RefCountClass
{
};

class MeshClass : public RefCountClass
{
public:
    unsigned char opaque[0x2F8];
    unsigned BaseVertexOffset;
    int Get_Base_Vertex_Offset() { return (int)BaseVertexOffset; }
    void Render_Material_Pass(MaterialPassClass *, IndexBufferClass *);
};

template<class T, int N> class ObjectPoolClass
{
public:
    void Free_Object_Memory(T *);
};

template<class T, int N> class AutoPoolClass
{
public:
    static ObjectPoolClass<T, N> Allocator;
    static void operator delete(void *);
};

template<class T, int N>
void AutoPoolClass<T, N>::operator delete(void *object)
{
    Allocator.Free_Object_Memory((T *)object);
}

class MatPassTaskClass : public AutoPoolClass<MatPassTaskClass, 256>
{
public:
    MaterialPassClass *MaterialPass;
    MeshClass *Mesh;
    MatPassTaskClass *NextVisible;

    MaterialPassClass *Peek_Material_Pass() { return MaterialPass; }
    MeshClass *Peek_Mesh() { return Mesh; }
    MatPassTaskClass *Get_Next_Visible() { return NextVisible; }
    void Set_Next_Visible(MatPassTaskClass *next) { NextVisible = next; }
    ~MatPassTaskClass()
    {
        MaterialPass->Release_Ref();
        Mesh->Release_Ref();
    }
};

template<> ObjectPoolClass<MatPassTaskClass, 256>
    AutoPoolClass<MatPassTaskClass, 256>::Allocator;

class __declspec(novtable) DX8FVFCategoryContainer
{
public:
    virtual ~DX8FVFCategoryContainer();
protected:
    bool Render_Procedural_Material_Passes();

private:
    unsigned char prefix[0xC4]; // target this+4 through this+0xC7
    MatPassTaskClass *visible_matpass_head;
    MatPassTaskClass *visible_matpass_tail;
    IndexBufferClass *index_buffer;
};

bool DX8FVFCategoryContainer::Render_Procedural_Material_Passes()
{
    MatPassTaskClass *mpr = visible_matpass_head;
    MatPassTaskClass *last_mpr = NULL;
    bool renderTasksRemaining = false;
    bool taskWasDeleted = false;

    while (mpr != NULL) {
        MeshClass *mesh = mpr->Peek_Mesh();
        if (mesh->Get_Base_Vertex_Offset() == 0xFFFF) {
            last_mpr = mpr;
            mpr = mpr->Get_Next_Visible();
            renderTasksRemaining = true;
            continue;
        }

        IndexBufferClass *pass_index_buffer = index_buffer;
        MaterialPassClass *material_pass = mpr->Peek_Material_Pass();
        mpr->Peek_Mesh()->Render_Material_Pass(material_pass, pass_index_buffer);
        MatPassTaskClass *next_mpr = mpr->Get_Next_Visible();
        taskWasDeleted = true;
        if (last_mpr == NULL)
            visible_matpass_head = next_mpr;
        else
            last_mpr->Set_Next_Visible(next_mpr);
        delete mpr;
        mpr = next_mpr;
    }

    visible_matpass_tail = renderTasksRemaining ? last_mpr : NULL;
    return taskWasDeleted;
}
