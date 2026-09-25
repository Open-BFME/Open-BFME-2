// cl: /O1 /MD /DNDEBUG
// Rva list<Object*>-style _M_create_node (retail 0x001EB9AC, 26B).
// Freelist pop via pinned 0x002393E2 with pool at 0x00DB8FEC, null-preserving
// value pointer at +8, single Object* copy.

class Object;

struct RvaListNode
{
	void *m_prev; // +0x00
	void *m_next; // +0x04
	const Object *m_data; // +0x08
};

class FreelistPool
{
public:
	void *pop();
};

extern "C" char Rva001EB9AC_pool;

class Rva001EB9ACList
{
public:
	RvaListNode *_M_create_node(const Object *& __x);
};

RvaListNode *Rva001EB9ACList::_M_create_node(const Object *& __x)
{
	FreelistPool *pool = (FreelistPool *)&Rva001EB9AC_pool;
	RvaListNode *node = (RvaListNode *)pool->pop();
	const Object **valuePtr = (const Object **)((char *)node + 8);
	if (valuePtr == 0)
		return node;
	valuePtr[0] = __x;
	return node;
}
