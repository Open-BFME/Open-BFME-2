// cl: /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

#include <stddef.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matpass.h
class MaterialPassClass
{
public:
    int vtable;
    int references;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass
{
public:
    int vtable;
    int references;
};

struct MatPassTaskClass;

class MatPassTaskPoolClass
{
public:
    MatPassTaskClass *Allocate_Object_Memory();
};

extern MatPassTaskPoolClass MatPassTaskPool;

struct MatPassTaskClass
{
    MaterialPassClass *pass;
    MeshClass *mesh;
    MatPassTaskClass *next;

    MatPassTaskClass(MaterialPassClass *new_pass, MeshClass *new_mesh) :
        pass(new_pass), mesh(new_mesh), next(0)
    {
        ++pass->references;
        ++mesh->references;
    }

    static void *operator new(size_t)
    {
        return MatPassTaskPool.Allocate_Object_Memory();
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8RigidFVFCategoryContainer
{
    // Eight bytes shorter than the Zero Hour layout puts it.  Retail stores
    // the list head and tail at [esi+0xC8] and [esi+0xCC] and sets the flag
    // byte at [esi+0xE5], where this overlay had them at 0xD0, 0xD4 and 0xED
    // -- three members, two dwords and a byte fifteen bytes further on, all
    // eight low, so it is the prefix that is wrong and not the spacing after
    // it.
    unsigned char prefix[0xc4];
    MatPassTaskClass *delayed_matpass_head;
    MatPassTaskClass *delayed_matpass_tail;
    unsigned char middle[0x15];
    bool AnyDelayedPassesToRender;

public:
    virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh);
};

void DX8RigidFVFCategoryContainer::Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh)
{
    MatPassTaskClass *task = new MatPassTaskClass(pass, mesh);

    if (delayed_matpass_head == 0) {
        delayed_matpass_head = task;
        delayed_matpass_tail = task;
    } else {
        delayed_matpass_tail->next = task;
        delayed_matpass_tail = task;
    }
    AnyDelayedPassesToRender = true;
}
