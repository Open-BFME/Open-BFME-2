// ?insert@?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@QAEPAUBfmeE8@@PAU3@ABU3@@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct BfmeE8 {
    float x, y;
    BfmeE8() {}
    BfmeE8(const BfmeE8& value): x(value.x), y(value.y) {}
};
BfmeE8* insertForTrial(_STL::vector<BfmeE8>& values, BfmeE8* position, const BfmeE8& value)
{
    return values.insert(position, value);
}
