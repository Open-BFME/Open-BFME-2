// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// The same map<int,int> instantiation as stlport_map_int_int.cpp, built for
// SIZE rather than speed. Retail is not uniform about this: the bodies that
// unit already holds are speed-optimised, but _M_erase is not - it pushes the
// child straight from memory with `ff 76 0c` and cleans with a one-byte pop,
// where the speed build loads into eax and cleans with `add esp, 4`.
//
// Rather than change that unit's flags, which sixteen landed rows depend on,
// this is a second unit with identical defines and /O1, claiming only the
// bodies the size build reproduces.
// stlport

#include <map>

template class _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >;
