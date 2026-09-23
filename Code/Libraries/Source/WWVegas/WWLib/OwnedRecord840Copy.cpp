// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target copy and cleanup of an 840-byte owning record.
// Offsets and copy operations come from retail disassembly; record identity and
// payload meanings remain unclaimed. BFME1 PeerResponse is related donor context.
// Anonymous union alternatives preserve the observed overlapping copies.
#include <string>
#include <vector>
#include <stddef.h>

template <typename T> class StringBase {
    friend class AsciiString;
    StringBase(const StringBase &);
    ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
    void *m_data;
};
class AsciiString : private StringBase<char> {
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
};

struct BfmeOpaqueOwnedRecord840 {
    BfmeOpaqueOwnedRecord840();
    ~BfmeOpaqueOwnedRecord840();
    int unknown_00;
    std::string unknown_04;
    std::string unknown_10;
    std::string unknown_1c;
    std::wstring unknown_28;
    std::string unknown_34;
    std::string unknown_40;
    std::wstring unknown_4c;
    std::string unknown_58;
    std::string unknown_64;
    std::string unknown_70;
    std::string unknown_7c;
    std::string unknown_88[8];
    std::string unknown_e8;
    std::string unknown_f4;
    _STL::vector<AsciiString> unknown_100;
    union {
        struct { int value; } payload_word0;
        struct { int value; } payload_word1;
        struct { int words[8]; } payload_32;
        struct { int first; int second; } payload_8a;
        struct { int value; } payload_4;
        struct { int words[3]; } payload_12;
        struct { int first; int second; } payload_8b;
        struct { int words[143]; } payload_572;
        struct { int words[79]; } payload_316;
        struct { int words[48]; } payload_192;
    };
};

typedef char Record840Extent[sizeof(BfmeOpaqueOwnedRecord840) == 840 ? 1 : -1];
typedef char Record840Alignment[__alignof(BfmeOpaqueOwnedRecord840) == 4 ? 1 : -1];
typedef char Record840WideStringOffset[offsetof(BfmeOpaqueOwnedRecord840, unknown_28) == 0x28 ? 1 : -1];
typedef char Record840SecondWideOffset[offsetof(BfmeOpaqueOwnedRecord840, unknown_4c) == 0x4c ? 1 : -1];
typedef char Record840ArrayOffset[offsetof(BfmeOpaqueOwnedRecord840, unknown_88) == 0x88 ? 1 : -1];
typedef char Record840StringE8Offset[offsetof(BfmeOpaqueOwnedRecord840, unknown_e8) == 0xe8 ? 1 : -1];
typedef char Record840StringF4Offset[offsetof(BfmeOpaqueOwnedRecord840, unknown_f4) == 0xf4 ? 1 : -1];
typedef char Record840VectorOffset[offsetof(BfmeOpaqueOwnedRecord840, unknown_100) == 0x100 ? 1 : -1];
typedef char Record840PayloadStart[offsetof(BfmeOpaqueOwnedRecord840, payload_word0) == 0x10c ? 1 : -1];

template void _STL::_Construct<BfmeOpaqueOwnedRecord840, BfmeOpaqueOwnedRecord840>(
    BfmeOpaqueOwnedRecord840 *, const BfmeOpaqueOwnedRecord840 &);

BfmeOpaqueOwnedRecord840::~BfmeOpaqueOwnedRecord840() {}
