// cl: /MD
//
// Opaque single-inheritance destructors tail-calling the matched
// Rva006D6470Owner::~ at 0x006D6470 (constructor row at 0x006D6410).
// Each class below stores its own vtable and tail-calls the base
// destructor; the base is only declared here so the call resolves through the
// matched row rather than a same-TU definition. Derived owner identities remain unproven
// (opaque Rva names). One ledger row per destructor, landed one commit at
// a time.

class Rva006D6470Owner
{
public:
	virtual ~Rva006D6470Owner();
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

class Rva006D65A0 : public Rva006D6470Owner
{
public:
	virtual ~Rva006D65A0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x20]; // sizeof 0x24
};

Rva006D65A0::~Rva006D65A0()
{
}

class Rva006E8F30 : public Rva006D6470Owner
{
public:
	virtual ~Rva006E8F30();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x20]; // sizeof 0x24
};

Rva006E8F30::~Rva006E8F30()
{
}

class Rva006F25D0 : public Rva006D6470Owner
{
public:
	virtual ~Rva006F25D0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x20]; // sizeof 0x24
};

Rva006F25D0::~Rva006F25D0()
{
}

class Rva006F3990 : public Rva006D6470Owner
{
public:
	virtual ~Rva006F3990();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x28]; // sizeof 0x2C
};

Rva006F3990::~Rva006F3990()
{
}

class Rva006FC120 : public Rva006D6470Owner
{
public:
	virtual ~Rva006FC120();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x60]; // sizeof 0x64
};

Rva006FC120::~Rva006FC120()
{
}

class Rva006FC1C0 : public Rva006D6470Owner
{
public:
	virtual ~Rva006FC1C0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x1C]; // sizeof 0x20
};

Rva006FC1C0::~Rva006FC1C0()
{
}

class Rva00709B80 : public Rva006D6470Owner
{
public:
	virtual ~Rva00709B80();
};

Rva00709B80::~Rva00709B80()
{
}
