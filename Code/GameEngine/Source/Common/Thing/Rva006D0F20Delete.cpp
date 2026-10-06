// cl: /MD
// ?rva006D1100@Rva006D0F20@@QAEPAXI@Z, retail 0x006D1100, 35 bytes.
// Chain deleting helper for the Nugget-chain block family: calls the rowed
// release at 0x006D0F20, then sized release through the rowed pool
// deallocator 0x006DB270 with the pool object at 0x00E176E8 and class size
// 0x10, returning this. Same 35B flag-free shape as Rva006CE630Delete.
class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

struct Rva006D0F20
{
	void release();
	void *rva006D1100(unsigned int flags);
};

void *Rva006D0F20::rva006D1100(unsigned int flags)
{
	release();
	if ((flags & 1) != 0)
		g_pChainBlockAllocator->freeBlock(this, 0x10);
	return this;
}
