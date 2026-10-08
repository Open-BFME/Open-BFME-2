// cl: /DNDEBUG /MD
// ?Rva002AC04EAlloc@@YGPAXPAPAX@Z @0x002AC04E (28B): freelist node alloc.
// Pops a 0x10 node from the pool object at 0x009BBD2C via rowed
// ?pop@FreelistPool@@QAEPAXXZ, stores the caller's pointed value into
// the node at +8, and returns the node. Caller at 0x002ACFA0. No donor;
// honest address name matching Rva00239BD8Alloc pattern.
class FreelistPool
{
public:
	void *pop();
};
extern FreelistPool g_freelistPool009BBD2C;
void *__stdcall Rva002AC04EAlloc(void **arg)
{
	void *node = g_freelistPool009BBD2C.pop();
	void *slot = (char *)node + 8;
	if (slot != 0) {
		void *v = *arg;
		*(void **)slot = v;
	}
	return node;
}
