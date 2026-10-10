// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport

#include <string>

// Native base cleanup is supplied by the independently verified B3C0 owner.
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }

namespace _STL
{
template <>
basic_string<char, char_traits<char>, allocator<char> >::~basic_string();

template <>
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(
        char*, size_t);
}

#include <locale>
// basic_string<char>::reserve is retail's 116-byte body at 0x0000C390, owned by
// stlport_narrow_string_reserve.cpp; this unit's header copy is not retail's and
// came before it in link order, so only declare its instantiation here.
namespace _STL { extern template void basic_string<char, char_traits<char>, allocator<char> >::reserve(size_t); }

// do_put(bool) and do_put(const void *) are owned by stlport_narrow_num_put_bool.cpp and
// stlport_narrow_num_put_voidptr.cpp; leave them declared so this unit emits neither (nor their getloc).
namespace _STL {
template <> ostreambuf_iterator<char, char_traits<char> >
num_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(
    ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, bool) const;
template <> ostreambuf_iterator<char, char_traits<char> >
num_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(
    ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, const void *) const;
}
template class _STL::num_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
