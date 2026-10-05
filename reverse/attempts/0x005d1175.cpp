// ??0Rva005D1129@@QAE@PAX@Z
// partial score=0.83 date=2026-10-06
// cl: /O1 /MD /EHsc
//
// Target layout read from 0x005D1129: a next pointer at +4 and a one-pointer
// wrapper at +8. Its constructor at 0x005D1175 confirms those offsets. The
// 76-byte body calls the wrapper cleanup at 0x005EC4AF, tests it with the
// rowed 0x005EB87A predicate, and on the other path allocates an 8-byte link
// node with vtable 0x00C755A4 before updating the prior object's wrapper.

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
class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;

class Rva00575674
{
public:
	void rva00575674(Object *value);

private:
	Object *m_ptr;
};

// One-pointer layout view. The +8 cleanup call at 0x005EC4AF is represented as
// its destructor; the target class relationship remains unproven.
class Rva005D1129Pointer
{
public:
	__forceinline Rva005D1129Pointer() : m_ptr(0) {}
	~Rva005D1129Pointer();

private:
	Object *m_ptr;
};

class Rva005D1129;

class __declspec(novtable) Rva005D1129Base
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;

	__forceinline Rva005D1129Base(void *vtable)
	{
		m_previous = 0;
		*(void **)this = vtable;
	}

protected:
	Rva005D1129 *m_previous;
};

class Rva005D1064Node
{
public:
	Rva005D1064Node(Rva005D1129 *owner, void *source);

private:
	void *m_vtable;
	Rva005D1129 *m_previous;
	Rva00575674 m_pointer;
};

struct Rva005D1129LinkNode
{
	unsigned int m_vtable;
	Rva005D1129 *m_previous;
};

class Rva005D1129Dispatch
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
};

class __declspec(novtable) Rva005D1129 : public Rva005D1129Base
{
public:
	Rva005D1129(void *vtable);
	void rva005D1129();

private:
	Rva005D1129Pointer m_pointer;
};

void *__cdecl operator new(unsigned int size);
void *__cdecl rva005ED198(Rva002BA8F1Logic *source);

Rva005D1129::Rva005D1129(void *vtable) : Rva005D1129Base(vtable), m_pointer()
{
	Rva002BA8F1Logic *global = g_009FEF10;
	m_previous = global ? (Rva005D1129 *)rva005ED198(global) : 0;
	if (m_previous)
	{
		new Rva005D1064Node(this, m_previous);
	}
	else
	{
		Rva005D1129LinkNode *node = (Rva005D1129LinkNode *)::operator new(8);
		if (node)
		{
			node->m_previous = this;
			node->m_vtable = 0x00C755A4;
		}
		else
		{
			node = 0;
		}
		((Rva00575674 *)&m_pointer)->rva00575674((Object *)node);
	}
}

void Rva005D1129::rva005D1129()
{
	m_pointer.~Rva005D1129Pointer();
	if (((Rva005EB87A *)&m_pointer)->rva005EB87A())
		return;

	Rva005D1129 *previous = m_previous;
	Rva005D1129LinkNode *node = (Rva005D1129LinkNode *)::operator new(8);
	if (node)
	{
		node->m_previous = previous;
		node->m_vtable = 0x00C755A4;
	}
	else
	{
		node = 0;
	}
	((Rva00575674 *)&previous->m_pointer)->rva00575674((Object *)node);
	Rva005D1129Dispatch *dispatch = (Rva005D1129Dispatch *)*(void **)&previous->m_pointer;
	dispatch->slot1();
}
