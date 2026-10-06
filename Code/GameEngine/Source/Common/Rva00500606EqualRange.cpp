// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <map>

extern unsigned int g_Va00E04544;

typedef _STL::map<int, int> Rva00500606IntMap;
typedef _STL::pair<const int, int> Rva00500606IntValue;
typedef _STL::_Rb_tree<int, Rva00500606IntValue, _STL::_Select1st<Rva00500606IntValue>,
	_STL::less<int>, _STL::allocator<Rva00500606IntValue> > Rva00500606IntTree;
typedef _STL::pair<Rva00500606IntTree::iterator, Rva00500606IntTree::iterator> Rva00500606NativeRange;

class Rva00500606Range
{
public:
	Rva00500606Range() {}
	Rva00500606Range(const Rva00500606Range &other)
		: m_first(other.m_first), m_second(other.m_second)
	{
	}
	void *m_first;
	void *m_second;
};

class Rva0050055D
{
	public:
	Rva0050055D(const Rva0050055D &other);
	char m_data[24];
};

class Rva002B82D5
{
	public:
	~Rva002B82D5();
	char m_data[24];
};

class Rva00500606Cleanup
{
	public:
	Rva00500606Cleanup(Rva0050055D *temporary) : m_temporary(temporary) {}
	~Rva00500606Cleanup()
	{
		((Rva002B82D5 *)m_temporary)->~Rva002B82D5();
	}
	private:
	Rva0050055D *m_temporary;
};

// The call sequence identifies the map lookup and temporary operations, but
// not the owner of either map or the semantic meaning of the returned range.
// Keep the target function address-derived and describe only its observed ABI.
Rva00500606Range __cdecl rva00500606(int key)
{
	Rva00500606IntMap *map = (Rva00500606IntMap *)&g_Va00E04544;
	const int *mapped = &map->find(key)->second;
	Rva0050055D temporary(*(const Rva0050055D *)mapped);
	Rva00500606Cleanup cleanup(&temporary);
	const Rva00500606NativeRange &nativeRange = ((Rva00500606IntTree *)&temporary)->equal_range(1);
	return *(const Rva00500606Range *)&nativeRange;
}
