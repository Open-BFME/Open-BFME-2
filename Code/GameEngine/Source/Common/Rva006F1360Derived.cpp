// cl: /MD
//
// Opaque single-inheritance destructor tail-calling Rva006F1360::~
// Rva006F1360 at 0x006F1360 (matched opaque dtor with member clears in
// Rva006F1360Dtor.cpp; only declared here so the tail-call resolves to the
// ledger address instead of a same-TU definition). The class below stores
// its own vtable (0xCECD4C, DIR32 auto-patch) and tail-calls the base
// destructor. Owner identity is unproven (opaque Rva name). One ledger row
// per destructor, landed one commit at a time.

class Rva006F1360
{
public:
	virtual ~Rva006F1360();
};

// Pooled classes: the scalar deleting destructors emitted here release
// through the chain-block pool at 0x00E176F4 with the class size, as retail's
// do (rowed here; previously modelled by address-named views in
// Rva006CBF40Siblings.cpp).
class Rva006D2A60
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006D2A60 *g_pChainBlockAllocatorF4;   // 0x00E176F4

class Rva006F1DB0 : public Rva006F1360
{
public:
	virtual ~Rva006F1DB0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x24]; // sizeof 0x28
};

Rva006F1DB0::~Rva006F1DB0()
{
}
