// cl: /DNDEBUG /MD /EHs
// ??1AIUpgradeHeuristicFactoryUnlock@@UAE@XZ @0x005DA7F5 60B
// Opaque dtor called by the rowed ??_G 0x005DA7D9 (vtable 0x00C76510#1).
// Target facts: stores its two-slot vtable 0x00C76510 { 0x005DA67F,
// ??_G 0x005DA7D9 }. Constructor 0x005DA831 separately installs the next
// table at 0x00C76518; its 0x005DA854 entry is not a third slot here.
// This destructor frees the malloc'd buffer at +0x08 through the CRT free
// (0x00030830) when non-null, then the inline base dtor resets to the base
// vtable 0x00C70B80 { __purecall, ??_G (Rva005DAA36), slot 2 }. Retail keeps
// EH state 0 (base subobject) around the extern "C" free, which cl only does
// under /EHs (TU-scoped flag). The table and deleting wrapper tie this
// lifetime to the constructor at 0x005DA6F3.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

// Base view as in V3PolyCopyCtors.cpp / Rva005DA64BCtor.cpp (two virtuals),
// so this unit's ??_7Rva005DAA36@@6B@ copy is the one the link keeps.
class Rva005DAA36
{
public:
	virtual int rva005DA67F(int) = 0;
	virtual ~Rva005DAA36() {}
};

class AIUpgradeHeuristicFactoryUnlock : public Rva005DAA36
{
public:
	virtual int rva005DA67F(int);
	virtual ~AIUpgradeHeuristicFactoryUnlock();

private:
	int m_04;
	void *m_buffer; // +0x08
};

AIUpgradeHeuristicFactoryUnlock::~AIUpgradeHeuristicFactoryUnlock()
{
	if (m_buffer)
		free(m_buffer);
}
