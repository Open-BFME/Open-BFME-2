// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native 0x000B68F0,27B: extends the observed20B record assignment by one dword.
// Application type and field meanings remain unknown; the old gslice identity is refuted.
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../GameEngine/Include/Common/BfmeRecord000B43E5.h"
struct Rva000B978ARecord : BfmeRecord000B43E5 {
    unsigned int word14;
    Rva000B978ARecord &operator=(const Rva000B978ARecord &);
};
typedef char RecordSizeIs24[sizeof(Rva000B978ARecord)==24 ? 1 : -1];
Rva000B978ARecord &Rva000B978ARecord::operator=(const Rva000B978ARecord &other)
{
    BfmeRecord000B43E5::operator=(other);
    word14 = other.word14;
    return *this;
}
