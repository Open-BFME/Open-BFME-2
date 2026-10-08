// cl: /DNDEBUG /MD
// ?Rva00239BD8Alloc@@YGPAXPAPAX@Z @0x00239BD8 28B: freelist node alloc.
// Pops a 0x10 node from the pool object at 0x009BA5E0 (same pool whose
// head at 0x009BA5E8 the 0x00239380 clear drains to) via rowed
// ?pop@FreelistPool@@QAEPAXXZ, stores the caller's pointed value into
// the node at +8, and returns the node. Caller at 0x00239D06. No donor;
// honest address name.
class FreelistPool
{
public:
	void *pop();
};
extern FreelistPool g_freelistPool00DBA5E0;
void *__stdcall Rva00239BD8Alloc(void **arg)
{
	void *node = g_freelistPool00DBA5E0.pop();
	void *slot = (char *)node + 8;
	if (slot != 0) {
		void *v = *arg;
		*(void **)slot = v;
	}
	return node;
}
