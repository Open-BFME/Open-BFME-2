// ??1Rva006C1F60@@QAE@XZ @ 0x006C3CC0 (93B).
//
// The destructor of the Rva006C1F60 allocator: its body flushes through
// rva006C38D0() (the rowed 0x006C38D0 teardown predicate), then lets the
// compiler destroy the +0x684 chain-array member and the GeneralAllocator
// base. Evidence for the destructor reading is the C++ EH frame: its unwind
// funclets are exactly `this+0x684 -> 0x006C21B0` (the out-of-line
// Rva006C17B0 destructor, which calls rva006C17B0(true,false)) and
// `this -> 0x00034D00` (the base destructor thunk). Normal-path member
// destruction inlines the same wrapper and calls 0x006C17B0 directly.
//
// Class view and layout come from the rowed Rva006C38D0Cluster.cpp; this TU
// only re-states the member/base needed to place the implicit destructor
// calls. The base destructor thunk at0x00034D00 calls the separately rowed
// bool teardown body at0x00033D50.

#include "../../Include/Common/GeneralAllocator.h"

class Rva006C17B0
{
public:
	~Rva006C17B0();
	void rva006C17B0(bool flag1, bool flag2);
};

// ?Rva006C17B0::~Rva006C17B0 present-unmatched
// Rva006C17B0's destructor is an inline wrapper over rva006C17B0(true,false).
// Retail keeps an out-of-line copy at 0x006C21B0 (used by unwind funclets and
// reached by 0x006C17B0's own sibling). That10B body is already rowed as
// rva006C21B0 in Rva006C17B0.cpp; this differently decorated inline destructor
// retains its existing marker/pin and is outside this base-provider repair.
inline Rva006C17B0::~Rva006C17B0()
{
	rva006C17B0(true, false);
}

class Rva006C1F60 : public EA::Allocator::GeneralAllocator
{
public:
	~Rva006C1F60();
	bool rva006C38D0();

private:
	unsigned char m_pad0[0x174];
	Rva006C17B0 m_684;
};

Rva006C1F60::~Rva006C1F60()
{
	rva006C38D0();
}
