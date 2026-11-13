// cl: /MD /EHsc
//
// ?Update@Rva005CFFB8@@UAEXXZ @0x005CFFE8 76B: Rva005CFFB8's Update (slot 1 of
// its table 0x00C752EC; dtor 0x005CFFB8), chain from 0x005EC4AF.
// Sibling of ?rva005D1129@Rva005D1129@@QAEXXZ (same 76B shape): calls the
// wrapper cleanup at 0x005EC4AF on +8, tests it with rowed 0x005EB87A,
// allocates an 8-byte link node with vtable 0x00C752A8, then updates the
// prior object's wrapper at +0x1C via rowed 0x00575674 and tail-runs its
// slot 1. Layout: +4 previous, +8 wrapper; previous has wrapper at +0x1C.

extern "C" const void *const __identifier("??_7Rva005CF925@@6B@")[];  // folded, 3 classes; via ??_7Rva005CF925@@6B@

#include "../../Include/Common/Rva005EB87AInner.h"

#include "../../Include/Common/Rva005EB87A.h"

class Object;

#include "../../Include/Common/Rva00575674.h"

#include "../../Include/Common/Rva005D1129Pointer.h"

class Rva005CFFE8Prev
{
public:
	char m_pad00[0x1C];
	Rva00575674 m_1C;
};

struct Rva005CFFE8LinkNode
{
	unsigned int m_vtable;
	Rva005CFFE8Prev *m_previous;
};

class Rva005CFFE8Dispatch
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
};

// The battle resolver state base (vtable 0x00C75290: ??_G, Update).
class Rva005CF872
{
public:
	virtual ~Rva005CF872() {}
	virtual void Update() {}
protected:
	Rva005CFFE8Prev *m_04;
};

class Rva005CFFB8 : public Rva005CF872
{
public:
	virtual void Update();
private:
	Rva005D1129Pointer m_08;
};

#include <new>

void Rva005CFFB8::Update()
{
	((Rva005D1129Pointer *)&m_08)->~Rva005D1129Pointer();
	if (((Rva005EB87A *)&m_08)->rva005EB87A())
		return;

	Rva005CFFE8Prev *previous = m_04;
	Rva005CFFE8LinkNode *node = (Rva005CFFE8LinkNode *)::operator new(8);
	if (node)
	{
		node->m_previous = previous;
		node->m_vtable = ((unsigned int)__identifier("??_7Rva005CF925@@6B@"));
	}
	else
	{
		node = 0;
	}
	((Rva00575674 *)&previous->m_1C)->rva00575674((Object *)node);
	Rva005CFFE8Dispatch *dispatch = (Rva005CFFE8Dispatch *)*(void **)&previous->m_1C;
	dispatch->slot1();
}
