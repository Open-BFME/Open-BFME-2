// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy narrow basic_string helper at 0x00079A6E (38B); stride-12
// copy loop through the rowed _Construct at 0x00079A41. Same recipe as
// stlport_uninitialized_copy.cpp: vector copy ctor instantiation emits the
// __uninitialized_copy worker out-of-line through the declared-only
// _Construct specialization below.
#include <memory>
#include <vector>
#include <string>

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > NarrowStr12;

namespace _STL {
template <> void _Construct<NarrowStr12, NarrowStr12>(NarrowStr12 *, const NarrowStr12 &);
}

template _STL::vector<NarrowStr12, _STL::allocator<NarrowStr12> >::vector(const _STL::vector<NarrowStr12, _STL::allocator<NarrowStr12> > &);
