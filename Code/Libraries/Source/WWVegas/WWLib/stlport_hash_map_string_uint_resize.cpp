// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_HASHTABLE_NEW_NODE_NOFORCEINLINE /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable
// stlport46
//
// hashtable<string, unsigned int>::resize at retail 0x0060CD36 (194B).
// String-keyed rehash: old bucket count from +4/+8, _M_next_size growth,
// fresh vector<void*> then per-node __stl_string_hash div new_n rechain,
// swap and free. Callers 0x0060D1BD (insert_unique shape); neighbours
// 0x0060CD16 (string bkt_num) and 0x0060CFFF (_Construct pair<string,I>).

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// vector<void*> members kept from this unit's link copies, moved beside <vector> so
// they precede every use. Import-inline: these members are inlined at every use here,
// and this unit's out-of-line copies (referenced from .debug$F alone) are not the ones
// the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL {
// The allocator is stateless; only the stored pointers need exchanging.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}

namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
#include <string>
#include <hash_map>

// The native string/unsigned hashtable calls its distinct copy owner at60CFFF.
// The standard _Construct spelling is already owned by the tree copy at38A5A4.
void StringUnsignedPairCopyAtRva0060CFFF(void *, const void *);
namespace _STL {
typedef pair<const string, unsigned int> StringUnsignedValue;
template <> _Hashtable_node<StringUnsignedValue> *
hashtable<StringUnsignedValue, string, hash<string>,
    _Select1st<StringUnsignedValue>, equal_to<string>,
    allocator<StringUnsignedValue> >::_M_new_node(const value_type &source)
{
    _Node *node = _M_num_elements.allocate(1);
    node->_M_next = 0;
    ::StringUnsignedPairCopyAtRva0060CFFF(&node->_M_val, &source);
    return node;
}
}

// Bind to the kept retail copy instead of emitting this unit's own.
// Bind to the kept retail copy instead of emitting this unit's own.
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$?8DV?$char_traits@D@_STL@@V?$allocator@D@1@@_STL@@YA_NABV?$basic_string@DV?$char_traits:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool operator==<char,char_traits<char>,allocator<char> >(basic_string<char,char_traits<char>,allocator<char> > const &,basic_string<char,char_traits<char>,allocator<char> > const &); }
// Suppress this TU's non-retail copy of ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> >::basic_string(basic_string<char,char_traits<char>,allocator<char> > const &); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }

template class _STL::hash_map<_STL::string, unsigned int,
	_STL::hash<_STL::string>, _STL::equal_to<_STL::string>,
	_STL::allocator<_STL::pair<const _STL::string, unsigned int> > >;
