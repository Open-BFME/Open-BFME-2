// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target copy and cleanup of the 840-byte PeerResponse record.
// Offsets and copy operations come from retail disassembly; payload meanings
// remain unclaimed. Identity (target): the matched PeerThread units construct
// and destroy their local PeerResponse through the REL32 calls that land on
// 0x00389F77 / 0x0038A063, and GameSpyPeerMessageQueue's response queue holds
// these 840-byte records. Name carried from the ZH/BFME1 PeerResponse donor.
// Anonymous union alternatives preserve the observed overlapping copies.
#include <string>
#include <vector>
#include <stddef.h>

#include "ascii_string.h"

struct PeerResponse {
    PeerResponse();
    ~PeerResponse();
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

typedef char Record840Extent[sizeof(PeerResponse) == 840 ? 1 : -1];
typedef char Record840Alignment[__alignof(PeerResponse) == 4 ? 1 : -1];
typedef char Record840WideStringOffset[offsetof(PeerResponse, unknown_28) == 0x28 ? 1 : -1];
typedef char Record840SecondWideOffset[offsetof(PeerResponse, unknown_4c) == 0x4c ? 1 : -1];
typedef char Record840ArrayOffset[offsetof(PeerResponse, unknown_88) == 0x88 ? 1 : -1];
typedef char Record840StringE8Offset[offsetof(PeerResponse, unknown_e8) == 0xe8 ? 1 : -1];
typedef char Record840StringF4Offset[offsetof(PeerResponse, unknown_f4) == 0xf4 ? 1 : -1];
typedef char Record840VectorOffset[offsetof(PeerResponse, unknown_100) == 0x100 ? 1 : -1];
typedef char Record840PayloadStart[offsetof(PeerResponse, payload_word0) == 0x10c ? 1 : -1];

template void _STL::_Construct<PeerResponse, PeerResponse>(
    PeerResponse *, const PeerResponse &);

PeerResponse::PeerResponse() {}

PeerResponse::~PeerResponse() {}
