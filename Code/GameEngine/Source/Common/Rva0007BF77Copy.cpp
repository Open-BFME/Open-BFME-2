// cl: /MD
// stlport46
// ?Rva0007BF77Copy@@YAPAURegion2D@@PAU1@00ABU__false_type@_STL@@H@Z @0x0007BF77 47B
// Counted copy of 16-byte Region2D records via rowed copy ctor 0x0004254E.
// Evidence: stride 0x10 sar 4 and direct thiscall to Region2D copy; caller 0x0007BF5A wrapper forwards first last result tag 0.
#include "../../../Libraries/Include/Lib/Region2D.h"
#define _STLP_USE_STATIC_LIB 1
#include <memory>  // _STL::__false_type
struct Region2D * Rva0007BF77Copy(struct Region2D *first, struct Region2D *last, struct Region2D *result, const _STL::__false_type &tag1, int tag2)
{
    int count = (int)(last - first);
    if (count <= 0)
        return result;
    int remaining = count;
    do {
        result->Region2D::Region2D(*first);
        ++first;
        ++result;
        --remaining;
    } while (remaining != 0);
    return result;
}
