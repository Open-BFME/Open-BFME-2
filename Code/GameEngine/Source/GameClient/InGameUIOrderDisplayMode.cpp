// cl: /O1 /G7 /MD /EHsc
// WB DB0210 names InGameUI::updateOrderDisplayMode, InGameUI.cpp:2849..2865.
// Native29A72C..29A767 is the complete59-byte target body (RET0).
// Target facts: ThePlayerList local player +10; player order mode +750
// (WB +758); UI display mode +8B4. All three native switch cases are kept.
// Unknown order modes preserve the previous display mode; no player sets0.
// Partial accessed class prefixes only; no class vtable is emitted.
class Player {public:char prefix[0x750];int orderMode;};
class PlayerList {public:char prefix[0x10];Player *local;};
extern PlayerList *ThePlayerList;
#include "../../Include/GameClient/InGameUI.h"
void InGameUI::updateOrderDisplayMode(){
 Player *player=ThePlayerList->local;
 if(player){
  switch(player->orderMode){
  case 0:m_8B4=0;break;
  case 1:m_8B4=1;break;
  case 2:m_8B4=2;break;
  }
 }else m_8B4=0;
}
