// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00418797@@QAE@ABVAsciiString@@PBV0@@Z @0x00418797 124B
// Ctor with two map<int void*> at +0/+0xc via rowed ctor 0x0033C432 plus AsciiString at +0x18 via rowed StringBase copy 0x000365F0 plus bytes at +0x1c/+0x1d. Nullable other gives defaults 1/0 else copy b1c then Rb_tree<int int> assigns 0x00418500 via IntIntTree cast then b1d. Returns this with ret 8.
// Evidence: callees rowed 0x0033C432 0x000365F0 0x00418500; caller 0x00418B10; sibling precedent Code/GameEngine/Source/GameClient/Rva00419669Ctor.cpp.
#include "ascii_string.h"

namespace _STL
{

template <class T>
struct less
{
};

template <class T>
class allocator
{
};

template <class K, class V>
struct pair
{
	K first;
	V second;
};

template <class P>
struct _Select1st
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	_Rb_tree &rva00418500(const _Rb_tree &x);
};

template <class K, class V, class C, class A>
class map
{
public:
	map();
	~map();
	char _pad[12];
};

typedef pair<const int, int> IntIntValue;
typedef _Select1st<IntIntValue> IntIntKeyOf;
typedef less<int> IntIntCompare;
typedef allocator<IntIntValue> IntIntAlloc;
typedef _Rb_tree<int, IntIntValue, IntIntKeyOf, IntIntCompare, IntIntAlloc> IntIntTree;

typedef pair<const int, void *> IntPtrValue;
typedef allocator<IntPtrValue> IntPtrAlloc;
typedef map<int, void *, less<int>, IntPtrAlloc> IntPtrMap;

}

class Rva00418797
{
public:
	Rva00418797(const AsciiString &name, const Rva00418797 *other);
private:
	_STL::IntPtrMap m_map1;
	_STL::IntPtrMap m_map2;
	AsciiString m_str;
	bool m_b1c;
	bool m_b1d;
};

Rva00418797::Rva00418797(const AsciiString &name, const Rva00418797 *other)
	: m_map1(), m_map2(), m_str(name)
{
	if (other == 0)
	{
		m_b1c = true;
		m_b1d = false;
	}
	else
	{
		m_b1c = other->m_b1c;
		((_STL::IntIntTree *)&m_map1)->rva00418500(*(_STL::IntIntTree *)&other->m_map1);
		((_STL::IntIntTree *)&m_map2)->rva00418500(*(_STL::IntIntTree *)&other->m_map2);
		m_b1d = other->m_b1d;
	}
}
