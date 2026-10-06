// cl: /DNDEBUG /MD
// ?Rva0029FB80Store@@YGPAXPAPAX@Z retail 0x0029FB80 28B
// Freelist store via rowed pop 0x002393E2 on pool 0xDA60E8 plus *arg into
// node+8. Returns node (EAX at ret) to keep lea-test; plain if.
// Caller 0x002A131A.
class FreelistPool
{
public:
	void *pop();
};

extern FreelistPool g_freelistPool;

void *__stdcall Rva0029FB80Store(void **p)
{
	void *node = g_freelistPool.pop();
	void **q = (void **)((char *)node + 8);
	if (q)
		*q = *p;
	return node;
}
