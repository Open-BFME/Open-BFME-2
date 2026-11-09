// cl: /O1 /MD
// Sized deleting helpers moved unchanged from Rva006CBF40Siblings.cpp.
// Their existing local complete-destructor emission bodies do not reproduce
// retail and still require real providers; no new identity or layout is claimed.
// The 35-byte native helpers and all their ledger evidence are preserved.
// Keep both chain-pool global definitions in their original owning units.

// Abstract base here: the retail deleting destructor 0x006DE820 is its own
// unit's (Rva006DE350Dtor.cpp); novtable keeps this unit from emitting a copy.
class __declspec(novtable) Rva006DE350
{
public:
	virtual ~Rva006DE350();
};

#include "../../Include/Common/Rva006DB270.h"

class Rva006D2A60
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator;   // 0x00E176E8
// 0x00E176F4; the definition remains in Rva006CBF40Siblings.cpp.
extern Rva006D2A60 *g_pChainBlockAllocatorF4;


class Rva006CC2F0 : public Rva006DE350
{
public:
	virtual ~Rva006CC2F0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
};

// ?Rva006CC2F0::~Rva006CC2F0 present-unmatched
Rva006CC2F0::~Rva006CC2F0()
{
}

void deleteRva006CC2F0(Rva006CC2F0 *p)
{
	delete p;
}

class Rva006CD620 : public Rva006DE350
{
public:
	virtual ~Rva006CD620();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x4]; // sizeof 0x8
};

// ?Rva006CD620::~Rva006CD620 present-unmatched
Rva006CD620::~Rva006CD620()
{
}

void deleteRva006CD620(Rva006CD620 *p)
{
	delete p;
}

class Rva006D71B0 : public Rva006DE350
{
public:
	virtual ~Rva006D71B0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[0x4]; // sizeof 0x8
};

// ?Rva006D71B0::~Rva006D71B0 present-unmatched
Rva006D71B0::~Rva006D71B0()
{
}

void deleteRva006D71B0(Rva006D71B0 *p)
{
	delete p;
}

// Retail's deleting helper calls ??1AptValueWithHash@@MAE@XZ at 0x006D63C0, rowed in its own unit.
class AptValueWithHash
{
protected:
	virtual ~AptValueWithHash();
	friend class Rva006D71E0;
};

class Rva006D71E0
{
public:
	virtual ~Rva006D71E0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x18]; // sizeof 0x1C
};

// ?Rva006D71E0::~Rva006D71E0 present-unmatched
__declspec(noinline) Rva006D71E0::~Rva006D71E0()
{
	reinterpret_cast<AptValueWithHash *>(this)->AptValueWithHash::~AptValueWithHash();
}

void deleteRva006D71E0(Rva006D71E0 *p)
{
	delete p;
}

// Retail's deleting helper calls ??1S4Dtor00587B30@@UAE@XZ at 0x006E96D0, rowed in its own unit.
class S4Dtor00587B30
{
public:
	virtual ~S4Dtor00587B30();
};

class Rva006E9B50
{
public:
	virtual ~Rva006E9B50();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x24]; // sizeof 0x28
};

// ?Rva006E9B50::~Rva006E9B50 present-unmatched
__declspec(noinline) Rva006E9B50::~Rva006E9B50()
{
	reinterpret_cast<S4Dtor00587B30 *>(this)->S4Dtor00587B30::~S4Dtor00587B30();
}

void deleteRva006E9B50(Rva006E9B50 *p)
{
	delete p;
}

class Rva006EC170 : public Rva006DE350
{
public:
	virtual ~Rva006EC170();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[0x1C]; // sizeof 0x20
};

// ?Rva006EC170::~Rva006EC170 present-unmatched
Rva006EC170::~Rva006EC170()
{
}

void deleteRva006EC170(Rva006EC170 *p)
{
	delete p;
}

// Retail's deleting helper calls ??1Rva006FE460@@UAE@XZ at 0x006FE460, rowed in its own unit.
class Rva006FE460
{
public:
	virtual ~Rva006FE460();
};

class Rva006FE430
{
public:
	virtual ~Rva006FE430();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x20]; // sizeof 0x24
};

// ?Rva006FE430::~Rva006FE430 present-unmatched
__declspec(noinline) Rva006FE430::~Rva006FE430()
{
	reinterpret_cast<Rva006FE460 *>(this)->Rva006FE460::~Rva006FE460();
}

void deleteRva006FE430(Rva006FE430 *p)
{
	delete p;
}
