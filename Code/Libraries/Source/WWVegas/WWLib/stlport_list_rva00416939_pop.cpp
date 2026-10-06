// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// list pop_front @0x00416939, 22B; masked twin of BfmePod12 pop_front @0x004907AA.
#include <list>
struct Rva00416939Pod { int a[3]; };
inline bool operator==(const Rva00416939Pod &x, const Rva00416939Pod &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const Rva00416939Pod &x, const Rva00416939Pod &y) { return x.a[0] < y.a[0]; }
template void _STL::list<Rva00416939Pod>::pop_front();
