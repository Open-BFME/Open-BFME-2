// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$swap@UBfmeE12@@@_STL@@YAXAAUBfmeE12@@0@Z at retail 0x004219CD 39 bytes.
// ??$?MUBfmeE12@@@_STL@@YA_NABU?$_Deque_iterator_base@UBfmeE12@@@0@0@Z at retail 0x004219B0 29 bytes.
// Donor vendor/stlport/stl/_algobase.h swap and vendor/stlport/stl/_deque.h operator< base;
// callers 0x0051C86D 0x005877D6 0x005D5CF4 0x00422270 and 0x0042224B 0x0054A295 0x0054BDC0.
// BfmeE12 names only the 12-byte element size.
#include <deque>
struct BfmeE12 { float x, y, z; };
template bool _STL::operator< <BfmeE12>(const _STL::_Deque_iterator_base<BfmeE12> &, const _STL::_Deque_iterator_base<BfmeE12> &);
template void _STL::swap<BfmeE12>(BfmeE12&, BfmeE12&);
