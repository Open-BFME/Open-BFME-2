// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <string>
// Canonical default construction is supplied by retail7850.
namespace _STL { template <> basic_string<char>::basic_string(); }
#include <locale>
// basic_string<char>::reserve is retail's 116-byte body at 0x0000C390, owned by
// stlport_narrow_string_reserve.cpp; this unit's header copy is not retail's and
// came before it in link order, so only declare its instantiation here.
namespace _STL { extern template void basic_string<char, char_traits<char>, allocator<char> >::reserve(size_t); }
// Use the complete retail scanner at 0x00007C90 rather than a competing
// generic header implementation.
namespace _STL {
template <> int _M_get_base_or_zero<istreambuf_iterator<char, char_traits<char> >, char>(
    istreambuf_iterator<char, char_traits<char> > &,
    istreambuf_iterator<char, char_traits<char> > &, ios_base &, char *);
}

template class _STL::num_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;

// Keep the two independently rowed string-termination helpers emitted.
template void _STL::basic_string<char>::_M_terminate_string();
template void _STL::basic_string<char>::_M_terminate_string_aux(const _STL::__true_type &);
