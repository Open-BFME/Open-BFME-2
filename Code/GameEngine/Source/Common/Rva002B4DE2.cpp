// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE
// stlport
// ?rva002B4DE2@Rva002B4DE2@@QAEHXZ @0x002B4DE2 139B.
// Unlock lane; list of BfmeStringRecord002B4DC1 at +0xF0 counted by word1
// (2 -> ebx, 1 -> count1, total) then float ratios vs threshold at 0x007C6688.
// Callees rowed 0x002B4DC1 and 0x00036E70; unblocks 0x00512948.
// TU-local honest-address class; record layout from StringRecordInlineCopyBFME2.cpp.
#include "unicode_string.h"

struct BfmeStringRecord002B4DC1 {
    UnicodeString text;
    unsigned int word0;
    unsigned int word1;
    BfmeStringRecord002B4DC1(const BfmeStringRecord002B4DC1 &o) throw();
};

struct Rva002B4DE2Node {
    Rva002B4DE2Node *m_next;
    Rva002B4DE2Node *m_prev;
    BfmeStringRecord002B4DC1 m_value;
};

class Rva002B4DE2 {
    char m_pad[0xF0];
    Rva002B4DE2Node *m_list;
public:
    int rva002B4DE2();
    int rva002B5C1D();
};

int Rva002B4DE2::rva002B4DE2()
{
    int count1 = 0;
    int total = 0;
    int count2 = 0;
    for (Rva002B4DE2Node *n = m_list->m_next; n != m_list; n = n->m_next) {
        BfmeStringRecord002B4DC1 tmp = n->m_value;
        if (tmp.word1 == 2)
            ++count2;
        else if (tmp.word1 == 1)
            ++count1;
        ++total;
    }
    if ((float)count2 / (float)total >= 0.75f)
        return 2;
    if ((float)(count2 + count1) / (float)total >= 0.75f)
        return 1;
    return 0;
}

// Native 0x002B5C1D is a complete 65-byte thiscall list sum, called by
// the 0x00512838 formatting callback. The +0xF0 list and its 12-byte record
// agree independently with this unit's existing 0x002B4DE2 traversal.
// Each iteration copies node+8 through rowed 0x002B4DC1, adds record+4,
// and releases its wide string through rowed 0x00036E70.
// Reference lead: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BfmeConv1025.cpp. Its whole eight-body unit
// was compiled under /O1 /Os /O2. The donor's sum has list+0xC0; native
// evidence requires +0xF0 and the existing target record-copy provider.
// Original owner identity, scalar names and signedness remain unknown.
int Rva002B4DE2::rva002B5C1D()
{
    unsigned int total = 0;
    for (Rva002B4DE2Node *n = m_list->m_next; n != m_list; n = n->m_next) {
        BfmeStringRecord002B4DC1 tmp = n->m_value;
        total += tmp.word0;
    }
    return static_cast<int>(total);
}
