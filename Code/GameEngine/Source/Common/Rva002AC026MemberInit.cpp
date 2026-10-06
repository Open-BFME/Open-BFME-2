// cl: /DNDEBUG /MD
// ?init@Rva002AC026Member@@QAEPAXPAX@Z @0x002AC026 (40B): freelist list-base init.
// Constructs the allocator proxy at this via rowed 0x0014F3C4, pops a sentinel
// node from the pool object at 0x009BBD2C via rowed FreelistPool::pop
// 0x002393E2, links it circular (next=prev=self) and returns this. Same 40B
// shape as ?init@Rva001EB984Member@@QAEPAXPAX@Z at 0x001EB984 (pool
// 0x00DB8FEC) and ?init@Rva0029FB3BMember@@QAEPAXPAX@Z at 0x0029FB3B (pool
// 0x00DA60E8). Callers at 0x002ACF91 0x002AE59B 0x002B10A6 0x004F35C5
// 0x004F3676. Pool shared with rowed Rva002AC04EAlloc 0x002AC04E.

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

class Rva002AC026Member
{
public:
	void *m_head;
	void *init(void *context);
};

extern FreelistPool g_freelistPool009BBD2C;

void *Rva002AC026Member::init(void *context)
{
	(void)context;
	char dummyAlloc;
	((FreelistProxyHead *)this)->setup(&dummyAlloc, 0);
	void *node = g_freelistPool009BBD2C.pop();
	((void **)node)[0] = node;
	((void **)node)[1] = node;
	m_head = node;
	return this;
}
