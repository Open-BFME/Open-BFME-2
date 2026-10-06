// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_MEMBER_TEMPLATES /Ireference/shims/bfmealloc
// stlport
// ?reserve@?$vector@URva00390729Element@@V?$allocator@URva00390729Element@@@_STL@@@_STL@@QAEXI@Z @0x00390729 125B. Identity: vector reserve with 12-byte stride; start/finish/end at +0/+4/+8; capacity check via idiv 0xC; empty path via allocator 0x395928; grow path via helper 0xE016A; free via 0x30830.
// Evidence: callers 0xE0B3D/0x3909AE/0x48C487; callees rowed/pinned in packet; neighbours 0x3901C9/0x3907A6; same 125B shape as rowed BfmeE12 reserve 0x3B0224.
#include <vector>

// Address-derived codegen view; only the 12-byte stride is witnessed.
struct Rva00390729Element { int opaque[3]; };

template void _STL::vector<Rva00390729Element, _STL::allocator<Rva00390729Element> >::reserve(unsigned int);
