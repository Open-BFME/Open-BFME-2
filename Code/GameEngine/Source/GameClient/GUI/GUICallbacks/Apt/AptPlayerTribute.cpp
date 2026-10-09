// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native tribute row callbacks. Shared339B update bodies remain in their
// existing Rva0050FF7FMethod and VslotSmallBodiesS provider homes after the
// concurrent recovery. This home owns row creation468B, debit65B and send179B.
#include "ascii_string.h"
class Player;
class PlayerList {public: char unknown00[0x10]; Player *localPlayer;};
extern PlayerList *ThePlayerList;
class Player {public: bool isLocalPlayer() const; char unknown00[0x54];int index;};
class BfmeMemberRV {public: bool bfmeAskRV();};
class Rva0050F0AB {public: char unknown00[0x6c];unsigned amount;void rva0050F2AF(unsigned);};
class Rva0050F041;
class Rva0050F5A6 { public:
 void rva0050FFEC(const char*); void rva0050EB0A(const char*);
 int level;char unknown04[0x1c];int count;
 struct Entry { Player *player;Rva0050F041 *object; };
 Entry *entries() { return reinterpret_cast<Entry *>((char *)this+0x24); }
};
extern "C" __declspec(dllimport) int __cdecl atoi(const char*);
bool Rva004128F0GetParam(const char*,const char*,AsciiString&);
namespace AptUtils { int LevelIndexFromTarget(const char*); const char *SkipLevelN(const char*); }

class Rva0050FC54 {public: Rva0050FC54(int,const AsciiString&,Player*);char opaque[0x80];};
class Rva0050FF55 {public: Rva0050FF55(Rva0050F5A6*,int,const AsciiString&,Player*);int rva0050EAC1();char opaque[0x80];Rva0050F5A6 *parent;};
class Object;
class Rva00575674 {public:void rva00575674(Object*);};
// Native50FFEC..5101C0 468B RET4; WB1358B70/tribute.cpp1203 corroborates
// index/name parsing and local-player row selection without an original name.
// Native constructors50FF55(42B RET16) and50FC54(392B RET12) receive ordinary
// ECX plus parent/level/path-reference/player or level/path-reference/player.
// The measured opaque sizes84/80 come from retail new operands, not WB layout.
// Both publish into the same slot via the existing pooled Object setter.
void Rva0050F5A6::rva0050FFEC(const char *params) {
 AsciiString indexText;
 if(!Rva004128F0GetParam(params,"index",indexText))return;
 int index=atoi(indexText.str());
 if(index<0 || index>count)return;
 Entry &slot=entries()[index];
 if(slot.object)return;
 AsciiString name;
 if(!Rva004128F0GetParam(params,"name",name))return;
 int rowLevel=AptUtils::LevelIndexFromTarget(name.str());
 if(rowLevel!=level)return;
 if(slot.player->isLocalPlayer())
  reinterpret_cast<Rva00575674*>(&slot.object)->rva00575674(reinterpret_cast<Object*>(new Rva0050FF55(this,rowLevel,AsciiString(AptUtils::SkipLevelN(name.str())),slot.player)));
 else
  reinterpret_cast<Rva00575674*>(&slot.object)->rva00575674(reinterpret_cast<Object*>(new Rva0050FC54(rowLevel,AsciiString(AptUtils::SkipLevelN(name.str())),slot.player)));
}

// Native50EAC1..50EB02 65B RET0, not the served260B extent which crosses
// three following independent bodies. Local-row constructor50FF55 proves
// parent80; the exact walkers prove count20 and paired player24/UI28.
// Slot1 of local-row vtableC655C4 points here. Native computes the negative
// total of amounts belonging to other players, skipping absent row objects.
int Rva0050FF55::rva0050EAC1(){
 int total=0;
 for(int i=0;i<parent->count;++i){
  Rva0050F5A6::Entry &slot=parent->entries()[i];
  if(!slot.player->isLocalPlayer() && slot.object)
   total-=reinterpret_cast<Rva0050F0AB*>(slot.object)->amount;
 }
 return total;
}

// Native50EB0A..50EBBD 179B RET4; WB13591B0 tribute assertions1275..1306
// corroborates focus clear and per-recipient tribute messages. Its apparent
// native260B twin at50EAC1 crosses the earlier65B debit and rowed8B helper.
// Player54 is the native integer passed with recipient54 and amount6C; window
// focus is vslot49 and MessageStream appendMessage vslot18 takes message466.
// ABI views below name only this measured virtual surface, not complete types.
class GameWindow;
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class AptTributeWindowManager {public:
#define W(n) virtual void slot##n();
 W(0) W(1) W(2) W(3) W(4) W(5) W(6) W(7) W(8) W(9)
 W(10) W(11) W(12) W(13) W(14) W(15) W(16) W(17) W(18) W(19)
 W(20) W(21) W(22) W(23) W(24) W(25) W(26) W(27) W(28) W(29)
 W(30) W(31) W(32) W(33) W(34) W(35) W(36) W(37) W(38) W(39)
 W(40) W(41) W(42) W(43) W(44) W(45) W(46) W(47) W(48)
#undef W
 virtual int winSetFocus(GameWindow*);
};
class GameMessage {public:void appendIntegerArgument(int);};
class MessageStream {public:
#define M(n) virtual void slot##n();
 M(0) M(1) M(2) M(3) M(4) M(5) M(6) M(7) M(8) M(9)
 M(10) M(11) M(12) M(13) M(14) M(15) M(16) M(17)
#undef M
 virtual GameMessage *appendMessage(int);
};
extern MessageStream *TheMessageStream;
void Rva0050F5A6::rva0050EB0A(const char *unused){
 reinterpret_cast<AptTributeWindowManager*>(TheWindowManager)->winSetFocus(0);
 Player *local=ThePlayerList->localPlayer;
 if(!reinterpret_cast<BfmeMemberRV*>(local)->bfmeAskRV())return;
 for(int i=0;i<count;++i){
  Entry &slot=entries()[i];
  Player *player=slot.player;
  if(player==local || !reinterpret_cast<BfmeMemberRV*>(player)->bfmeAskRV())continue;
  if(!slot.object)continue;
  unsigned amount=reinterpret_cast<Rva0050F0AB*>(slot.object)->amount;
  if(amount>0){
   GameMessage *message=TheMessageStream->appendMessage(0x466);
   if(message){
    message->appendIntegerArgument(local->index);
    message->appendIntegerArgument(player->index);
    message->appendIntegerArgument(amount);
   }
  }
 }
}

