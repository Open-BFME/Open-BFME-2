// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00419669@@QAE@ABVAsciiString@@PBV0@@Z retail 0x00419669 143B unlock ctor with map+float8
// Evidence: calls rowed StringBase copy 0x000365F0 via AsciiString member; rowed map<int void*> ctor 0x0033C432; rowed Rb_tree<int int> copy 0x00418500; default 0x32/1/zero8/2 else copy map+floats; caller 0x004199EC.
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

class Rva00419669
{
public:
	Rva00419669(const AsciiString &name, const Rva00419669 *other);
private:
	AsciiString m_name;
	_STL::IntPtrMap m_map;
	int m_unk10;
	float m_arr14[8];
	bool m_flag34;
	int m_unk38;
};

Rva00419669::Rva00419669(const AsciiString &name, const Rva00419669 *other)
	: m_name(name), m_map(), m_unk38(2)
{
	if (other == 0)
	{
		m_flag34 = true;
		m_unk10 = 0x32;
		for (int i = 0; i < 8; ++i)
			m_arr14[i] = 0;
	}
	else
	{
		m_flag34 = other->m_flag34;
		m_unk10 = other->m_unk10;
		for (int i = 0; i < 8; ++i)
			m_arr14[i] = other->m_arr14[i];
		((_STL::IntIntTree *)&m_map)->rva00418500(*(_STL::IntIntTree *)&other->m_map);
	}
}
