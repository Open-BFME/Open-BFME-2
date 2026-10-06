// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport's two-argument sort over a pointer range of 12-byte records ordered by
// the int at +0: sort (0x0051D868, 70B) and the family it instantiates,
// 0x0051C07D .. 0x0051D778. Target evidence: the introsort loop at 0x0051D778
// divides by 12 and calls the int median folded at 0x00331716 (rowed in
// stlport_int_algorithm_bodies.cpp); sort reaches the rest by its calls.
//
// The record is a STAND-IN: the image fixes its size, that it copies bitwise,
// and the int key at +0. Five bodies are shared with other instantiations and
// are pinned there, not rowed: the median, swap (0x004219CD, BfmeE12's) and the
// copy_backward chain (0x0051C94D, 0x000CA187, 0x000B6813). As in
// stlport_copy_backward_e12.cpp, the build uses the stock STLport headers: the
// bfmealloc shim force-inlines the copy_backward helpers, and retail keeps
// them out of line.

#include <algorithm>

struct BfmeE12Key { int k; int a; int b; };

inline bool operator<(const BfmeE12Key &x, const BfmeE12Key &y) { return x.k < y.k; }

template void _STL::sort<BfmeE12Key *>(BfmeE12Key *, BfmeE12Key *);
