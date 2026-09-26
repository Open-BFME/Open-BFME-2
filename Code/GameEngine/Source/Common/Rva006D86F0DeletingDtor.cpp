// cl: /O1 /MD
// ??_GRva006D86F0@@UAEPAXI@Z, retail 0x006D86C0, 35 bytes.
// Scalar deleting destructor for Rva006D86F0 (vtable 0x008EA560, slot 14
// offset 0x38 per tf.py vslot). Calls the rowed complete dtor at 0x006D86F0
// (11B vptr store + tail-jmp to pinned base 0x006DE350), then sized release
// through the pinned pool deallocator 0x006DB270 with the pool object at
// 0x00E176E8 and class size 0xC. Sized operator delete inlines to the retail
// mov ecx,[pool] + push 0xC + push this + call shape (SizedDeleteDestructors
// precedent); the dtor stays empty so the local ??1 copy remains 11B.

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

class Rva006D86F0 : public Rva006DE350
{
public:
	virtual ~Rva006D86F0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[8]; // +0x04..0x0B: sizeof 0xC for the sized delete
};

Rva006D86F0::~Rva006D86F0()
{
}

void deleteRva006D86F0(Rva006D86F0 *p)
{
	delete p;
}
