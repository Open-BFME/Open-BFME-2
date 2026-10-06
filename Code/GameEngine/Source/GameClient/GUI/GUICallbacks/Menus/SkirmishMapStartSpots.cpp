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
class MapMetaData {
public: char unknown00[0x20]; int m_numPlayers; char unknown24[0x100-0x24];
 MapMetaData(const MapMetaData&); ~MapMetaData();
};
class MapCache:public _STL::map<AsciiString,MapMetaData> {};
typedef char MapMetaDataSizeCheck[sizeof(MapMetaData)==0x100?1:-1];
extern MapCache *TheMapCache;
class GameSlot {
public:
 int getApparentStartPos() const;
 int getStartPos() const {return m_startPos;}
 int getPlayerTemplate() const {return m_playerTemplate;}
 void setStartPos(int n) {m_startPos=n;}
private: char unknown00[0x10]; int m_startPos; char unknown14[4];int m_playerTemplate;
};
class GameInfo {
public: AsciiString getMap() const; GameSlot *getSlot(int);
};
class GameWindow {
public: int winHide(bool); void rva003148A2(UnicodeString);
};
void GadgetButtonSetText(GameWindow*,UnicodeString);
class GameTextInterface {
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02();
 virtual void slot03(); virtual void slot04(); virtual void slot05();
 virtual void slot06(); virtual void slot07(); virtual void slot08();
 virtual void slot09(); virtual void slot10(); virtual void slot11();
 virtual void slot12(); virtual void slot13();
 virtual UnicodeString fetch(const char*,bool* =0);
 virtual UnicodeString fetch(const AsciiString&,bool* =0);
 virtual void slot16();
 // Target slot44 returns a borrowed UnicodeString pointer used by format.
 // Original spelling and ownership beyond the observed borrow remain unknown.
 virtual const UnicodeString* rvaSlot44(const char*,bool* =0);
};
extern GameTextInterface *TheGameText;
void updateMapStartSpots(GameInfo *myGame,GameWindow *buttons[],bool onLoadScreen) {
 AsciiString lowerMap=myGame->getMap(); lowerMap.toLower();
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
  if(!onLoadScreen) buttons[i]->rva003148A2(TheGameText->fetch("TOOLTIP:StartPosition"));
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
    temp.format(TheGameText->rvaSlot44("TOOLTIP:StartPositionN"),i+1);
    buttons[gs->getStartPos()]->rva003148A2(temp);
   } else if(gs->getStartPos()>=mmd.m_numPlayers) gs->setStartPos(-1);
  }
 }
}
