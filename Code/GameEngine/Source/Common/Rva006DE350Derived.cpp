// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva006DE350::~
// Rva006DE350 at 0x006DE350 (pinned opaque dtor asserting IsDestroyedGC with
// vtable 0xCEAED0; exact method unproven). Each class below stores its own
// vtable and tail-calls the base destructor; the base itself is only declared
// here (defined nowhere -- it resolves via the pin), because a same-TU
// definition would capture the call locally instead of at the ledger address.
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.
//
// Rva006FB9B0 below is the exception: its retail table is AptValue's, so it
// derives from AptValue and reaches the base destructor through the rowed
// ??1AptValue@@MAE@XZ instead of the Rva006DE350 view's pin.

#include "../../Include/Common/Rva006DE350.h"

#include "../../../Libraries/Source/Apt/AptValue.h"

#include "../../Include/Common/Rva006DB270.h"

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva006D8510 : public Rva006DE350
{
public:
	virtual ~Rva006D8510();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[8]; // +0x04..0x0B: sizeof 0xC for the sized delete
};

Rva006D8510::~Rva006D8510()
{
}

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

class Rva006D88B0 : public Rva006DE350
{
public:
	virtual ~Rva006D88B0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[8]; // +0x04..0x0B: sizeof 0xC for the sized delete
};

Rva006D88B0::~Rva006D88B0()
{
}

// Rva006FB9B0 is an AptValue, not an opaque Rva006DE350: retail table
// 0x008ED808 has AptValue's own fifteen slots and differs from AptValue's
// 0x00CEAED0 only at 12, 13 and 14. Deriving from AptValue binds slots 0..11
// to AptValue's own bodies at retail's addresses and leaves this class's two
// overrides plus its deleting destructor, which is the whole of the
// difference. The destructor still stores its own table and tail-jumps to the
// base at 0x006DE350, now under the canonical ??1AptValue name rather than the
// Rva006DE350 view spelling.
//
// Slot 12 returns false and slot 13 is empty; retail folded both away, so each
// is rowed as an ICF twin with fold-proof=.
class Rva006FB9B0 : public AptValue
{
public:
	virtual ~Rva006FB9B0();
	virtual bool IsGarbageCollected() const;
	virtual void RegisterReferences() const;
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[4]; // AptValue is 8 bytes: +0x08..0x0B keeps sizeof 0xC
};

Rva006FB9B0::~Rva006FB9B0()
{
}

bool Rva006FB9B0::IsGarbageCollected() const { return false; }

void Rva006FB9B0::RegisterReferences() const {}

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
