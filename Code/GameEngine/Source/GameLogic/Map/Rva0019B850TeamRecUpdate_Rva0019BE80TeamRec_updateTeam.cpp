// cl: /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/stringbaseascii /Ireference/open-bfme-1/inputs/reference/shims/buildlistinfo /Ireference/open-bfme-1/inputs/reference/shims/moduledata /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Map /Ireference/shims/bfmealloc /D_CRTIMP=
//
// ?addToIndex@TeamsInfoRec@@QAEXH@Z
// retail 0x0032D103, 288 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameLogic/Map/Rva0019B850TeamRecUpdate.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport
// BFME 1 retail 0x0019B850, 396 bytes (the donor called it updateTeam; WorldBuilder names it TeamsInfoRec::addToIndex):
// 0x0019BA40 and 0x0019BC00 call this one-index thiscall through ILT 0x26EE.
// The map key is (teamOwner, teamName). The vector at +0x0C contains
// 16-byte records: a Dict at +0x0C and a tree node link at +8.
// New keys map to the index; existing keys link the previous and current
// records through shorts at +6/+4, then update the tree's index at node+0x18.
// Native map::insert's result wrapper and vector::begin's access expression
// are required for the retail return-buffer and register allocation.

#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/Dict.h"
#include "Common/WellKnownKeys.h"
#include <map>
#include <vector>
typedef _STL::pair<AsciiString,AsciiString> TeamKey0019B850;
typedef _STL::pair<TeamKey0019B850,int> TeamPair0019B850;
typedef _STL::pair<const TeamKey0019B850,int> TeamValue0019B850;
typedef _STL::_Rb_tree<TeamKey0019B850,TeamValue0019B850,_STL::_Select1st<TeamValue0019B850>,_STL::less<TeamKey0019B850>,_STL::allocator<TeamValue0019B850> > TeamTree0019B850;
namespace _STL {
template<> pair<TeamKey0019B850,int>::~pair();
template<> pair<const TeamKey0019B850,int>::~pair();
template<> __declspec(noinline) TeamPair0019B850 make_pair(const TeamKey0019B850& key, const int& index) { return TeamPair0019B850(key,index); }
}
// This key ordering has its own retail tree body; keep its address in the
// comparator type instead of borrowing a different physical instantiation.
struct TeamLess0019B850 : _STL::less<TeamKey0019B850> {};
struct TeamRecord0019B850 {
    short field00, field02, field04, field06;
    _STL::_Rb_tree_node_base* field08;
    Dict field0c;
};
class TeamsInfoRec
{
    _STL::map<TeamKey0019B850,int,TeamLess0019B850> field00;
    _STL::vector<TeamRecord0019B850> field0c;
public:
    void addToIndex(int index);
};
void TeamsInfoRec::addToIndex(int index) {
    TeamRecord0019B850* team = field0c.begin() + index;
    TeamKey0019B850 key(team->field0c.getAsciiString(TheKey_teamOwner),team->field0c.getAsciiString(TheKey_teamName));
    team->field08 = field00.find(key)._M_node;
    if(team->field08 == field00.end()._M_node) {
        team->field08 = field00.insert(_STL::make_pair(key,index)).first._M_node;
    } else {
        int previous = static_cast<_STL::_Rb_tree_node<TeamValue0019B850>*>(team->field08)->_M_value_field.second;
        TeamRecord0019B850* prior = field0c.begin() + previous; prior->field06 = (short)index;
        team->field04 = (short)previous;
        static_cast<_STL::_Rb_tree_node<TeamValue0019B850>*>(team->field08)->_M_value_field.second = index;
    }
}

typedef char RecordWidth0019B850[(sizeof(TeamRecord0019B850)==16)?1:-1];

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?find@Rva0032C07COwner@@QAEPAUTeamMapNode@@AAURva0002C4FD@@@Z=??$_M_find@U?$pair@VAsciiString@@V1@@_STL@@@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@UTeamLess0019B850@@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@1@ABU?$pair@VAsciiString@@V1@@1@@Z")
