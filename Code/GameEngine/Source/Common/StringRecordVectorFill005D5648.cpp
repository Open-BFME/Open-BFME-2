// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva005D5648Fill@@YGXPAV?$vector@UBfmeStringRecord005D511F@@V?$allocator@UBfmeStringRecord005D511F@@@_STL@@@_STL@@PAVGameInfo@@@Z @0x005D5648 136B
// Fill a vector<BfmeStringRecord005D511F> from human game slots. Layout from
// GameSlotSetState (name@0x30 ip@0x34 nat@0x38 port@0x3C) and the 5-arg ctor
// row 0x005D516E plus push_back row 0x005D5548. Callers 0x005D5715 0x005D579A.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeStringRecord005D511F {
    UnicodeString text0; unsigned int word0, word1; UnicodeString text1; unsigned int word2;
    BfmeStringRecord005D511F(const BfmeStringRecord005D511F &o);
    BfmeStringRecord005D511F(const UnicodeString &t0, unsigned int w0, unsigned int w1, const UnicodeString &t1, unsigned int w2);
    ~BfmeStringRecord005D511F();
};

class GameSlot
{
public:
    bool isHuman() const;
    void *m_vtable;                 // +0x00
    int m_state;                    // +0x04
    bool m_isAccepted;              // +0x08
    bool m_hasMap;                  // +0x09
    bool m_isMuted;                 // +0x0A
    char m_pad0B;                   // +0x0B
    int m_color;                    // +0x0C
    int m_startPos;                 // +0x10
    int m_bfme14;                   // +0x14
    int m_playerTemplate;           // +0x18
    int m_teamNumber;               // +0x1C
    int m_bfme20;                   // +0x20
    int m_origColor;                // +0x24
    int m_origStartPos;             // +0x28
    int m_origPlayerTemplate;       // +0x2C
    UnicodeString m_name;           // +0x30
    AsciiString m_ip;               // +0x34
    unsigned int m_nat;             // +0x38
    unsigned int m_port;            // +0x3C
};

class GameInfo
{
public:
    GameSlot *getSlot(int slotNum);
private:
    char m_pad[0x18];
    GameSlot *m_slot[8];
};

extern unsigned int g_00DB91B4;
extern unsigned int g_00DB91B0;

void __stdcall Rva005D5648Fill(_STL::vector<BfmeStringRecord005D511F> *vec, GameInfo *info)
{
    int i = 0;
    if (info == 0)
        return;
    unsigned int arg = g_00DB91B4;
    for (; i < 8; ++i)
    {
        GameSlot *slot = info->getSlot(i);
        if (slot == 0)
            continue;
        if (!slot->isHuman())
            continue;
        BfmeStringRecord005D511F tmp(slot->m_name, slot->m_nat, slot->m_port, UnicodeString::TheEmptyString, arg);
        vec->push_back(tmp);
        arg = g_00DB91B0;
    }
}
