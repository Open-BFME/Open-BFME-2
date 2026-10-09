// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??4BfmeRecord000B43E5@@QAEAAU0@ABU0@@Z, retail 0x000B43E5 (47 bytes, RET 4).
// Record assignment: three dwords (+0x00/+0x04/+0x08) and one byte (+0x0C) copied inline, then
// the AsciiString at +0x10 through StringBase<char>::set 0x000366F0 (rowed); returns this.
// Layout read from the retail body; application name and scalar meanings are unknown.
#include "ascii_string.h"

struct BfmeRecord000B43E5 {
    unsigned int word0; unsigned int word1; unsigned int word2; char flag; AsciiString text;
    BfmeRecord000B43E5 &operator=(const BfmeRecord000B43E5 &o);
};
BfmeRecord000B43E5 &BfmeRecord000B43E5::operator=(const BfmeRecord000B43E5 &o)
{
    word0 = o.word0;
    word1 = o.word1;
    word2 = o.word2;
    flag = o.flag;
    text = o.text;
    return *this;
}
