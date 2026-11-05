// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

#include <stddef.h>

#include "MaterialPassClass.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass
{
public:
    int vtable;
    int references;
};

// BFME2 pool view: MatPassTaskClass derives AutoPoolClass<...,256> and uses
// the Allocator instance at VA 0x00DF3690 (the 0x00144CB0 body loads it for its
// `new`), matching the reference shims/bfmepool/mempool.h layout. The pool is
// 0x14 bytes: free-list head +0, block-list head +4, free count +8, total
// count +0xC, lock word +0x10 (the rowed 0x001440C0 owner proves the layout).
template<class T, int BLOCK_SIZE = 64>
class ObjectPoolClass
{
public:
    T *Allocate_Object_Memory(void);
    void Free_Object_Memory(T *obj);

private:
    T *m_freeListHead;
    unsigned int *m_blockListHead;
    int m_freeObjectCount;
    int m_totalObjectCount;
    unsigned int m_poolLock;
};

template<class T, int BLOCK_SIZE = 64>
class AutoPoolClass
{
public:
    static void *operator new(size_t) { return Allocator.Allocate_Object_Memory(); }
    static void operator delete(void *memory) { Allocator.Free_Object_Memory((T *)memory); }

private:
    static ObjectPoolClass<T, BLOCK_SIZE> Allocator;
};

class MatPassTaskClass : public AutoPoolClass<MatPassTaskClass, 256>
{
public:
    MaterialPassClass *pass;
    MeshClass *mesh;
    MatPassTaskClass *next;

    MatPassTaskClass(MaterialPassClass *new_pass, MeshClass *new_mesh) :
        pass(new_pass), mesh(new_mesh), next(0)
    {
        ++pass->NumRefs;
        ++mesh->references;
    }
};

// The new-expression's cleanup otherwise emits this unit's own copy of the pool's
// operator delete, which is not retail's body; the call links to the kept retail definition.
template <> void AutoPoolClass<MatPassTaskClass, 256>::operator delete(void *);

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
// The Allocator pool instance at VA 0x00DF3690 is defined by dx8renderer.cpp's
// DEFINE_AUTO_POOL(MatPassTaskClass, 256) and owned by the data ledger (RVA
// 0x009F3690, 0x14 bytes, zero-filled). The old /alternatename binding of the
// BFME1 MatPassTaskPool view is gone: `new MatPassTaskClass` here uses the
// Allocator, exactly as the retail 0x00144CB0 bytes show.
