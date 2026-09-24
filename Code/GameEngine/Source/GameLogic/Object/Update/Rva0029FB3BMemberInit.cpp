// cl: /O1 /DNDEBUG /MD
//
// ?init@Rva0029FB3BMember@@QAEPAXPAX@Z, retail 0x0029FB3B, 40 bytes.
// Freelist-node member init shared by 7 behavior ctors (ArrowStorm,
// DamageField, RousingSpeech, GloriousCharge and sibs): constructs the
// allocator proxy at this, pops a node from the pool object at
// 0xDA60E8, links it into a circular sentinel and returns this. The
// incoming context argument is unused (retail dead arg kept for the
// callers). The pool container itself is unidentified so the member
// keeps its honest Rva address name.

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

class Rva0029FB3BMember
{
public:
	void *m_head;
	void *init(void *context);
	void reset();
};

extern FreelistPool g_freelistPool;

// ?init@Rva0029FB3BMember@@QAEPAXPAX@Z @0x0029FB3B
void *Rva0029FB3BMember::init(void *context)
{
	(void)context;
	char dummyAlloc;
	((FreelistProxyHead *)this)->setup(&dummyAlloc, 0);
	void *node = g_freelistPool.pop();
	((void **)node)[0] = node;
	((void **)node)[1] = node;
	m_head = node;
	return this;
}
