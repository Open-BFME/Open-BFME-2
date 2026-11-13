// cl: -O1 -arch:SSE -G7 -MD -EHs
// ??1Rva002B74DE@@QAE@XZ retail 0x002B74DE 93B
// Non-virtual dtor with an empty body: member dtors in reverse order under EH
// states 2..0 -- the vectors at +0x1C and +0x10 (inline CRT free of each
// block), the holder at +0xC whose complete dtor matches the rowed
// ?clear@Rva002B430C@@QAEXXZ 0x002B430C, then the holder at +8 whose inline
// dtor runs the rowed ?rva002B2EA0@Rva002B2EA0@@QAEXXZ 0x002B2EA0.
// Names address-derived.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#include <new>
#undef _CRTIMP

class Rva002B2EA0
{
public:
	~Rva002B2EA0()
	{
		rva002B2EA0();
	}
	void rva002B2EA0();
private:
	void *m_ptr;
};

class Rva004FA2E2 { public: ~Rva004FA2E2(); };

#include "../../Include/Common/Rva002B430C.h"
// Native normal and unwind paths both call the complete26-byte owning
// teardown at2B430C: null the slot, destroy its pointee, then free storage.
Rva002B430C::~Rva002B430C()
{
    Rva004FA2E2 *old = m_ptr;
    m_ptr = 0;
    if (old) {
        old->Rva004FA2E2::~Rva004FA2E2();
        operator delete(old);
    }
}

class Rva002B74DEVector
{
public:
	~Rva002B74DEVector()
	{
		if (m_begin)
			free(m_begin);
	}

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class Rva002B74DE
{
public:
	~Rva002B74DE();

private:
	char m_pad00[8];
	Rva002B2EA0 m_holder08; // +0x08
	Rva002B430C m_holder0C; // +0x0C
	Rva002B74DEVector m_vector10; // +0x10
	Rva002B74DEVector m_vector1C; // +0x1C
};

Rva002B74DE::~Rva002B74DE()
{
}
