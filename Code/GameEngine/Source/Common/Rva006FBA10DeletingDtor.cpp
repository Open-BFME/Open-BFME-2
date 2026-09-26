// cl: /O1 /MD
// ??_GRva006FBA10@@UAEPAXI@Z, retail 0x006FB9E0, 35 bytes.
// Scalar deleting destructor for Rva006FBA10 (vtable 0x008ED844, slot 14
// offset 0x38 per tf.py vslot). Calls the rowed complete dtor at 0x006FBA10
// (11B vptr store + tail-jmp to pinned base 0x006DE350), then sized release
// through the pinned pool deallocator 0x006DB270 with the pool object at
// 0x00E176E8 and class size 0xC. Same sized-pool-free recipe as the sibling
// ??_GRva006FB9B00 at 0x006FB980; the dtor stays empty so the local ??1 copy
// remains 11B.

class Rva006DE350
{
public:
	virtual ~Rva006DE350();
};

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva006FBA10 : public Rva006DE350
{
public:
	virtual ~Rva006FBA10();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[8]; // +0x04..0x0B: sizeof 0xC for the sized delete
};

Rva006FBA10::~Rva006FBA10()
{
}

void deleteRva006FBA10(Rva006FBA10 *p)
{
	delete p;
}
