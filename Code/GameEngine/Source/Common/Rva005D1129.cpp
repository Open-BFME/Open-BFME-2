// cl: /MD /EHsc
//
// ?slot1@Rva005D10F9@@UAEXXZ: slot 1 of Rva005D10F9's vftable 0x008755AC (whose
// ctor 0x005D1064 installs it); rowed earlier as ?rva005D1129@Rva005D1129.
// Target layout read from 0x005D1129: a next pointer at +4 and a one-pointer
// wrapper at +8. Its constructor at 0x005D1175 confirms those offsets. The
// 76-byte body calls the wrapper cleanup at 0x005EC4AF, tests it with the
// rowed 0x005EB87A predicate, and on the other path allocates an 8-byte link
// node with vtable 0x00C755A4 before updating the prior object's wrapper.

extern "C" const void *const __identifier("??_7Rva005D1052@@6B@")[];  // folded, 2 classes; via ??_7Rva005D1052@@6B@

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../Include/Common/Rva005EB87AInner.h"

#include "../../Include/Common/Rva005EB87A.h"

class Object;
class Rva002BA8F1Logic;

#include "../../Include/Common/Rva00575674.h"

// One-pointer layout view. The +8 cleanup call at 0x005EC4AF is represented as
// its destructor; the target class relationship remains unproven.
#include "../../Include/Common/Rva005D1129Pointer.h"

class Rva005D10F9;

class __declspec(novtable) Rva005D1129Base
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;

protected:
	Rva005D10F9 *m_previous;
};

class Rva005D1064Node
{
public:
	Rva005D1064Node(Rva005D10F9 *owner, void *source);

private:
	void *m_vtable;
	Rva005D10F9 *m_previous;
	Rva00575674 m_pointer;
};

struct Rva005D1129LinkNode
{
	unsigned int m_vtable;
	Rva005D10F9 *m_previous;
};

class Rva005D1129Dispatch
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
};

class __declspec(novtable) Rva005D10F9 : public Rva005D1129Base
{
public:
	virtual void slot1();

private:
	Rva005D1129Pointer m_pointer;
};

#include <new>

void Rva005D10F9::slot1()
{
	m_pointer.~Rva005D1129Pointer();
	if (((Rva005EB87A *)&m_pointer)->rva005EB87A())
		return;

	Rva005D10F9 *previous = m_previous;
	Rva005D1129LinkNode *node = (Rva005D1129LinkNode *)::operator new(8);
	if (node)
	{
		node->m_previous = previous;
		node->m_vtable = ((unsigned int)__identifier("??_7Rva005D1052@@6B@"));
	}
	else
	{
		node = 0;
	}
	((Rva00575674 *)&previous->m_pointer)->rva00575674((Object *)node);
	Rva005D1129Dispatch *dispatch = (Rva005D1129Dispatch *)*(void **)&previous->m_pointer;
	dispatch->slot1();
}
