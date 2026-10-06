// cl: /DNDEBUG /MD
//
// The pooled circular list behind Player's team-prototype list (+0x32C):
// its nodes come from the pool object at 0x009BBD2C (rowed node alloc
// 0x002AC04E and sentinel init 0x002AC026) and go back onto that pool's
// free list, VA 0x00DBBD34 (the global rowed Rva002ABAC0Free pushes the
// erased node of Player::removeTeamFromList 0x002ABD48 onto).
//
// ?clear@Rva002AAC74PoolList@@QAEXXZ @0x002AAC74 (42B): drains every node
// after the sentinel at this+0 onto that free list, then points the
// sentinel's next and prev back at itself. Same shape as rowed
// Rva001EB130Holder::rva001EB130 (free list 0x00DB8FF4).
//
// ?destroy@Rva002AAC74PoolList@@QAEXXZ @0x002ABB44 (29B): clear(), then the
// sentinel itself goes onto the free list when non-null -- the list-base
// destructor; called on a local list at 0x002AE8BC and from 0x002B1314,
// 0x004F36D9, 0x004F36E1 and unwind funclets (0x00775AD4).
//
// ?dtor@Rva002AC007PoolListOwner@@QAEXXZ @0x002AC007 (5B): a jmp to
// destroy(), the outer list destructor that only runs the base one; reached
// from unwind funclets 0x00775AFB, 0x00775DEE, 0x00775F7A, 0x00792DF5 and
// 0x00792E05.
//
// The element type and the allocator's real names are unproven, so the
// bodies keep address names.
struct PoolNode002ABAC0;

// Rva002ABAC0Free.cpp defines this free list, VA 0x00DBBD34.
extern PoolNode002ABAC0 *g_00DBBD34;

class Rva002AAC74PoolList
{
public:
	void *m_head;
	void clear();
	void destroy();
};

class Rva002AC007PoolListOwner
{
public:
	Rva002AAC74PoolList m_list;
	void dtor();
};

void Rva002AAC74PoolList::clear()
{
	void *node = ((void **)m_head)[0];
	if (node != m_head) {
		do {
			void *freeHead = g_00DBBD34;
			void *current = node;
			node = ((void **)current)[0];
			((void **)current)[0] = freeHead;
			g_00DBBD34 = (PoolNode002ABAC0 *)current;
		} while (node != m_head);
	}
	((void **)m_head)[0] = m_head;
	((void **)m_head)[1] = m_head;
}

void Rva002AAC74PoolList::destroy()
{
	clear();
	void *head = m_head;
	if (head != 0) {
		void *freeHead = g_00DBBD34;
		((void **)head)[0] = freeHead;
		g_00DBBD34 = (PoolNode002ABAC0 *)head;
	}
}

void Rva002AC007PoolListOwner::dtor()
{
	m_list.destroy();
}
