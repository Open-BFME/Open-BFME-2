// cl: /O1 /MD /EHs /Ireference/shims/bfme2_ascii
// WB1514C00 names AptMessengerLan::OnUpdateData at AptMessengerLan.cpp95.
// Native5AE4E5..5AE5E8 RET0; base update511E6D, LAN vslotE0,
// flag2A0, GameSlot name30, and both text bindings establish behavior.
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../../Include/GameNetwork/GameInfo.h"
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
#include "../../../../../Include/GameNetwork/LANAPI.h"
extern LANAPI *TheLAN;
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
 GameInfo *info=(GameInfo *)TheLAN->GetMyGame();
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
