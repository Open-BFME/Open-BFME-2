// cl: /GX-
class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *acquire(int size, int flags);
	virtual void release(void *block, int flags);
};
extern "C" int __cdecl printf(const char *fmt, ...);
GenAlloc *g_genAlloc;
GenAlloc *Gen007EFFC0()
{
	if (g_genAlloc == 0)
		printf("no FESL allocator defined\n");
	return g_genAlloc;
}
