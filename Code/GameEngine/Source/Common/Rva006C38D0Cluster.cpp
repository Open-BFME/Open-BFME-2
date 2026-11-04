// ?rva006C38D0@Rva006C1F60@@QAE_NXZ @ 0x006C38D0 (99B).
//
// The body sits immediately above the rowed 0x006C3840 lock-guarded setter
// (Rva006C3840Cluster.cpp) and shares its Rva006C1F60 layout, so the class, the
// 0x006C33D0 callee and the +0x4E4 lock are already established.
//
// Its callee 0x00033D50 was named nowhere in the ledger and is now pinned as an
// address-derived member of this class. That it is a MEMBER rather than a free
// function is target evidence, not a guess: 0x33D50 AddRefs this+0x4E4 on
// entry, walks the +0x49C map and the +0x448 sentinel list, then stores 0 to
// +0x4E4 and Release/Deletes the lock -- memory_pool.cpp already proves +0x448
// as a list sentinel and +0x4E4 as a Lock*, and Rva006C1F60.cpp proves +0x4E4
// on this class. It is also reached through the jump thunk 0x00034D00.
//
// Structural inference, NOT proven identity: 0x6C38D0 propagates the byte
// 0x33D50 returns and invokes it on the same object, so it reads as a
// teardown/flush predicate that always clears the +0x510 byte.
//
// +0x678 is read as a self-pointer: this body compares it against `this` and
// calls 0x006C17B0 on the +0x684 sub-object only when they are equal. Field
// labels below are descriptive; only the offsets are target facts.
//
// The sibling body at 0x006C3940 was recovered from the same neighbourhood and
// is banked as a partial attempt (reverse/attempts/0x006c3940.cpp, score 0.72):
// its fencepost sequence and retry semantics are byte-exact, but MSVC 7.1
// rotates every loop form into a two-call shape instead of retail's single
// allocation with the back-edge at 0x006C3966. Its layout findings are
// retained below because they come from its retail bytes.
//
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

// Private view of the rowed array-of-chains class (0x006C17B0); only its state
// fields are touched here, because 0x6C38D0 inlines the four stores instead of
// calling the 0x006C17B0 body. The field WIDTHS below are target facts, read
// off the stores themselves: +0x684, +0x68C and +0x694 take a DWORD while
// +0x688 takes a BYTE, so the field at +4 is a byte and not the int the rowed
// Rva006C17B0.cpp view happens to carry.
class Rva006C17B0
{
public:
	void rva006C17B0(bool flag1, bool flag2);

	void *m_array;			// +0x00
	unsigned char m_pad4;		// +0x04
	unsigned char m_pad5[3];
	unsigned int m_count;		// +0x08
	int m_padC;			// +0x0C, untouched by 0x006C38D0
	int m_10;			// +0x10
};

// Rva006C1F60 is itself a GeneralAllocator: memory_pool.cpp proves +0x448 as
// that class's list sentinel and +0x4E4 as its Lock*, and 0x00033D50 reads both
// through `this`. The canonical base is 0x510 bytes, so the derived members
// below start at +0x510; the banked 0x006C3940 body needed 0x00035080 through it and that pin
// already exists under the GeneralAllocator name.
#include "../../Include/Common/GeneralAllocator.h"

class Rva006C1F60 : public EA::Allocator::GeneralAllocator
{
public:
	bool rva006C38D0();


	void rva006C33D0(int a, int b);

private:
	unsigned char m_510;		// +0x510, the first member past the base
	unsigned char m_pad3[0x548 - 0x510 - 1];
	char *m_548;
	char *m_54C;
	char *m_550;
	char *m_554;
	unsigned char m_pad4[0x678 - 0x554 - 4];
	Rva006C1F60 *m_678;
	unsigned char m_pad5[0x684 - 0x678 - 4];
	Rva006C17B0 m_684;
};

bool Rva006C1F60::rva006C38D0()
{
	rva006C33D0(0, 0);
	bool result = GeneralAllocator::rva00033D50();
	m_510 = 0;
	if (m_678 == this)
	{
		m_684.m_array = 0;
		m_684.m_pad4 = 0;
		m_684.m_count = 0;
		m_684.m_10 = 0;
	}
	else
	{
		m_684.rva006C17B0(true, true);
	}
	return result;
}