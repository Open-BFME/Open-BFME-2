// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??0Rva003371B1@@QAE@ABV0@@Z @ 0x003371B1 (67B): copy ctor over 20-byte record
// with AsciiString at +0 via pinned StringBase<char> copy 0x365F0, flag byte
// at +4, and vector<BfmeStringRecord000331962> at +8 via rowed copy 0x33629E.
// Layout sized by retail accesses (add edi,8; lea ecx,[esi+8]) and by the
// 0x14-step vector loops in callers 0x337960/0x337749/0x337D21. Shape matches
// the 67B StringBase+vector copy at 0x000C0BEC in StringVectorRecordCopyBFME2.
#include <memory>
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
private:
    AsciiString m_str;
    unsigned char m_flag;
    _STL::vector<BfmeStringRecord000331962> m_vec;
};
Rva003371B1::Rva003371B1(const Rva003371B1 &other)
    : m_str(other.m_str), m_flag(other.m_flag), m_vec(other.m_vec)
{
}
template void _STL::_Construct<Rva003371B1, Rva003371B1>(Rva003371B1 *, const Rva003371B1 &);
