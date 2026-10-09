// cl: /O1 /G7 /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <stl/_algobase.h>

// BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d ThingFactory.cpp, O1/G7/MD.
// Retail 511CB4..511CB9 tail-calls the actual 32B four-byte fill at 7E48F.
// void* is a compatible storage exemplar; original payload, name and reachability are unknown.
void **rva00511CB4FillPointers(void **first, unsigned count, void *const &value)
{
    return _STL::fill_n(first, count, value);
}
