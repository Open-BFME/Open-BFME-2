// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

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

// upstream layout: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
// This is the base class's non-virtual Add_Visible_Material_Pass, not the
// rigid container's delayed override: the base ctor 0x00144E90 clears the
// list head and tail at +0xC8 and +0xCC and the flag bytes +0xE4..+0xE6, the
// rigid ctor 0x00145420 clears its own delayed list at +0xF0 and +0xF4, and
// retail MeshClass::Render calls this body directly while it reaches the
// delayed append through vtable slot +0x14 (0x00144D70).
class DX8FVFCategoryContainer
{
    // vptr, MultiListObjectClass base and the texture category lists
    unsigned char prefix[0xc8];
    MatPassTaskClass *visible_matpass_head;
    MatPassTaskClass *visible_matpass_tail;
    unsigned char middle[0x15];
    bool AnythingToRender;

public:
    void Add_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh);
};

void DX8FVFCategoryContainer::Add_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh)
{
    MatPassTaskClass *new_mpr = new MatPassTaskClass(pass, mesh);

    if (visible_matpass_head == 0) {
        visible_matpass_head = new_mpr;
    } else {
        visible_matpass_tail->next = new_mpr;
    }

    visible_matpass_tail = new_mpr;
    AnythingToRender = true;
}
// ?MatPassTaskPool@@3VMatPassTaskPoolClass@@A: the global at VA 0xdf3690 is ?Allocator@?$AutoPoolClass@VMatPassTaskClass@@$0BAA@@@0V?$ObjectPoolClass@VMatPassTaskClass@@$0BAA@@@A.
#pragma comment(linker, "/alternatename:?MatPassTaskPool@@3VMatPassTaskPoolClass@@A=?Allocator@?$AutoPoolClass@VMatPassTaskClass@@$0BAA@@@0V?$ObjectPoolClass@VMatPassTaskClass@@$0BAA@@@A")
