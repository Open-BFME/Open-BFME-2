// ?UpdatePlayerTabButtons@AptMessengerOnline@@QAEXXZ
// partial score=0.75 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
#include <vector>
#include "ascii_string.h"
void Rva00030830FreeAllocation(void *);
struct BfmeE8 {void *p;unsigned char flag;char pad[3];};
namespace _STL {
template<> inline void allocator<int>::deallocate(int *p,size_t) const {if(p)::Rva00030830FreeAllocation(p);}
template<> inline void allocator<BfmeE8>::deallocate(BfmeE8 *p,size_t) const {if(p)::Rva00030830FreeAllocation(p);}
}
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

class AptMessenger {public:__declspec(noinline) void GetSelectedPlayers(int,int,int);};
class Rva005AEB2C {public:Rva005AEB2C();_STL::vector<BfmeE8> m_vec;};
class Rva005AE7A5Class {public:int rva005AE7A5(int);};
extern int g_Va00E046BC;
struct MessengerOnlineButton {AsciiString text;bool enabled;char pad[3];};
class AptMessengerOnline : public AptMessenger {
public:void UpdatePlayerTabButtons();
private:char prefix[0x28c];MessengerOnlineButton *buttons;char middle[0x10];bool acceptingFriend;
};
void AptMessengerOnline::UpdatePlayerTabButtons(){
 if(!TheGameSpyInfo)return;
 buttons[0].text.set("APT:AddFriend");
 buttons[1].text.set("APT:Ignore");
 buttons[0].enabled=false;
 buttons[1].enabled=false;
 acceptingFriend=false;
 _STL::vector<int> selected;
 GetSelectedPlayers(g_Va00E046BC,(int)&selected,0);
 if(selected.size()!=1)return;
 struct SelectionState {int notIgnored,notBuddy,ignored,pendingBuddy;int *it;};
 SelectionState state;state.ignored=0;state.notIgnored=0;state.notBuddy=0;state.pendingBuddy=0;
 int local=TheGameSpyInfo->getLocalProfileID();
 Rva005AEB2C buddies;
 for(state.it=selected.begin();state.it!=selected.end();++state.it){
  int profile=*state.it;
  if(profile==local)goto cleanup;
  BfmeE8 *buddy=(BfmeE8 *)((Rva005AE7A5Class *)&buddies)->rva005AE7A5(profile);
  if(buddy){if(!buddy->flag)goto cleanup;++state.pendingBuddy;}else ++state.notBuddy;
  PlayerInfo *player=TheGameSpyInfo->rva00382D0A(profile);
  if(player){if(player->isIgnored())++state.ignored;else ++state.notIgnored;}
 }
 if(state.notBuddy){buttons[0].enabled=(state.pendingBuddy==0);}
 else if(state.pendingBuddy){buttons[0].text.set("APT:AcceptFriend");buttons[0].enabled=true;acceptingFriend=true;}
 if(state.notIgnored){buttons[1].enabled=(state.ignored==0);}
 else if(state.ignored){buttons[1].enabled=true;buttons[1].text.set("APT:RemoveIgnore");}
cleanup:;
}
