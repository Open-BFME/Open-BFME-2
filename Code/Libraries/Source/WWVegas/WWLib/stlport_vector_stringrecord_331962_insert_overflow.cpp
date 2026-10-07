// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@UBfmeStringRecord000331962@@V?$allocator@UBfmeStringRecord000331962@@@_STL@@@_STL@@IAEXPAUBfmeStringRecord000331962@@ABU3@ABU__false_type@2@I_N@Z, retail 0x003323F1, 183 bytes.
// Vector overflow via rowed allocate pin 0x395928 plus workers 0x331BAC 0x331B6A plus Construct pin 0x331B3D plus Clear pin 0xC05EC.
// Evidence: caller push_back at 0x332568; same 183B shape as siblings; /G7 for retail imul.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord000331962 {
    unsigned int word;
    AsciiString text;
    unsigned char flag;
    BfmeStringRecord000331962();
    ~BfmeStringRecord000331962();
    BfmeStringRecord000331962(const BfmeStringRecord000331962 &o) : word(o.word), text(o.text), flag(o.flag) {}
};
#include <memory>
namespace _STL {
template <> void _Construct<BfmeStringRecord000331962, BfmeStringRecord000331962>(BfmeStringRecord000331962 *, const BfmeStringRecord000331962 &);
}
#include <vector>
template void _STL::vector<BfmeStringRecord000331962>::_M_insert_overflow(BfmeStringRecord000331962 *, const BfmeStringRecord000331962 &, const _STL::__false_type &, unsigned int, bool);
