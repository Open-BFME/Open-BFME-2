// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// ??1?$vector@UBfmeStringRecord005D511F@@V?$allocator@UBfmeStringRecord005D511F@@@_STL@@@_STL@@QAE@XZ @0x005D5434 63B.
// Vector dtor over 0x14-byte BfmeStringRecord005D511F via rowed _Destroy 0x005D541B and _free 0x00030830.
// Same EH shape (and/or -1 states) as BfmeStringRecord00111ACF vector dtor @0x003F6936 and Prereq vector dtor @0x002D040C.
// Callers 0x005D56D0 and 0x005D574C.
#include <vector>
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
// 0x14-byte record (the rowed _Destroy loop steps by 0x14), spelled as ChatWindowsLan.cpp does.
struct BfmeStringRecord005D511F {
    UnicodeString text0;
    unsigned int word0, word1;
    UnicodeString text1;
    unsigned int word2;
    BfmeStringRecord005D511F(const BfmeStringRecord005D511F &);
    BfmeStringRecord005D511F(const UnicodeString &, unsigned int,
        unsigned int, const UnicodeString &, unsigned int);
    ~BfmeStringRecord005D511F();
};
template _STL::vector<BfmeStringRecord005D511F>::~vector();
