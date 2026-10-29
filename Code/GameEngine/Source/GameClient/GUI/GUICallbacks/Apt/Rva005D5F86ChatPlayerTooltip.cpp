// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?showPlayerTooltip@Rva005D5F86@@QAEXABVAsciiString@@@Z
// Retail 0x005D5F86..0x005D62E8 (866 bytes) RET4, ecx unused. The chat
// player tooltip: translates the player name, looks up its PlayerInfo
// through TheGameSpyInfo slot 0x58, then builds the locale label
// (WOL:Locale%2.2d), favourite side (APT:Men or SIDE:%s), ladder rank from
// the mode threshold tables, the two rank labels (rowed 0x005D59F0) into
// TOOLTIP:ChatPlayerInfo, prefixes TOOLTIP:BuddyPlayer or
// TOOLTIP:GenericPlayer and hands it to TheMouse; an unknown name gets the
// bare name at scale 1.5.
// Evidence: retail literals, callees and offsets; the staging-room sibling
// AptOnlineCustomMatch::MpOwnerUpdatePlayerTooltip (0x005A00E6, same
// PlayerInfo/GameSpyInfo views) and the BFME1 donor chat tooltip
// (Rva005307B0ChatPlayerTooltip.cpp, revision 9cbfb551) as semantic guide.
// The owner class is unidentified, so the name is address-derived.

#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <stdlib.h>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// The profile record (layout as the staging tooltip's view).
class PlayerInfo
{
public:
    unsigned char m_prefix[8];
    AsciiString m_locale;
    int m_wins;
    int m_losses;
    int m_profileID;
    int m_18;
    int m_rankPoints;
    int m_rank20;
    int m_rank24;
    int m_side;
    int m_favoriteSide;
};

class BuddyInfo
{
public:
    int m_id;
    AsciiString m_name;
    AsciiString m_email;
    AsciiString m_countryCode;
    int m_status;
    UnicodeString m_statusString;
    UnicodeString m_locationString;
};
typedef std::map<int, BuddyInfo> BuddyInfoMap;

class GameSpyInfoInterface
{
public:
#define V(n) virtual void gs##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21)
    virtual PlayerInfo *rva00382CCE(const char *name) = 0; // rowed native +0x58
    V(23)
    virtual BuddyInfoMap *getBuddyMap() = 0; // native +0x60
#undef V
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class GameTextInterface
{
public:
#define T(n) virtual void t##n();
	T(0) T(1) T(2) T(3) T(4) T(5) T(6) T(7) T(8) T(9) T(10) T(11) T(12) T(13)
#undef T
    virtual UnicodeString fetch(const char *, bool *exists = 0);
    virtual UnicodeString fetch(const AsciiString &, bool *exists = 0);
    virtual void t16();
    virtual UnicodeString *fetchPtr(const char *, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

struct RGBColor;
class Mouse
{
public:
    void rva001EEA6D(UnicodeString, int, const RGBColor *, float);
};
extern Mouse *TheMouse;

// Existing 52-byte rank-table globals defined by Rva005B8116Stats.cpp and
// the mode flag that picks between them (ColdGlobalDwordGetters.cpp).
class Rva00559D0CRankWeights;
extern Rva00559D0CRankWeights g_00E05FCC;
extern Rva00559D0CRankWeights g_00E06000;
extern int g_Va00E06548;
extern const char *g_rva0033A3F4Table[7];
UnicodeString Rva00559CE5(int side, int rank);
UnicodeString Rva005D59F0Get(int rank);

class Rva005D5F86
{
public:
    void showPlayerTooltip(const AsciiString &name);
};

void Rva005D5F86::showPlayerTooltip(const AsciiString &name)
{
    if (!TheGameSpyInfo)
        return;
    UnicodeString uName;
    uName.translate(name);
    PlayerInfo *info = TheGameSpyInfo->rva00382CCE(name.str());
    if (!info) {
        TheMouse->rva001EEA6D(uName, -1, 0, 1.5f);
        return;
    }
    int profileID = info->m_profileID;
    AsciiString localeIdentifier;
    localeIdentifier.format("WOL:Locale%2.2d", atoi(info->m_locale.str()));
    UnicodeString playerInfo;
    int wins = 0;
    int losses = 0;
    wins = info->m_wins;
    losses = info->m_losses;
    UnicodeString favoriteSide;
    int totalGames = 0;
    int side = 0;
    totalGames = info->m_wins + info->m_losses;
    side = info->m_favoriteSide;
    if (!totalGames)
        favoriteSide = TheGameText->fetch("APT:Men");
    else {
        AsciiString sideKey;
        sideKey.format("SIDE:%s", g_rva0033A3F4Table[side]);
        favoriteSide = TheGameText->fetch(sideKey);
    }
    const int *thresholds = g_Va00E06548 ? (const int *)&g_00E05FCC : (const int *)&g_00E06000;
    int rankSide = info->m_side;
    int points = info->m_rankPoints;
    int rank;
    for (rank = 1; rank < 11; ++rank)
        if (points < thresholds[rank])
            break;
    UnicodeString rankText = Rva00559CE5(rankSide, rank - 1);
    UnicodeString rank20 = Rva005D59F0Get(info->m_rank20);
    UnicodeString rank24 = Rva005D59F0Get(info->m_rank24);
    playerInfo.format(TheGameText->fetchPtr("TOOLTIP:ChatPlayerInfo"),
        TheGameText->fetch(localeIdentifier).str(), rankText.str(),
        wins, losses, favoriteSide.str(), rank20.str(), rank24.str());
    UnicodeString tooltip = UnicodeString::TheEmptyString;
    if (TheGameSpyInfo->getBuddyMap()->find(profileID) != TheGameSpyInfo->getBuddyMap()->end())
        tooltip.format(TheGameText->fetchPtr("TOOLTIP:BuddyPlayer"), uName.str());
    else
        tooltip.format(TheGameText->fetchPtr("TOOLTIP:GenericPlayer"), uName.str());
    tooltip.concat(playerInfo);
    TheMouse->rva001EEA6D(tooltip, -1, 0, 1.0f);
}
