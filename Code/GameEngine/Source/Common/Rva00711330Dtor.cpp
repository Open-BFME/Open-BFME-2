// cl: /MD
//
// Opaque destructor with a member clear tail-calling
// Rva006D6470Owner::~Rva006D6470Owner at 0x006D6470.
// The class below stores its own vtable (0xCEFB40, DIR32 auto-patch), clears
// its pointer member at +0x20, and tail-jumps to the base destructor; the
// base itself is only declared here (defined nowhere), because a same-TU
// definition would capture the call locally instead of at the ledger address.
// Dedicated speed-flags TU: the /O1 shared TU
// compacts the member clear to and-form ahead of the vptr store, while
// retail uses the speed-form mov after it. The opaque derived identity remains
// unresolved.

// The scalar deleting destructor emitted here releases through the
// chain-block pool at 0x00E176F4 with the class size, as retail's does.
class Rva006D2A60
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006D2A60 *g_pChainBlockAllocatorF4;   // 0x00E176F4

class Rva006D6470Owner
{
public:
	virtual ~Rva006D6470Owner();
};

class Rva00711330 : public Rva006D6470Owner
{
public:
	virtual ~Rva00711330();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}

private:
	char m_pad04[0x20 - 4];
	void *m_ptr20;
};

Rva00711330::~Rva00711330()
{
	m_ptr20 = 0;
}
