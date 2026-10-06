// cl: /MD /EHsc
//
// ?rva005CFFE8@Rva005CFFE8@@QAEXXZ @0x005CFFE8 76B: chain from 0x005EC4AF.
// Sibling of ?rva005D1129@Rva005D1129@@QAEXXZ (same 76B shape): calls the
// wrapper cleanup at 0x005EC4AF on +8, tests it with rowed 0x005EB87A,
// allocates an 8-byte link node with vtable 0x00C752A8, then updates the
// prior object's wrapper at +0x1C via rowed 0x00575674 and tail-runs its
// slot 1. Layout: +4 previous, +8 wrapper; previous has wrapper at +0x1C.

struct Rva005EB87AInner
{
	char m_pad[8];
	int m_field08;
};

class Rva005EB87A
{
public:
	Rva005EB87AInner *m_ptr;
	bool rva005EB87A();
};

class Object;

class Rva00575674
{
public:
	void rva00575674(Object *value);

private:
	Object *m_ptr;
};

class Rva005D1129Pointer
{
public:
	~Rva005D1129Pointer();
};

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

class Rva005CFFE8
{
public:
	void rva005CFFE8();
private:
	void *m_00;
	Rva005CFFE8Prev *m_04;
	Rva005D1129Pointer m_08;
};

void *__cdecl operator new(unsigned int size);

void Rva005CFFE8::rva005CFFE8()
{
	((Rva005D1129Pointer *)&m_08)->~Rva005D1129Pointer();
	if (((Rva005EB87A *)&m_08)->rva005EB87A())
		return;

	Rva005CFFE8Prev *previous = m_04;
	Rva005CFFE8LinkNode *node = (Rva005CFFE8LinkNode *)::operator new(8);
	if (node)
	{
		node->m_previous = previous;
		node->m_vtable = 0x00C752A8;
	}
	else
	{
		node = 0;
	}
	((Rva00575674 *)&previous->m_1C)->rva00575674((Object *)node);
	Rva005CFFE8Dispatch *dispatch = (Rva005CFFE8Dispatch *)*(void **)&previous->m_1C;
	dispatch->slot1();
}
