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
class PlayerInfo {public: bool isIgnored();};
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




