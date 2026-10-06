// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva000BC758Find@@YAPAV?$StringBase@D@@PAV1@0ABV1@H@Z @0x000BC758 172B via STL find Duff 4x
// Evidence: unrolled 4x compare loop with trip_count (last-first)>>2 and dec-chain tail;
// callee row ?compare@?$StringBase@D@@QBEHABV1@@Z @0x000069D6; callers 0x000BD22F (dispatch).
#include "string_base.h"

StringBase<char> *Rva000BC758Find(
    StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val, int dummy)
{
    (void)dummy;
    int trip = (last - first) >> 2;
    for (; trip > 0; --trip) {
        if (first->compare(val) == 0)
            return first;
        ++first;
        if (first->compare(val) == 0)
            return first;
        ++first;
        if (first->compare(val) == 0)
            return first;
        ++first;
        if (first->compare(val) == 0)
            return first;
        ++first;
    }
    switch (last - first) {
    case 3:
        if (first->compare(val) == 0)
            return first;
        ++first;
    case 2:
        if (first->compare(val) == 0)
            return first;
        ++first;
    case 1:
        if (first->compare(val) == 0)
            return first;
        ++first;
    case 0:
    default:
        return last;
    }
}

StringBase<char> *Rva000BD22FFind(
    StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val)
{
    char dummy;
    return Rva000BC758Find(first, last, val, (int)&dummy);
}
