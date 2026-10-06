// cl: /DNDEBUG /MD
//
// ?Rva00268902@PoolMember@@QAEXXZ, retail 0x00268902, 29 bytes.
// Teardown of the free-list member that Rva0029FB3BMember::init (0x0029FB3B)
// builds: return every node through the rowed reset (0x0026549E), then push
// the sentinel head itself back onto the pool's free list (the global at
// 0xDA60F0 that reset also uses). Eight module units call it by this pinned
// name (module dtors on their +0x88 member); the owning container type is
// unidentified, so the address-derived name is kept.

class Rva0029FB3BMember
{
public:
	void reset();
};

extern void *g_freeList;

class PoolMember
{
public:
	void Rva00268902();

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
