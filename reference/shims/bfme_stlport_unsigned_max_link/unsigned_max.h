// TU-scoped STLport 4.5.3 unsigned max view; donor inputs at BFME1
// 9cbfb551fe20dae985f91f2319d8997287b6a705. Same reference-returning
// comparison as stl/_algobase.h. The native outlined owner is
// stlport_narrow_istream.cpp at 0x00013740; consumers inline entirely.
#ifndef BFME_UNSIGNED_MAX_LINK_H
#define BFME_UNSIGNED_MAX_LINK_H
#include <stl/_algobase.h>
namespace _STL {
template <> __declspec(dllimport) __forceinline
const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#endif
