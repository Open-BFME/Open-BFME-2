// cl: /EHs /MD
//
// ??0Rva005344C0@@QAE@ABU0@@Z @0x00534676 (29B).
// Pair copy: copy first int then copy-construct second via rowed Rb_tree copy
// 0x00534581 (dup_00534581 object-symbol). Evidence: gap between erase
// 0x00534641 and clear 0x00534693 in RvaTreeValueEraseFamily.cpp with same
// /O1 /EHs /MD; callee rowed; caller 0x005346F5; returns this (MSVC ctor).
namespace _STL
{
template <class T> class allocator;
template <class T1, class T2> struct pair { ~pair(); };
template <class T> struct less;
template <class P> struct _Select1st;
template <class K, class V, class S, class C, class A> class _Rb_tree
{
public:
	_Rb_tree(const _Rb_tree &o);
};
}

typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > IntTree00534581;

struct Rva005344C0
{
	int m_first;
	IntTree00534581 m_second;
	Rva005344C0(const Rva005344C0 &o);
	Rva005344C0(const int *pFirst, const IntTree00534581 &second);
};

Rva005344C0::Rva005344C0(const Rva005344C0 &o) : m_first(o.m_first), m_second(o.m_second)
{
}

// ??0Rva005344C0@@QAE@PBHABVIntTree00534581@@@Z @0x005346BC (29B).
// Two-arg pair build: copy int from *pFirst then copy-construct second via
// rowed Rb_tree copy 0x00534581. Evidence: unlock between clear 0x00534693
// and construct 0x005346D9 same TU/flags; callee rowed/pinned; caller
// 0x00534A63; ret 8; returns this.
Rva005344C0::Rva005344C0(const int *pFirst, const IntTree00534581 &second) : m_first(*pFirst), m_second(second)
{
}

// ?Rva005346D9Construct@@YAXPAURva005344C0@@ABU1@@Z @0x005346D9 (45B).
// Conditional copy-construct via placement new for caller 0x00534757.
// Evidence: chain from 0x00534676 which this session landed; same TU/flags.
#include <new>

void __cdecl Rva005346D9Construct(Rva005344C0 *p, const Rva005344C0 &v)
{
	new (p) Rva005344C0(v);
}
