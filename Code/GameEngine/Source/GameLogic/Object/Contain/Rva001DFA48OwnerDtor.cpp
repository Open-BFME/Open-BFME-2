// cl: /Ob2 /DNDEBUG /MD /EHsc
// ??1Rva001DFEAABase@@UAE@XZ @0x1DFA48 (60B): virtual destructor.
// Formerly spelled ~TransportContainModuleData; that identity belongs to
// 0x004684F1 (slot 0 of TransportContainModuleData vtable 0x00C442F8, installed
// by ctor 0x00468301, calls it via ??_G 0x004684D5). This body installs a
// different vtable (0x7DC940), so its owner class is unrecovered.
// Installs vtable 0x7DC940 then destroys the two pool-aware members at +0xC
// and +0x8 (reverse order) through the 13B forwarder at 0x360D26.
// Identity: vtable install and the ??_G scalar-deleting
// destructor at 0x1DFA87 tail-calling here. The member type is unrecovered
// (not a string: strings route to releaseBuffer, this forwards to a pool op),
// so it keeps an address-derived name with an opaque pin.
// No base call is emitted (trivial base).

// The pool-aware member at +0x8/+0xC; only its address and non-virtual dtor
// are proven. It occupies four bytes (the two call sites are four apart).
class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

// The FXNugget base: its ctor 0x001DFEAA installs the same vtable 0x00BDC940
// as this dtor, so the dtor carries the ctor's class name.
#include "../../../../Include/GameClient/Rva001DFEAABase.h"

// ??1Rva001DFEAABase@@UAE@XZ
Rva001DFEAABase::~Rva001DFEAABase()
{
}
