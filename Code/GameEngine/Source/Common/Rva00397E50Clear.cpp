// cl: /DNDEBUG /MD
//
// ?rva00397E50@Rva00397E50@@QAEXXZ, retail 0x00397E50, 92 bytes.
// Vector clear at +0x80 with per-element unlink, GameLogic notify, virtual
// release and delete, then erase. Evidence: rowed Unlink 0x002E3714,
// rowed Rva0023D661 0x0023D661 via TheGameLogic 0x009FE78C,
// virtual slot0 with 0 plus operator delete 0x0002FD60,
// rowed vector<void*> erase 0x0031BD55; callers 0x003983D4 0x0039857D.

class GameLogic;
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A

class Rva0023D661
{
public:
	void rva0023D661(int val);
};

struct Rva002E36D5Node
{
	unsigned char m_pad[0x3C];
	Rva002E36D5Node *m_next3C;
};

void __cdecl Rva002E3714Unlink(Rva002E36D5Node *node);
void __cdecl operator delete(void *p);

struct Elem
{
	virtual void *V0(int val);
};

namespace _STL
{
template <class T> class allocator
{
};
template <typename T, typename A> class vector
{
public:
	T *m_begin;
	T *m_end;
	T *m_cap;
	T *erase(T *first, T *last);
};
}

class Rva00397E50
{
public:
	void rva00397E50();
private:
	char m_pad[0x80];
	_STL::vector<void *, _STL::allocator<void *> > m_vec;
};

void Rva00397E50::rva00397E50()
{
	_STL::vector<void *, _STL::allocator<void *> > *v = &m_vec;
	for (Elem **it = (Elem **)m_vec.m_begin; it != (Elem **)m_vec.m_end; ++it)
	{
		Elem *e = *it;
		if (e != 0)
		{
			Rva002E3714Unlink((Rva002E36D5Node *)(void *)e);
			((Rva0023D661 *)(void *)TheGameLogic)->rva0023D661((int)(void *)e);
			::operator delete(e->V0(0));
		}
	}
	v->erase(v->m_begin, v->m_end);
}
