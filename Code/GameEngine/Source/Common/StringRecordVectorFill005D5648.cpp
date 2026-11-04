// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
// ?rva005D5648@ChatWindowsLan@@QAEXPAV?$vector@UBfmeStringRecord005D511F@@V?$allocator@UBfmeStringRecord005D511F@@@_STL@@@_STL@@PAVGameInfo@@@Z @0x005D5648 136B
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
    UnicodeString text0;
    unsigned int word0, word1;
    UnicodeString text1;
    unsigned int word2;
    BfmeStringRecord005D511F(const BfmeStringRecord005D511F &);
    BfmeStringRecord005D511F(const UnicodeString &, unsigned int,
        unsigned int, const UnicodeString &, unsigned int);
    ~BfmeStringRecord005D511F();
};

// Canonical GameSlot/GameInfo (GameInfo.h): name +0x30, NAT dword +0x38 and
// the port +0x3C, whose 16-bit field retail reads as a whole dword with its padding.
#include "../../Include/GameNetwork/GameInfo.h"

extern unsigned int g_00DB91B4;
extern unsigned int g_00DB91B0;
// Owned here (their only reader); retail .data initial colors.
unsigned int g_00DB91B4 = 0xFFFF00FF;
unsigned int g_00DB91B0 = 0xFFFF0000;

// A ChatWindowsLan member that never reads `this`: both retail callers in
// ChatWindowsLan (0x005D5715 in 0x005D56D0 and 0x005D579A in 0x005D574C) load
// ECX=this once for it and the GetLobbyPlayers member call they share.
class GameWindow;
class ChatWindowsLan
{
public:
	void GetLobbyPlayers(_STL::vector<BfmeStringRecord005D511F> *);
	bool PopulatePlayerList(_STL::vector<BfmeStringRecord005D511F>*);
	bool rva005D56D0();
	bool rva005D574C();
	// 0x005D5648 (StringRecordVectorFill005D5648.cpp): a member that never
	// reads ECX; this caller sets ECX=this for it (retail hoists that into the
	// loop test it shares with PopulatePlayerList).
	void rva005D5648(_STL::vector<BfmeStringRecord005D511F> *, GameInfo *);
	char m_pad00[0x10];
	class GameWindow *playerList10; // +0x10
};

void ChatWindowsLan::rva005D5648(_STL::vector<BfmeStringRecord005D511F> *vec, GameInfo *info)
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
        BfmeStringRecord005D511F tmp(slot->m_name, slot->m_field38,
            *reinterpret_cast<const unsigned int *>(&slot->m_field3C),
            UnicodeString::TheEmptyString, arg);
        vec->push_back(tmp);
        arg = g_00DB91B0;
    }
}
