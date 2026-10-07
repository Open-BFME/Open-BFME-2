// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <string>
// Canonical default construction is supplied by retail7850.
namespace _STL { template <> basic_string<char>::basic_string(); }
#include <locale>

template class _STL::num_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;

// Keep the two independently rowed string-termination helpers emitted.
template void _STL::basic_string<char>::_M_terminate_string();
template void _STL::basic_string<char>::_M_terminate_string_aux(const _STL::__true_type &);
