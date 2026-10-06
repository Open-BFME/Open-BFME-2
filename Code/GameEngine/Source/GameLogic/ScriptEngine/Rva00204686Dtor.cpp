// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ??1Rva00204686@@QAE@XZ @0x00204686 53B: non-virtual dtor over pair at +0 and
// AsciiString at +8. Evidence: rowed _STL::pair<const AsciiString,AsciiString>
// dtor 0x0002C0C0; rowed StringBase releaseBuffer 0x00036410; callers 0x00204AF9
// 0x00206723 0x00208E41 0x00208E4D make 0x00204AF6/28 and 0x00206706/53 ready.

#include "ascii_string.h"


namespace _STL
{
template <typename T1, typename T2>
struct pair
{
    ~pair();
    T1 first;
    T2 second;
};
}

struct Rva00204686
{
    _STL::pair<const AsciiString, AsciiString> m_pair;
    AsciiString m_entry;
    ~Rva00204686();
};

Rva00204686::~Rva00204686() {}
