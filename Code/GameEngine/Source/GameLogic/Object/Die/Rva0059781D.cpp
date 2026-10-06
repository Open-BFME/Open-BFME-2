// cl: /GX-
// ?rva0059781D@Rva0059781D@@QAEXXZ @0x0059781D 208B: prune two voidptr vectors at +0x24/+0x30 erasing null or checked via rowed findObjectByID 0x00049DC5 and 0x004E9378 with slot0+delete then 0x0055ADBA on flag; caller 0x00597FC5
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	char m_pad00[0x438];
	unsigned char m_438;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	_Tp *erase(_Tp *pos);
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_end;
};

}

class Elem
{
public:
	virtual void *slot0(int x);
	char m_pad04[4];
	ObjectID m_id08;
	char m_pad0c[0x20];
	unsigned char m_2c;
	char m_pad2d[7];
	unsigned char m_34;
};

class Rva004E9378
{
public:
	bool rva004E9378();
};

class Rva00506FE9Hit
{
public:
	void rva0055ADBA(void *p);
};

void __cdecl operator delete(void *p);

class Rva0059781D
{
public:
	void rva0059781D();
private:
	char m_pad00[0x14];
	void *m_14;
	_STL::vector<void *, _STL::allocator<void *> > m_vec18;
	_STL::vector<void *, _STL::allocator<void *> > m_vec24;
	_STL::vector<void *, _STL::allocator<void *> > m_vec30;
};

void Rva0059781D::rva0059781D()
{
	void **it = m_vec24.m_start;
	while (it != m_vec24.m_finish)
	{
		Elem *e = (Elem *)*it;
		Object *obj = TheGameLogic->findObjectByID(e->m_id08);
		if (obj != 0)
		{
			if (!((Rva004E9378 *)e)->rva004E9378())
			{
				++it;
				continue;
			}
		}
		if (e->m_34 != 0)
		{
			((Rva00506FE9Hit *)e)->rva0055ADBA(m_14);
		}
		void *p = *it;
		void *q = 0;
		if (p != 0)
		{
			q = ((Elem *)p)->slot0(0);
		}
		::operator delete(q);
		it = m_vec24.erase(it);
	}
	void **it2 = m_vec30.m_start;
	while (it2 != m_vec30.m_finish)
	{
		Elem *e = (Elem *)*it2;
		Object *obj = TheGameLogic->findObjectByID(e->m_id08);
		if (obj != 0)
		{
			if ((obj->m_438 & 1) == 0)
			{
				if (!((Rva004E9378 *)e)->rva004E9378())
				{
					++it2;
					continue;
				}
			}
		}
		if (e->m_2c != 0)
		{
			((Rva00506FE9Hit *)e)->rva0055ADBA(m_14);
		}
		void *p = *it2;
		void *q = 0;
		if (p != 0)
		{
			q = ((Elem *)p)->slot0(0);
		}
		::operator delete(q);
		it2 = m_vec30.erase(it2);
	}
}
