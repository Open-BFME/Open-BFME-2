// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions: allocate-then-initialise bodies.

#include <new>

namespace _STL {

}

// The refcounted node the holder allocates is Rva0023DAE8 (RvaSmallVtableCtors.cpp):
// its table 0x007EDAA0 (slot 0 the shared scalar deleting destructor 0x005FAA31)
// is the vptr retail stores here, after the inlined base clears the count at +4.
// The holder inlines the constructor that unit rows out of line at 0x0023DAE8, so
// this view expands it in place and never emits it.
#include "../../Include/Common/Rva0007DF07.h"

class Rva0023DAE8 : public Rva0007DF07
{
public:
	__declspec(dllimport) __forceinline Rva0023DAE8(int) {}
	virtual ~Rva0023DAE8();

	int m_08;		// the holder allocates 12 bytes
};

class Bfme5RefHolderA
{
public:
	Bfme5RefHolderA(int unused);

	Rva0023DAE8 *m_bfmeNode;
};

Bfme5RefHolderA::Bfme5RefHolderA(int unused)
{
	Rva0023DAE8 *p = new Rva0023DAE8(unused);
	m_bfmeNode = p;
	if (p)
		++p->m_04;
}

// ??0Rva0023FC10@@QAE@URva0023FC10Arg@@@Z, retail 0x0023FC10 (19B, RET4).
// Target evidence: a constructor whose only work is running the holder
// constructor above on this, handing it the address of its own one-word
// by-value argument, then returning this (twin skeleton of the by-value
// timer-binder ctor 0x005C7D37). The holder row spells that parameter as an
// unused int, so the address is passed through that spelling. Owner, the
// argument's type and the holder's real parameter type are unresolved.
struct Rva0023FC10Arg
{
	int m_word;
};

class Rva0023FC10
{
public:
	Rva0023FC10(Rva0023FC10Arg arg);

	Bfme5RefHolderA m_holder;
};

Rva0023FC10::Rva0023FC10(Rva0023FC10Arg arg)
	: m_holder((int)&arg)
{
}
