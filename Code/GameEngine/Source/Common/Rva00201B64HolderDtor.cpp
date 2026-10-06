// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00201B64@@QAE@XZ, retail 0x00201B64, 108B.
// Holder dtor: deletes Owner heap objects held as ints in list<int>,
// erases nodes, then destroys list via rowed List_base dtor.
// Evidence: calls rowed Owner dtor E19E1 plus delete plus list erase.
#include <list>

class Rva0048C200Owner
{
public:
	~Rva0048C200Owner();
};

class Rva00201B64
{
public:
	Rva00201B64();
	~Rva00201B64();
private:
	_STL::list<int> m_list00;
};

Rva00201B64::Rva00201B64()
{
}

Rva00201B64::~Rva00201B64()
{
	for (_STL::list<int>::iterator it = m_list00.begin(); it != m_list00.end();)
	{
		int v = *it;
		if (v != 0)
		{
			Rva0048C200Owner *o = (Rva0048C200Owner *)v;
			*(void **)o = 0;
			delete o;
		}
		it = m_list00.erase(it);
	}
}
