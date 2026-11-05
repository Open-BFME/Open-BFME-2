// cl: /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Reference: GeneralsMD SkirmishGameOptionsMenu.cpp updateMapStartSpots at
// BFME1 reference revision6583b3c1ff21db4a561285717028fdafc780b7db.
// Target identity: map getter23E943, map metadata copy3039E8 and destructor
// 22DBC6, GameSlot accessors, NUMBER:%d and TOOLTIP:StartPosition strings.
// Retail boundary303AE9..303D6B is642B. Target removes reference null checks,
// uses GUI:Blank when no map is found, fetches borrowed tooltip text via
// slot44, and resets an out-of-range actual start position to -1.
// MapMetaData256B/copy/dtor separately verified in MapMetaDataCopy.cpp.
// This is a call-only prefix view, not its construction model.
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../../Include/GameClient/MapMetaData.h"
#include "../../../../../Include/GameClient/MapCache.h"
typedef char MapMetaDataSizeCheck[sizeof(MapMetaData)==0x100?1:-1];
extern MapCache *TheMapCache;
#include "../../../../../Include/GameNetwork/GameInfo.h"
#include "../../../../../Include/GameClient/Bfme2GameWindow.h"
void GadgetButtonSetText(GameWindow*,UnicodeString);
#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
void updateMapStartSpots(GameInfo *myGame,GameWindow *buttons[],bool onLoadScreen) {
 AsciiString lowerMap=myGame->getMap(); ((StringBase<char> &)(lowerMap)).toLower();
 MapCache::iterator it=TheMapCache->find(lowerMap);
 if(it==TheMapCache->end()) {
  for(int i=0;i<8;++i) {
   buttons[i]->winHide(true);
   GadgetButtonSetText(buttons[i],TheGameText->fetch("GUI:Blank"));
  }
  return;
 }
 MapMetaData mmd=it->second;
 for(int i=0;i<8;++i) {
  GadgetButtonSetText(buttons[i],UnicodeString::TheEmptyString);
  if(!onLoadScreen) buttons[i]->winSetTooltip(TheGameText->fetch("TOOLTIP:StartPosition"));
 }
 for(i=0;i<8;++i) {
  GameSlot *gs=myGame->getSlot(i);
  if(onLoadScreen) {
   if(gs->getApparentStartPos()>=0 && gs->getApparentStartPos()<mmd.m_numPlayers && gs->getPlayerTemplate()>-2) {
    AsciiString displayNumber; displayNumber.format("NUMBER:%d",i+1);
    GadgetButtonSetText(buttons[gs->getApparentStartPos()],TheGameText->fetch(displayNumber));
   }
  } else {
   if(gs->getStartPos()>=0 && gs->getStartPos()<mmd.m_numPlayers && gs->getPlayerTemplate()>-2) {
    AsciiString displayNumber; displayNumber.format("NUMBER:%d",i+1);
    GadgetButtonSetText(buttons[gs->getStartPos()],TheGameText->fetch(displayNumber));
    UnicodeString temp;
    temp.format(TheGameText->fetchPtr("TOOLTIP:StartPositionN"),i+1);
    buttons[gs->getStartPos()]->winSetTooltip(temp);
   } else if(gs->getStartPos()>=mmd.m_numPlayers) gs->setStartPos(-1);
  }
 }
}
