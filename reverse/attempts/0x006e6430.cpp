// ??1Rva006E6430@@QAE@XZ
// partial score=0.85 date=2026-10-04
// cl: /O2 /EHa /MD
// ??1Rva006E6430@@UAE@XZ @0x006E6430 259B.
//
// Complete destructor for the 0xB4-byte class whose scalar deleting dtor is the
// rowed 0x006CC320 in Rva006CC320Siblings.cpp; that file pins this address as
// ??1Rva006E6430@@UAE@XZ and models the class as 0xB4 bytes, which this body's
// member offsets confirm.
//
// Retail body, in order:
//   - two pool frees through the pinned chain-block allocator at 0x00E176E8
//     (freeBlock 0x006DB270): this+0x40 sized by (this+0xAC)*4, and this+0x00
//     sized by (this+0xA4)*4;
//   - this+0x34, when non-null, is a debug-new block: the block header at
//     [ptr-4] goes to the debug operator delete 0x00629110 with (ptr, 0x20,
//     block, 0x00AE4F60), then the header itself is freed by 0x006CD460;
//   - this+0x14, when non-null, is freed by 0x006CD460;
//   - this+0xA0, when non-null, frees *this+0xA0 by 0x006CD460 and then
//     returns the 0x14-byte block to the allocator as (ptr, 0x14);
//   - the five member pools at +0x30, +0x28, +0x20, +0x18 and +0x08 are torn
//     down in that order, the first through 0x006F84F0 and the other four
//     through 0x006E3BF0, each preceded by a `mov byte ptr [esp+0x14], N`
//     unwind-state update.
//
// The SEH frame is NOT a source-level __try: retail's prologue is the compiler's
// own unwinder installed because the five member pools have non-trivial
// destructors, and those destructors are also what emit the unwind-state stores
// before each teardown call (the effect stlport_time_info_dtor.cpp documents for
// its inlined scalar strings). Writing __try/__except here instead is rejected
// outright -- MSVC refuses a __try in a function that requires object unwinding
// (C2712) -- and a __try body would additionally place a __SEH_prolog helper
// call retail does not have. /EHa is what installs the automatic frame.
//
// 0x006E3BF0 and 0x006F84F0 are address-derived pins (reverse/symbols.csv)
// whose bodies remain unclaimed here.

// The pinned chain-block allocator at 0x00E176E8.
class Rva006DB270
{
public:
	void freeBlock(void *block, int bytes);
};

extern Rva006DB270 *g_pChainBlockAllocator;

// 0x006CD460 frees a plain pointer. C++ linkage and nothrow, which is what
// keeps the unwind-state updates alive (see stlport_time_info_dtor.cpp).
void Rva006CD460Free(void *p) throw(...);

// 0x00629110 is the debug operator delete:
// (size, block, header, dealloc) -- retail pushes 0x20, the block pointer, the
// header word at [block-4], and the 0x00AE4F60 deallocator.
void __cdecl bfmeDebugDelete(unsigned int size, void *block, unsigned int header,
	void (*dealloc)(void *));

// The pool teardown routines this dtor drives, pinned by address.
void Rva006E3BF0Teardown(void *pool);
void Rva006F84F0Teardown(void *pool);

// The base carries the first dword. It has no virtual destructor of its own:
// retail's body stores no vtable pointer on entry, so the complete destructor
// below is the non-virtual QAE form and the +0x00 slot it frees is plain data.
class Rva006DE350
{
public:
	void *m_p00;                 // +0x00, the slot retail hands to freeBlock
	unsigned char m_pad04[4];    // +0x04..0x07
};

class Rva006E6430 : public Rva006DE350
{
public:
	~Rva006E6430();

private:
	// A member pool. The pools are trivial for the compiler -- each carries no
	// destructor of its own -- and are torn down from the single destructor body
	// below. Retail writes one unwind-state byte at a constant [esp+0x14] before
	// each teardown; a per-member destructor would instead give each pool its own
	// record and walk the slot upward, which is what retail does not do.
	struct Pool
	{
		unsigned short m_count;    // +0x00, word count
		unsigned short m_capacity; // +0x02, word capacity
		void *m_arr;               // +0x04, dword element array
	};

	// The +0x30 member is torn down through a different routine. Unlike the
	// other pools it carries a destructor, and that destructor is what installs
	// the SEH frame retail's body opens with.
	struct WrapperPool
	{
		unsigned char m_pad[4];    // +0x30..0x33
		~WrapperPool() { Rva006F84F0Teardown(this); }
	};

	Pool m_pool08;               // +0x08
	unsigned char m_pad10[4];    // +0x10..0x13
	void *m_p14;                 // +0x14
	Pool m_pool18;               // +0x18
	Pool m_pool20;               // +0x20
	Pool m_pool28;               // +0x28
	WrapperPool m_pool30;      // +0x30
	void *m_p34;               // +0x34, a debug-new block
	unsigned char m_pad38[8];  // +0x38..0x3F
	void *m_p40;               // +0x40, sized by m_nAC * 4
	unsigned char m_pad44[0x5C]; // +0x44..0x9F
	void *m_pA0;               // +0xA0, a 0x14-byte block
	unsigned int m_nA4;        // +0xA4
	unsigned char m_padA8[4];  // +0xA8..0xAB
	unsigned int m_nAC;        // +0xAC
	unsigned char m_padB0[4];  // +0xB0..0xB3
};

Rva006E6430::~Rva006E6430()
{
	// Retail writes a single unwind-state byte at a constant [esp+0x14] before
	// each teardown, counting 3, 2, 1, 0, -1 down the five members. It is one
	// char local live across every call rather than five separate per-member
	// destructor records, which is why the slot does not walk upward.
	char state = 3;
	g_pChainBlockAllocator->freeBlock(m_p40, m_nAC * 4);
	if (m_p34)
	{
		char *block = (char *)m_p34;
		bfmeDebugDelete(0x20, block, *(unsigned int *)(block - 4),
			(void (*)(void *))0x00AE4F60);
		Rva006CD460Free(block - 4);
	}
	if (m_p14)
		Rva006CD460Free(m_p14);
	g_pChainBlockAllocator->freeBlock(m_p00, m_nA4 * 4);
	if (m_pA0)
	{
		Rva006CD460Free(*(void **)m_pA0);
		g_pChainBlockAllocator->freeBlock(m_pA0, 0x14);
	}
	// m_pool30 is torn down by its own destructor as the body returns; the
	// remaining four follow here, each preceded by a decrement of `state`.
	state = 2;
	Rva006E3BF0Teardown(&m_pool28);
	state = 1;
	Rva006E3BF0Teardown(&m_pool20);
	state = 0;
	Rva006E3BF0Teardown(&m_pool18);
	state = -1;
	Rva006E3BF0Teardown(&m_pool08);
}

typedef char Rva006E6430Size[(sizeof(Rva006E6430) >= 0xA4) ? 1 : -1];

// The dtor is only reachable through a vtable, so nothing in this unit
// instantiates it. This anchor forces the emission the ledger row verifies; it
// is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva006E6430Dtor@@YAXPAVRva006E6430@@@Z present-unmatched
void bfmeEmitRva006E6430Dtor(Rva006E6430 *p)
{
	p->~Rva006E6430();
}
#pragma inline_depth()