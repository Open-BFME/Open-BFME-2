// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva005F2406@Rva005F2406@@QAEXH@Z @0x005F2406 51B insert int into set at +0x10 then broadcast
// If set<int>::insert 0x000BC15D reports new key, forEach 0x005F224E over list at +0
// with forwarder 0x001FF3A9 and this plus the key. Evidence: callees rowed, caller 0x005E4E12.
#include <set>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Node factory and allocator paths of the set<int> insert, inline
// (dllimport+forceinline) so this TU emits no losing COMDAT copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<int> *allocator<_Rb_tree_node<int> >::allocate(size_t n, const void *) const
{ return n != 0 ? reinterpret_cast<_Rb_tree_node<int> *>(__sgi_alloc::allocate(n * sizeof(_Rb_tree_node<int>))) : 0; }
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<int> *_STLP_alloc_proxy<_Rb_tree_node<int> *, _Rb_tree_node<int>, allocator<_Rb_tree_node<int> > >::allocate(size_t n)
{ return __stl_alloc_rebind(static_cast<allocator<_Rb_tree_node<int> >&>(*this), (_Rb_tree_node<int> *)0).allocate(n, 0); }
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<int> *_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_M_create_node(const int &__x)
{
  _Rb_tree_node<int> *__tmp = this->_M_header.allocate(1);
  _Construct(&__tmp->_M_value_field, __x);
  return __tmp;
}
}

namespace _STL {
template <> _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::iterator
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, const int &, _Rb_tree_node_base *);
}

#include "../../Include/Common/Rva005F224EListener.h"

class Rva005F224EList
{
public:
	void forEach(void (Rva005F224EListener::*notify)(void *, int), void *arg, int value);
private:
	Rva005F224EListener **m_begin;
	Rva005F224EListener **m_end;
	Rva005F224EListener **m_capacity;
	unsigned int m_index;
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
};

class Rva005F2406
{
public:
	void rva005F2406(int val);
private:
	Rva005F224EList m_list00;
	_STL::set<int> m_set10;
};

void Rva005F2406::rva005F2406(int val)
{
	if (m_set10.insert(val).second)
		m_list00.forEach((void (Rva005F224EListener::*)(void *, int))&Rva001FF3A9::rva001FF3A9, this, val);
}
