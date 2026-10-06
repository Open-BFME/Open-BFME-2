// cl: /MD /DNDEBUG
//
// ?init@Rva001EB984Member@@QAEPAXPAX@Z, retail 0x001EB984, 40 bytes.
// Freelist-node list-base init for list<Object*> (pool at 0x00DB8FEC):
// constructs the allocator proxy at this via rowed 0x0014F3C4, pops a
// sentinel node via rowed FreelistPool::pop 0x002393E2, links it circular
// and returns this. Byte-identical shape to ?init@Rva0029FB3BMember at
// 0x0029FB3B (same 40B sequence, pool differs 0xDA60E8 vs 0xDB8FEC).
// Evidence: pinned STL spelling ??0?$_List_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@ABV?$allocator@PAVObject@@@1@@Z
// harvested from list<Object*> ctor 0x004702FB REL32; callers at 0x001EBCCD
// 0x001EC779 0x0024723F plus list<Object*> copy ctor; pool shared with
// rowed create_node 0x001EB9AC.

class FreelistProxyHead
{
public:
	void setup(const void *alloc, void *head);
};

class FreelistPool
{
public:
	void *pop();
};

class Rva001EB984Member
{
public:
	void *m_head;
	void *init(void *context);
};

// Distinct from the behavior pool at VA 0x00DA60E8.
extern FreelistPool g_freelistPool00DB8FEC;

// ?init@Rva001EB984Member@@QAEPAXPAX@Z @0x001EB984
void *Rva001EB984Member::init(void *context)
{
	(void)context;
	char dummyAlloc;
	((FreelistProxyHead *)this)->setup(&dummyAlloc, 0);
	void *node = g_freelistPool00DB8FEC.pop();
	((void **)node)[0] = node;
	((void **)node)[1] = node;
	m_head = node;
	return this;
}
