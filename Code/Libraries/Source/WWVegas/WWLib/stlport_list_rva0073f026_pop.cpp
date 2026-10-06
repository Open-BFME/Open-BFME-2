// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// list pop_front @0x0073F026, 22B; masked twin of BfmePod12 pop_front @0x004907AA.
#include <list>
struct Rva0073F026Pod { int a[3]; };
inline bool operator==(const Rva0073F026Pod &x, const Rva0073F026Pod &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const Rva0073F026Pod &x, const Rva0073F026Pod &y) { return x.a[0] < y.a[0]; }
template void _STL::list<Rva0073F026Pod>::pop_front();
