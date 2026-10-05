// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport partial_sort over the 20-byte Rva003371B1 records (AsciiString at
// +0, flag byte at +4, vector<BfmeStringRecord000331962> at +8), ordered by
// StringBase<char>::compare of the strings at +0 (less-than). Root partial_sort
// 0x00337C55; bodies are accepted only where byte-equal by the REL32 graph.
// Records are copied by the rowed copy constructor 0x003371B1, assigned by the
// body rowed at 0x003372EC (pinned as the assignment) and destroyed by the
// rowed destructor 0x003372B7. Comparator name is address-derived.
#include <algorithm>
#include <vector>
#include "ascii_string.h"

struct BfmeStringRecord000331962 {
    unsigned int word;
    AsciiString text;
    unsigned char flag;
    ~BfmeStringRecord000331962();
};

class Rva003371B1 {
public:
    Rva003371B1(const Rva003371B1 &other);
    Rva003371B1 &operator=(const Rva003371B1 &other);
    ~Rva003371B1();
    AsciiString m_str;
    unsigned char m_flag;
    _STL::vector<BfmeStringRecord000331962> m_vec;
};

struct Rva00337C55Less
{
    bool operator()(const Rva003371B1 &a, const Rva003371B1 &b) const
    {
        return ((const StringBase<char> &)a.m_str).compare((const StringBase<char> &)b.m_str) < 0;
    }
};

template void _STL::partial_sort<Rva003371B1 *, Rva00337C55Less>(Rva003371B1 *, Rva003371B1 *, Rva003371B1 *, Rva00337C55Less);
