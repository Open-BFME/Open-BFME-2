// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

// Retail's basic_ios<char>::widen is the generic ctype<char>::widen dispatch (as in
// stlport_basic_ios_init.cpp), not STLport's identity specialization.
#define _STLP_NO_METHOD_SPECIALIZATION
#include <ios>

// Retail's generic-widening init is owned by stlport_basic_ios_init.cpp.
// Leave this specialization declared so this unit does not emit a different copy.
namespace _STL {
template <> void basic_ios<char, char_traits<char> >::init(
    basic_streambuf<char, char_traits<char> > *);
}


#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
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
namespace _STL { template <> basic_ios<char, char_traits<char> > &basic_ios<char, char_traits<char> >::copyfmt(const basic_ios<char, char_traits<char> > &); }
template class _STL::basic_ios<char, _STL::char_traits<char> >;
