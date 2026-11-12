// cl: /O1 /arch:SSE /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// AptMessenger.cpp -- AptMessenger members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. The per-list player selections are an array of
// pointers at +0x280; each answers through 0x005AFEF7 (unnamed).

#include <vector>
#include "ascii_string.h"

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
}

// The second-tab name vector calls the existing out-of-line destructor.
namespace _STL { template <> vector<AsciiString>::~vector(); }
void __cdecl Rva004178C1(int profile, const AsciiString &name);
#include "../../../../../Include/GameNetwork/PlayerInfo.h"
#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;
void __cdecl Rva004177D5(int);

typedef int Int;

// ChatWindowsInGame.cpp owns the recovered query. The allocator is an
// address-derived ABI view of the native scalar vector, not an original name.
template<class T> class Rva002444BEAllocator : public _STL::allocator<T> {};
typedef _STL::vector<int,Rva002444BEAllocator<int> > SelectionIDs;
class ChatWindowsInGame
{
public:
	int rva005AFEF7(SelectionIDs *, _STL::vector<AsciiString> *);
};

// The rowed 0x00416088 destructor establishes two strings at record+8/+12.
// The 192-byte caller supplies the two -1 scalar defaults.
struct Rva00416088 {
    unsigned int m_00;
    unsigned int m_04;
    AsciiString m_08;
    AsciiString m_0C;
    Rva00416088() : m_00(-1), m_04(-1) {}
    ~Rva00416088();
};
// Native local occupies 24 bytes: profile / 16-byte string record / tail.
// Field meanings other than the iterated profile remain unknown.
struct Rva005AE7C6Info {
    int profile;
    Rva00416088 record;
    int tail;
    Rva005AE7C6Info() : profile(-1), tail(-1) {}
};
// The query is the rowed AptOnlineCustomMatch::FillBuddyInviteGameInfo
// (0x0059FB4F) and the helper the rowed cdecl Rva0041647ASend (0x0041647A),
// whose 24-byte Rva004160BEInfo record has this local's layout.
class Rva0059EF62;
#include "../../../../../Include/GameClient/AptOnlineCustomMatch.h"
extern int g_currentAptOnlineCustomMatch;
struct Rva004160BEInfo;
void Rva0041647ASend(const Rva004160BEInfo *info);

#include "../../../../../Include/GameClient/AptMessenger.h"

// WB AptMessengerOnline::OnBttnInvite (callgraph lead); the Online screen is this
// AptMessenger layout, so the body keeps the base view.
#include "../../../../../Include/GameClient/AptMessengerOnline.h"

// AptMessenger::GetSelectedPlayers, retail 0x00511C19.
void AptMessenger::GetSelectedPlayers(Int listIndex, Int a, Int b)
{
	ChatWindowsInGame *list = field280[listIndex];
	if (list)
		list->rva005AFEF7(reinterpret_cast<SelectionIDs *>(a),
			reinterpret_cast<_STL::vector<AsciiString> *>(b));
}


// Native 0x005AE886..0x005AE90F RET0; OnBttn_0 selects this first-tab
// action on the same screen receiver. Start from the 0.96 bank at
// reverse/attempts/0x005ae886.cpp; /EHs supplies its missing cleanup-state
// reset. The profile loop and virtual slot0x128 are observed target facts;
// the slot's original method name and application action remain unknown.
void AptMessenger::rva005AE886()
{
    if (!TheGameSpyInfo)
        return;
    _STL::vector<int> selected;
    GetSelectedPlayers(0, (int)&selected, 0);
    for (_STL::vector<int>::iterator entry = selected.begin();
            entry != selected.end(); ++entry) {
        int profile = *entry;
        if (profile != TheGameSpyInfo->getLocalProfileID())
            TheGameSpyInfo->removeBuddy(profile);
    }
}

// Native 0x005AE7C6..0x005AE886 RET0; rowed OnBttn_1 selects this
// screen method. The global query writes the 24-byte local; a failed query
// returns immediately. For each selected nonlocal profile, the cdecl helper
// receives that local with its first field replaced. Query/helper names and
// the remaining scalar meanings are retained as address-derived views.
void AptMessengerOnline::OnBttnInvite()
{
    AptOnlineCustomMatch *query = (AptOnlineCustomMatch *)g_currentAptOnlineCustomMatch;
    if (query) {
        Rva005AE7C6Info info;
        if (!query->FillBuddyInviteGameInfo((Rva0059EF62 *)&info))
            return;
        _STL::vector<int> selected;
        GetSelectedPlayers(0, (int)&selected, 0);
        for (_STL::vector<int>::iterator it = selected.begin();
                it != selected.end(); ++it) {
            int profile = *it;
            if (profile != TheGameSpyInfo->getLocalProfileID()) {
                info.profile = profile;
                Rva0041647ASend((const Rva004160BEInfo *)&info);
            }
        }
    }
}

// Native 0x005AE990..0x005AEA3E RET0; rowed OnBttn_0 selects this
// second-tab action. GetSelectedPlayers supplies parallel profile/name
// vectors. The rowed AsciiString-vector destructor at 0x0002CC70 fixes
// the second container's element identity and cleanup; the existing
// 0x004178C1 call used by AptSaveLoadCallbacks takes profile/name by reference.
void AptMessenger::rva005AE990()
{
    if (!TheGameSpyInfo)
        return;
    _STL::vector<int> profiles;
    _STL::vector<AsciiString> names;
    GetSelectedPlayers(1, (int)&profiles, (int)&names);
    _STL::vector<AsciiString>::iterator name = names.begin();
    for (_STL::vector<int>::iterator it = profiles.begin();
            it != profiles.end(); ++it, ++name) {
        int profile = *it;
        if (profile != TheGameSpyInfo->getLocalProfileID())
            Rva004178C1(profile, *name);
    }
}

// Native 0x005AEA3E..0x005AEB2C RET0; OnBttn_1 selects this second-tab
// action. PeerDefs.cpp identifies slots0x5C/0x12C/0x130 and the directly
// called PlayerInfo::isIgnored body at 0x00382841. Parallel selections
// toggle saved-ignore state for each nonlocal profile found in the player map.
void AptMessenger::rva005AEA3E()
{
    if (!TheGameSpyInfo)
        return;
    _STL::vector<int> profiles;
    _STL::vector<AsciiString> names;
    GetSelectedPlayers(1, (int)&profiles, (int)&names);
    _STL::vector<AsciiString>::iterator name = names.begin();
    for (_STL::vector<int>::iterator it = profiles.begin();
            it != profiles.end(); ++it, ++name) {
        int profile = *it;
        if (profile != TheGameSpyInfo->getLocalProfileID()) {
            PlayerInfo *player = TheGameSpyInfo->rva00382D0A(profile);
            if (player) {
                if (player->isIgnored())
                    TheGameSpyInfo->removeFromSavedIgnoreList(profile);
                else
                    TheGameSpyInfo->addToSavedIgnoreList(profile, *name);
            }
        }
    }
}
