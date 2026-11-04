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

// Use the shared retail PlayerInfo layout for the profile record.
#include "../../../../../Include/GameNetwork/PlayerInfo.h"

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

#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

struct RGBColor;
#include "../../../../../Include/GameClient/Mouse.h"
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
    int profileID = info->m_at14;
    AsciiString localeIdentifier;
    localeIdentifier.format("WOL:Locale%2.2d", atoi(info->m_at08.str()));
    UnicodeString playerInfo;
    int wins = 0;
    int losses = 0;
    wins = info->m_at0c;
    losses = info->m_at10;
    UnicodeString favoriteSide;
    int totalGames = 0;
    int side = 0;
    totalGames = info->m_at0c + info->m_at10;
    side = info->m_at2c;
    if (!totalGames)
        favoriteSide = TheGameText->fetch("APT:Men");
    else {
        AsciiString sideKey;
        sideKey.format("SIDE:%s", g_rva0033A3F4Table[side]);
        favoriteSide = TheGameText->fetch(sideKey);
    }
    const int *thresholds = g_Va00E06548 ? (const int *)&g_00E05FCC : (const int *)&g_00E06000;
    int rankSide = info->m_at28;
    int points = info->m_at1c;
    int rank;
    for (rank = 1; rank < 11; ++rank)
        if (points < thresholds[rank])
            break;
    UnicodeString rankText = Rva00559CE5(rankSide, rank - 1);
    UnicodeString rank20 = Rva005D59F0Get(info->m_at20);
    UnicodeString rank24 = Rva005D59F0Get(info->m_at24);
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
