// cl: /MD
// ??_GRva006D6D20@@UAEPAXI@Z @0x006D7320 35B.
// Scalar deleting dtor calls rowed ??1 at 0x006D6D20 plus sized pool free
// via pinned 0x006DB270 with pool g_pChainBlockAllocator 0x00E176E8 and
// class size 0x10.
class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8
// g_pChainBlockAllocator: matched references place it at VA 0xe176e8 (zero-filled .bss).
Rva006DB270 * g_pChainBlockAllocator;

class Rva006D6D20
{
public:
	__declspec(noinline) virtual ~Rva006D6D20();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[0x10 - 4];
};

Rva006D6D20::~Rva006D6D20() { m_pad[0] = 0; }
void deleteRva006D6D20(Rva006D6D20 *p) { delete p; }
