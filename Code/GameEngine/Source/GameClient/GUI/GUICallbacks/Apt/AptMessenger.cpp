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
class GameSpyInfoInterface {public:
 virtual void _M_slot_00();
 virtual void _M_slot_04();
 virtual void _M_slot_08();
 virtual void _M_slot_0c();
 virtual void _M_slot_10();
 virtual void _M_slot_14();
 virtual void _M_slot_18();
 virtual void _M_slot_1c();
 virtual void _M_slot_20();
 virtual void _M_slot_24();
 virtual void _M_slot_28();
 virtual void _M_slot_2c();
 virtual void _M_slot_30();
 virtual void _M_slot_34();
 virtual void _M_slot_38();
 virtual void _M_slot_3c();
 virtual void _M_slot_40();
 virtual void _M_slot_44();
 virtual void _M_slot_48();
 virtual void _M_slot_4c();
 virtual void _M_slot_50();
 virtual void _M_slot_54();
 virtual void _M_slot_58();
 virtual PlayerInfo *rva00382D0A(int profile);
 virtual void _M_slot_60();
 virtual void _M_slot_64();
 virtual void _M_slot_68();
 virtual void _M_slot_6c();
 virtual void _M_slot_70();
 virtual void _M_slot_74();
 virtual void _M_slot_78();
 virtual int getLocalProfileID();
 virtual void _M_slot_80();
 virtual void _M_slot_84();
 virtual void _M_slot_88();
 virtual void _M_slot_8c();
 virtual void _M_slot_90();
 virtual void _M_slot_94();
 virtual void _M_slot_98();
 virtual void _M_slot_9c();
 virtual void _M_slot_a0();
 virtual void _M_slot_a4();
 virtual void _M_slot_a8();
 virtual void _M_slot_ac();
 virtual void _M_slot_b0();
 virtual void _M_slot_b4();
 virtual void _M_slot_b8();
 virtual void _M_slot_bc();
 virtual void _M_slot_c0();
 virtual void _M_slot_c4();
 virtual void _M_slot_c8();
 virtual void _M_slot_cc();
 virtual void _M_slot_d0();
 virtual void _M_slot_d4();
 virtual void _M_slot_d8();
 virtual void _M_slot_dc();
 virtual void _M_slot_e0();
 virtual void _M_slot_e4();
 virtual void _M_slot_e8();
 virtual void _M_slot_ec();
 virtual void _M_slot_f0();
 virtual void _M_slot_f4();
 virtual void _M_slot_f8();
 virtual void _M_slot_fc();
 virtual void _M_slot_100();
 virtual void _M_slot_104();
 virtual void _M_slot_108();
 virtual void _M_slot_10c();
 virtual void _M_slot_110();
 virtual void _M_slot_114();
 virtual void _M_slot_118();
 virtual void _M_slot_11c();
 virtual void _M_slot_120();
 virtual void _M_slot_124();
 virtual void _M_slot_128(int profile);
 virtual void addToSavedIgnoreList(int profile, AsciiString name);
 virtual void removeFromSavedIgnoreList(int profile);
};
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
class AptOnlineCustomMatch {public: bool FillBuddyInviteGameInfo(Rva0059EF62 *info);};
extern int g_currentAptOnlineCustomMatch;
struct Rva004160BEInfo;
void Rva0041647ASend(const Rva004160BEInfo *info);

class AptMessenger
{
public:
	__declspec(noinline) void GetSelectedPlayers(Int listIndex, Int a, Int b);
	void rva005AE90F();
	void rva005AE886();
	void rva005AE990();
	void rva005AEA3E();

private:
	unsigned char m_pad000[0x280];
	ChatWindowsInGame **m_lists;		// +0x280
};

// WB AptMessengerOnline::OnBttnInvite (callgraph lead); the Online screen is this
// AptMessenger layout, so the body keeps the base view.
class AptMessengerOnline : public AptMessenger
{
public:
	void OnBttnInvite();
};

// AptMessenger::GetSelectedPlayers, retail 0x00511C19.
void AptMessenger::GetSelectedPlayers(Int listIndex, Int a, Int b)
{
	ChatWindowsInGame *list = m_lists[listIndex];
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
            TheGameSpyInfo->_M_slot_128(profile);
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
