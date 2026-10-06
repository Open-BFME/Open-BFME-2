// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$_Construct@V?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@V12@@_STL@@YAXPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@0@ABV10@@Z
// @ 0x0032B598 (45B).  STLport placement-copy for a vector<BfmeE8> element:
// null-guarded placement new over one element, delegating out-of-line to the
// rowed vector<BfmeE8> copy ctor 0x004334D7.  Called per element by the
// 0xC-stride vector walkers 0x0032B5C5 / 0x0032B5EB / 0x0032E842 / 0x0032EA3F.
// Same 45B EH shape as the other _Construct<T,T> rows; the vendored header
// emits the EH state before the null test, which the hand-written
// `if (p) new (p) T(v)` free-function attempt banked one byte away.
#include <memory>
#include <vector>

struct BfmeE8 { int a, b; };

typedef _STL::vector<BfmeE8> ConstructE8Vec;

template void _STL::_Construct<ConstructE8Vec, ConstructE8Vec>(ConstructE8Vec *, const ConstructE8Vec &);
