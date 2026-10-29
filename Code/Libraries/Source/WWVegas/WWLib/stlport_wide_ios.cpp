// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <ios>

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_ios<unsigned short, char_traits<unsigned short> > & basic_ios<unsigned short, char_traits<unsigned short> >::copyfmt(basic_ios<unsigned short, char_traits<unsigned short> > const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> locale basic_ios<unsigned short, char_traits<unsigned short> >::imbue(locale const &); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void allocator<char>::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *allocator<char>::allocate(size_t, const void*);
}
template class _STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >;
