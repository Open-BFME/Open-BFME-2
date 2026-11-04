// cl: /O1 /MD /EHs /Ireference/shims/bfme2_ascii
// WB1514C00 names AptMessengerLan::OnUpdateData at AptMessengerLan.cpp95.
// Native5AE4E5..5AE5E8 RET0; base update511E6D, LAN vslotE0,
// flag2A0, GameSlot name30, and both text bindings establish behavior.
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../../Include/GameNetwork/GameInfo.h"
template<int N> class LanSlots:public LanSlots<N-1> {public:virtual void gap(char (*)[N])=0;};
template<> class LanSlots<0> {};
class LANAPI:public LanSlots<56> {public:virtual GameInfo *slotE0()=0;};
extern LANAPI *TheLAN;
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
class AptMessenger {
public: virtual ~AptMessenger(); int rva00511E6D();
private:char unknown04[0x2A0-4];
};
class AptMessengerLan:public AptMessenger {
public:virtual int OnUpdateData();
private:bool showLobby;
};
int AptMessengerLan::OnUpdateData()
{
 int result=rva00511E6D();
 if (!TheLAN) return result;
 GameInfo *info=TheLAN->slotE0();
 if(info) {
  if(showLobby) {
   const GameSlot *slot=info->getConstSlot(0);
   if(!slot) return result;
   {
    AsciiString name("APT:CurrentLobbyName");
    g_bfmeAptWindowManager->bfmeSetText(name,slot->m_name,false);
   }
   showLobby=false;
  }
 } else if (!showLobby) {
  {
   AsciiString name("APT:CurrentLobbyName");
   g_bfmeAptWindowManager->bfmeSetText(name,TheGameText->fetch("APT:LobbyRoom",0),false);
  }
  showLobby=true;
 }
 return result;
}
