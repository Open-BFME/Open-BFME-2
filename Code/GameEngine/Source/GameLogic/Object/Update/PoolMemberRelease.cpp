// cl: /DNDEBUG /MD
//
// ?Rva00268902@PoolMember@@QAEXXZ, retail 0x00268902, 29 bytes.
// Teardown of the free-list member that Rva0029FB3BMember::init (0x0029FB3B)
// builds: return every node through the rowed reset (0x0026549E), then push
// the sentinel head itself back onto the pool's free list (the global at
// 0xDA60F0 that reset also uses). Eight module units call it by this pinned
// name (module dtors on their +0x88 member); the owning container type is
// unidentified, so the address-derived name is kept.

#include "../../../../Include/GameLogic/Module/Rva0029FB3BMember.h"

// The free-list head is the +8 member of the complete pool at VA 0xDA60E8.
class FreelistPool;
extern FreelistPool g_freelistPool;
#define g_freeList (*(void **)((char *)&g_freelistPool + 8))

class PoolMember
{
public:
	__declspec(noinline) void Rva00268902();

private:
	void *m_head;
};

void PoolMember::Rva00268902()
{
	((Rva0029FB3BMember *)this)->reset();
	void *head = m_head;
	if (head) {
		*(void **)head = g_freeList;
		g_freeList = head;
	}
}

// Native0x00268AFF..0x00268B04: tail JMP to sole owned cleanup0x00268902.
// ECX/stack unchanged no stack args RET0. Original wrapper name enclosing
// type and lifetime role unknown; reuse only the existing receiver view.
struct Rva00268AFFCleanupForward { void cleanup(); };
void Rva00268AFFCleanupForward::cleanup()
{
    reinterpret_cast<PoolMember*>(this)->Rva00268902();
}

// Native0x00265466..0x0026547D (24B): stdcall (node, size) deallocator for the
// same 0xDA60F0 free list: a non-null node is pushed back as the new head and
// the size is ignored (ret 8). Skeleton twin of the 0x00DBD4B8 pool's
// Rva002EAD84 (GapBodiesGE04.cpp); allocator type unidentified.
void __stdcall Rva00265466(void *node, unsigned int)
{
	if (node) {
		*(void **)node = g_freeList;
		g_freeList = node;
	}
}
