// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions: allocate-then-initialise bodies.

#include <new>

namespace _STL {

}

// The one-word node table the holder installs at +0: retail RVA 0x007EDAA0
// holds two code pointers, the shared scalar deleting destructor 0x005FAA31
// and 0x0023DAF7 (the member call after the +0x08 object). No other unit owns
// the word, so it is defined here beside its only writer.
extern "C" {
void __identifier("??_GRva004E84A4@@QAEPAXI@Z")();
void __identifier("?rva0023DAF7@Rva0023DAF7@@QAEXMH@Z")();
}
extern "C" void *__identifier("?g_bfme5RefVtable@@3PAXA")[2] =
{
	(void *)&__identifier("??_GRva004E84A4@@QAEPAXI@Z"),
	(void *)&__identifier("?rva0023DAF7@Rva0023DAF7@@QAEXMH@Z"),
};

extern void *g_bfme5RefVtable;

struct Bfme5RefNode
{
	void *m_bfmeVptr;
	int m_bfmeRefCount;
	int m_bfmePad;
};

class Bfme5RefHolderA
{
public:
	Bfme5RefHolderA(int unused);

	Bfme5RefNode *m_bfmeNode;
};

Bfme5RefHolderA::Bfme5RefHolderA(int unused)
{
	Bfme5RefNode *q = (Bfme5RefNode *)operator new(12);
	Bfme5RefNode *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfme5RefVtable;
		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;

	if (p)
		++p->m_bfmeRefCount;
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
