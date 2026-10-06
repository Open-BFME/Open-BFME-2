// ?rva0021E9D8@Rva0021E9D8@@QAEHIABVAsciiString@@00@Z
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0021E9D8@Rva0021E9D8@@QAEHIABVAsciiString@@00@Z @0x0021E9D8 129B: caller 0x0021EA6B and vector/helper operations at +0x15C; class identity unproven.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"

struct BfmeStringRecord002199C8 {
    unsigned char strings[12];
    unsigned int word;
    BfmeStringRecord002199C8(unsigned int, const AsciiString &, const AsciiString &, const AsciiString &);
};

class Rva0021A0C2 : public BfmeStringRecord002199C8 {
public:
    __forceinline Rva0021A0C2(unsigned int w, const AsciiString &a, const AsciiString &b, const AsciiString &c)
        : BfmeStringRecord002199C8(w, a, b, c) {}
    ~Rva0021A0C2();
};

struct CreateAHeroBlingEntry {
    unsigned char pad[12];
    int blingId;
};
CreateAHeroBlingEntry *rva0021D120(CreateAHeroBlingEntry *, CreateAHeroBlingEntry *, const AsciiString &);

namespace _STL {
template <> void _Construct<BfmeStringRecord002199C8, BfmeStringRecord002199C8>(
    BfmeStringRecord002199C8 *, const BfmeStringRecord002199C8 &);
}

class Rva0021E9D8 {
    unsigned char pad[0x15c];
    _STL::vector<BfmeStringRecord002199C8> records;
public:
    int rva0021E9D8(unsigned int, const AsciiString &, const AsciiString &, const AsciiString &);
};

int Rva0021E9D8::rva0021E9D8(unsigned int word, const AsciiString &a, const AsciiString &b, const AsciiString &c)
{
    int count = (int)((char *)records.end() - (char *)records.begin());
    count >>= 4;
    CreateAHeroBlingEntry *found = rva0021D120(records.begin(), records.end(), a);
    if (found == records.end()) {
        Rva0021A0C2 record(word, a, b, c);
        records.push_back(record);
    } else {
        count = (int)((char *)found - (char *)records.begin());
        count >>= 4;
    }
    return count;
}
