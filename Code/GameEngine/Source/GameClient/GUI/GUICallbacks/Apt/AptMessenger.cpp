// cl: /O1 /arch:SSE /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// AptMessenger.cpp -- AptMessenger members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. The per-list player selections are an array of
// pointers at +0x280; each answers through 0x005AFEF7 (unnamed).

#include <vector>
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
 virtual void _M_slot_5c();
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
};
extern GameSpyInfoInterface *TheGameSpyInfo;
void __cdecl Rva004177D5(int);

typedef int Int;

class Rva005AFEF7List
{
public:
	void rva005AFEF7(Int a, Int b);		// 0x005AFEF7
};

class AptMessenger
{
public:
	__declspec(noinline) void GetSelectedPlayers(Int listIndex, Int a, Int b);
	void rva005AE90F();
	void rva005AE886();

private:
	unsigned char m_pad000[0x280];
	Rva005AFEF7List **m_lists;		// +0x280
};

// AptMessenger::GetSelectedPlayers, retail 0x00511C19.
void AptMessenger::GetSelectedPlayers(Int listIndex, Int a, Int b)
{
	Rva005AFEF7List *list = m_lists[listIndex];
	if (list)
		list->rva005AFEF7(a, b);
}

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
