// cl: /O1 /MD
// Each destructor rowed in another unit is only declared here: the inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
//
// Original family: 15 scalar deleting destructors sharing the Rva006FB9B0DeletingDtor.cpp
// shape (35 bytes each): call the class complete destructor, then a sized
// release through one of two pinned chain-block pools. The class is named
// after its own deleting destructor RVA; the complete dtor is only declared
// and resolves through its symbols.csv pin (same recipe as the
// Rva004B8CDEDeletingDtor.cpp opaque-middle stub), so the local empty body is
// emission scaffolding, not a recovery claim. The stub is marked
// present-unmatched and the full dtor bodies stay unrowed.
//
// Variation per member: complete-dtor call target, pool object
// (0x00E176E8/Rva006DB270 or 0x00E176F4/Rva006D2A60) and class size.
// Fourteen more of this shape are rowed beside the destructors they call:
// 0x006D6570, 0x006E9B20, 0x006F2C70, 0x006F3960, 0x006FC0F0, 0x006FC190 in
// Rva006D6470Derived.cpp, 0x006DE280 and 0x006DE760 in
// Rva006D63C0Derived.cpp, 0x006F1DC0 in Rva006F1360Derived.cpp; and five
// more beside their own class destructors: 0x006D64D0
// (LadderPreferencesDtor.cpp), 0x006ECF90 (Rva006ECFC0Siblings.cpp),
// 0x006F15D0 (Rva006F1360Dtor.cpp), 0x006FBC60 (Rva006FBC90OwnerDtor.cpp),
// 0x00711350 (Rva00711330Dtor.cpp).

// Seven members whose local complete destructors differ from retail are
// preserved in Rva006CBF40Deferred.cpp; their provider repair remains pending.

// Abstract base here: the retail deleting destructor 0x006DE820 is its own
// unit's (Rva006DE350Dtor.cpp); novtable keeps this unit from emitting a copy.
#include "../../Include/Common/Rva006DE350.h"

#include "../../Include/Common/Rva006DB270.h"

#include "../../../Libraries/Source/Apt/Rva006D2A60.h"

extern Rva006DB270 *g_pChainBlockAllocator;   // 0x00E176E8
// 0x00E176F4, zero-filled .bss (4 bytes); defined here, the first of its
// referencing units in link order.
Rva006D2A60 *g_pChainBlockAllocatorF4 = 0;


class Rva006CBF40 : public Rva006DE350
{
public:
	explicit Rva006CBF40(int) {}
	virtual ~Rva006CBF40();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x5C]; // sizeof 0x60
};

// ?Rva006CBF40::~Rva006CBF40 present-unmatched
Rva006CBF40 *famgenNew_Rva006CBF40() { return new Rva006CBF40(0); }

void deleteRva006CBF40(Rva006CBF40 *p)
{
	delete p;
}

// Native6CEA60 is the sized deleting helper for the 28B checkpoint
// container. Its constructor in Apt.cpp has no vptr; the complete destructor
// in AptShutdownRva006CFAB0.cpp forwards to the container destructor6CE570.
class Rva006CEA60
{
public:
 ~Rva006CEA60();
 static void operator delete(void *p,unsigned size) { g_pChainBlockAllocator->freeBlock(p,size); }
 char m_storage[0x1c];
};
void deleteRva006CEA60(Rva006CEA60 *p) { delete p; }

class Rva006DA560 : public Rva006DE350
{
public:
	explicit Rva006DA560(int) {}
	virtual ~Rva006DA560();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x28]; // sizeof 0x2C
};

// ?Rva006DA560::~Rva006DA560 present-unmatched
Rva006DA560 *famgenNew_Rva006DA560() { return new Rva006DA560(0); }

void deleteRva006DA560(Rva006DA560 *p)
{
	delete p;
}

class Rva006F7DC0 : public Rva006DE350
{
public:
	explicit Rva006F7DC0(int) {}
	virtual ~Rva006F7DC0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[0x2C]; // sizeof 0x30
};

// ?Rva006F7DC0::~Rva006F7DC0 present-unmatched
Rva006F7DC0 *famgenNew_Rva006F7DC0() { return new Rva006F7DC0(0); }

void deleteRva006F7DC0(Rva006F7DC0 *p)
{
	delete p;
}

class Rva006F8D70 : public Rva006DE350
{
public:
	explicit Rva006F8D70(int) {}
	virtual ~Rva006F8D70();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[0x1C]; // sizeof 0x20
};

// ?Rva006F8D70::~Rva006F8D70 present-unmatched
Rva006F8D70 *famgenNew_Rva006F8D70() { return new Rva006F8D70(0); }

void deleteRva006F8D70(Rva006F8D70 *p)
{
	delete p;
}

// Retail's three pool records below derive from the class whose destructor is
// 0x006D6470 (rowed in LadderPreferencesDtor.cpp): their folded destructor
// 0x00709B80 tail-jumps there. novtable keeps this unit from emitting its table.
class __declspec(novtable) Rva006D6470Owner
{
public:
	virtual ~Rva006D6470Owner();
};

class Rva0070A530 : public Rva006D6470Owner
{
public:
	virtual ~Rva0070A530();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x40]; // sizeof 0x44
};

// Retail folds this empty destructor with its siblings' at 0x00709B80 (ICF).
Rva0070A530::~Rva0070A530()
{
}

void deleteRva0070A530(Rva0070A530 *p)
{
	delete p;
}

class Rva0070A560 : public Rva006D6470Owner
{
public:
	virtual ~Rva0070A560();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x2C]; // sizeof 0x30
};

// Retail folds this empty destructor with its siblings' at 0x00709B80 (ICF).
Rva0070A560::~Rva0070A560()
{
}

void deleteRva0070A560(Rva0070A560 *p)
{
	delete p;
}

class Rva0070A590 : public Rva006D6470Owner
{
public:
	virtual ~Rva0070A590();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x30]; // sizeof 0x34
};

// Retail folds this empty destructor with its siblings' at 0x00709B80 (ICF).
Rva0070A590::~Rva0070A590()
{
}

void deleteRva0070A590(Rva0070A590 *p)
{
	delete p;
}

