// cl: /MD /DNDEBUG
// ?rva006FBED0@Rva8D0D80Result@@QAEXXZ @ 0x006FBED0 (150B).
//
// Address-derived recovery of the Rva8D0D80Result delayed-free flush that
// installs a fresh garbage-collector root. The class and the +0x28 list field
// come from the near file Rva006FBE60Cluster.cpp, which forwards to the same
// family through the same global 0x00E1835C; only the two offsets this body
// reads are named here, because the full object is not otherwise recovered.
// The receiver is NOT virtual -- retail reads this+0x28 and this+0x2C directly
// with no vtable load -- so the virtual call belongs to the root object built
// inside the fresh block, which is a different type.
//
// Both branches take one 0x20-byte block from the chain-block pool at
// 0x00E176F4 through the rowed Rva006D2A60::allocBlock at 0x006D29E0 (ret 4,
// self-cleaning), spelled here as `new` because that is the shape the sibling
// rowed BfmeQuery1279 ctor at 0x006F7B20 uses for the same pool: the
// `mov [esp+4],eax / test eax,eax / mov [esp+0x10],N / je` sequence is MSVC7's
// new-expression null check plus its SEH scope state, where N is 0 on the
// count!=0 path and 1 on the count==0 path.
//
// The unsigned16 count at this+0x2C decides which unnamed constructor builds
// the root inside the block:
//
//   count != 0  the pair constructor 0x006FBB10 (count, m_run);
//   count == 0  the single constructor 0x006FBAA0 (m_run).
//
// The new root is stored into the global 0x00E1835C and its virtual slot 0 is
// called, which is how the near file's global is maintained. A failed allocation
// stores null through the shared `xor eax,eax` landing pad.

#include "../../../Libraries/Source/Apt/Rva006D2A60.h"

extern Rva006D2A60 *g_pChainBlockAllocatorF4; // VA 0x00E176F4

// The Apt value base the rowed cluster Rva006D93D0Cluster.cpp already uses.
// It is what supplies slot 0 and slot 1 of the root, and its virtual shape is
// what makes MSVC emit the new-expression SEH scope state this body carries.
class BfmeAptValue006DCD20
{
public:
	virtual void slot0();
	virtual void release();
};

// The garbage-collector root installed into the global; the near file pins the
// same slot for Rva006FBE60. Only slot 0 is used here.
class Rva006FBED0Root : public BfmeAptValue006DCD20
{
public:
	// Retail allocates exactly 0x20 bytes for the root, so the class is padded
	// to that size: the new-expression passes sizeof(*this) to the pool.
	char m_pad[0x1c];

	static void *operator new(unsigned int size)
	{
		return g_pChainBlockAllocatorF4->allocBlock((int)size);
	}
};

// The two constructors (0x006FBAA0 single run, 0x006FBB10 run plus count) are
// rowed as Rva006FBC90Owner's; the root is built through that view and the
// result stored as the root. Same 0x20 size and pool operator new.
class AptValue;
class Rva006FBC90Owner
{
public:
	Rva006FBC90Owner(AptValue *run);
	Rva006FBC90Owner(AptValue *run, int count);
	char m_pad[0x20];

	static void *operator new(unsigned int size)
	{
		return g_pChainBlockAllocatorF4->allocBlock((int)size);
	}
	// The matching sized delete frees a failed construction (unwind actions
	// 0x007AA220/0x007AA22F push the 0x20 extent and call native 0x006F12F0).
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, (int)size);
	}
};

// The receiver: the Rva8D0D80Result list owner the near file describes.
class Rva8D0D80Result
{
public:
	void rva006FBED0();

	unsigned char m_unaccessed[0x28];
	void *m_run;            // +0x28
	unsigned short m_count; // +0x2C
};

class AptFrameStack;
extern "C" AptFrameStack *__identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A");

// ?rva006FBED0@Rva8D0D80Result@@QAEXXZ @ 0x006FBED0 (150B)
void Rva8D0D80Result::rva006FBED0()
{
	// Retail calls no default constructor on the fresh block: it stores the
	// allocation result straight into the frame slot and then calls one of the
	// two named ctors. Spelled as new-with-initialiser so MSVC emits the same
	// store and the same single post-new call.
	// The global is written on both arms and then read back for the virtual
	// call, which is what keeps the allocation result in eax across the store.
	if (m_count)
		__identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A") = (AptFrameStack *)new Rva006FBC90Owner((AptValue *)m_run, m_count);
	else
		__identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A") = (AptFrameStack *)new Rva006FBC90Owner((AptValue *)m_run);

	((Rva006FBED0Root *)__identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A"))->slot0();
}
