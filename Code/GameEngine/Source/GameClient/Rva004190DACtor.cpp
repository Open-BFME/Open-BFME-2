// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva004190DA@@QAE@ABVAsciiString@@PBV0@@Z retail 0x004190DA 104B unlock ctor with map+flags
// Evidence: calls rowed StringBase copy 0x000365F0 via AsciiString member; rowed map<int void*> ctor 0x0033C432; rowed BitFlags<11> default 0x003B31AD; rowed Rb_tree copy 0x00418E78; tail copies map+flags or sets all bits; caller 0x0041942F.
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
	_Rb_tree &rva00418e78(const _Rb_tree &x);
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

template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags();
	unsigned int m_word;
};

class Rva004190DA
{
public:
	Rva004190DA(const AsciiString &name, const Rva004190DA *other);
private:
	AsciiString m_name;
	_STL::IntPtrMap m_map;
	BitFlags<11> m_flags;
};

Rva004190DA::Rva004190DA(const AsciiString &name, const Rva004190DA *other)
	: m_name(name), m_map(), m_flags()
{
	if (other != 0)
	{
		((_STL::IntIntTree *)&m_map)->rva00418e78(*(_STL::IntIntTree *)&other->m_map);
		m_flags.m_word = other->m_flags.m_word;
	}
	else
	{
		m_flags.m_word = ~m_flags.m_word;
	}
}
