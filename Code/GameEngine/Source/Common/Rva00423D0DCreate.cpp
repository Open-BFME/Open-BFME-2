// cl: /O1 /MD
// ?rva00423D0DCreate@@YGHPAXH@Z @0x00423D0D 34B (name TBD, free stdcall)
extern void *rva000307F0_new(unsigned size, int dummy);
extern void rva00423648_init(void *p, int a);
void *__stdcall rva00423D0DCreate(int a)
{
	void *blk = rva000307F0_new(0x14, 0);
	rva00423648_init((char *)blk + 8, a);
	return blk;
}
