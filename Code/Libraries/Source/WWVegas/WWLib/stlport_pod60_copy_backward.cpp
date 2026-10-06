// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??$copy_backward@PAUBfmePod60@@PAU1@@_STL@@YAPAUBfmePod60@@PAU1@00@Z @0x005875BF 29B
// copy_backward for 60-byte POD: dispatches to rowed __copy_backward at
// 0x00587447 with tag plus null distance. Caller 0x00587E3D.
// Evidence: 5 pushes plus add esp 0x14 plus rowed callee.
#include <vector>
#include <algorithm>
struct BfmePod60 { int a[15]; };

template BfmePod60 *_STL::copy_backward<BfmePod60 *, BfmePod60 *>(BfmePod60 *, BfmePod60 *, BfmePod60 *);
