// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$_Construct@UBfmePod88@@U1@@_STL@@YAXPAUBfmePod88@@ABU1@@Z @ 0x004E3706 (45B).
// Null-guarded placement copy over the 88-byte element whose real copy ctor
// is the rowed Rva004E3184 copy at 0x004E2F9F (twin-pinned as BfmePod88 copy).
// Same 45B shape as the rowed _Construct<AsciiString> at 0x0002C485.
// Callers are the rowed Pod88 uninitialized_copy at 0x004E3733 plus fill_n
// at 0x004E3759 plus push_back at 0x004E3BA1.
#include <memory>

struct BfmePod88 {
    BfmePod88(const BfmePod88 &other);
    char m_body[88];
};

template void _STL::_Construct<BfmePod88, BfmePod88>(BfmePod88 *, const BfmePod88 &);
