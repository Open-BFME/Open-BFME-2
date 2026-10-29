// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ?erase@?$list@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@_STL@@QAE?AU?$_List_iterator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@U?$_Nonconst_traits@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@2@U32@@Z
// retail 0x00424363, 42 bytes. list<basic_string<char>>::erase single-iterator
// via rowed basic_string dtor 0x0007FAB3 plus _free 0x00030830. Evidence:
// unlock lane; caller 0x004246E7 in 0x004246D7; unblocks 0x004246D7.
// ?pop_back@?$list@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@_STL@@QAEXXZ
// retail 0x004246D7, 23 bytes. list<basic_string<char>>::pop_back via rowed
// erase 0x00424363. Evidence: chain lane (calls 0x00424363 just landed);
// caller 0x00424982 in 0x0042481E; unblocks 0x0042481E.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
// codegen otherwise instantiates the min<int> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <string>

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> bool operator==<char, char_traits<char>, allocator<char> >(basic_string<char, char_traits<char>, allocator<char> > const &, basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// less<string>::operator() is the rowed body 0x00389117; _S_merge calls it.
namespace _STL { template <> bool less<basic_string<char, char_traits<char>, allocator<char> > >::operator()(basic_string<char, char_traits<char>, allocator<char> > const &, basic_string<char, char_traits<char>, allocator<char> > const &) const; }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
namespace _STL {
typedef _List_node<basic_string<char> > StringListNode;
template <> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<StringListNode *, StringListNode, allocator<StringListNode> >::deallocate(StringListNode *p, size_t n)
{ allocator<StringListNode>::deallocate(p, n); }
}

// The list constructor, destructor and splice, _S_sort, _S_merge, _S_unique, the
// node proxy swap, the _List_base constructor and destructor and _M_create_node
// have no retail row; this unit emits them for its explicit instantiation rather
// than leaning on w3d_dep.cpp's unrowed copies.
template class _STL::list<_STL::basic_string<char> >;
template bool _STL::equal_to<_STL::basic_string<char> >::operator()(const _STL::basic_string<char> &, const _STL::basic_string<char> &) const;
