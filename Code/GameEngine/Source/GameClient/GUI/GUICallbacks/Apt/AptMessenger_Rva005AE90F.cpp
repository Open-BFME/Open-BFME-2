// cl: /O1 /arch:SSE /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Split from AptMessenger.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
#include "../../../../../Include/Common/ChatWindowsInGame.h"

// The rowed 0x00416088 destructor establishes two strings at record+8/+12.
// The 192-byte caller supplies the two -1 scalar defaults.
// Native local occupies 24 bytes: profile / 16-byte string record / tail.
// Field meanings other than the iterated profile remain unknown.
// The query is the rowed AptOnlineCustomMatch::FillBuddyInviteGameInfo
// (0x0059FB4F) and the helper the rowed cdecl Rva0041647ASend (0x0041647A),
// whose 24-byte Rva004160BEInfo record has this local's layout.
class Rva0059EF62;
class AptOnlineCustomMatch {public: bool FillBuddyInviteGameInfo(Rva0059EF62 *info);};
extern int g_currentAptOnlineCustomMatch;
struct Rva004160BEInfo;
void Rva0041647ASend(const Rva004160BEInfo *info);

#include "../../../../../Include/GameClient/AptMessenger.h"

// WB AptMessengerOnline::OnBttnInvite (callgraph lead); the Online screen is this
// AptMessenger layout, so the body keeps the base view.
#include "../../../../../Include/GameClient/AptMessengerOnline.h"


// Native 0x005AE90F..0x005AE990 RET0; AptMessenger::OnBttn_1 calls this
// method on the screen receiver (rowed 0x005AEF32). The vector base ctor
// is rowed at 0x00211E58, and GetSelectedPlayers writes to that vector.
// OnlinePreferences.cpp independently identifies TheGameSpyInfo's slot0x7C
// as getLocalProfileID. The remaining cdecl helper's application name is unknown.
// STLport 4.5.3 vector<int> provides the 12-byte selection container;
// /EHs preserves the observed cleanup state before free.
void AptMessenger::rva005AE90F()
{
    if (TheGameSpyInfo) {
        _STL::vector<int> selected;
        GetSelectedPlayers(0, (int)&selected, 0);
        for (_STL::vector<int>::iterator it = selected.begin();
                it != selected.end(); ++it) {
            int profile = *it;
            if (profile != TheGameSpyInfo->getLocalProfileID())
                Rva004177D5(profile);
        }
    }
}




