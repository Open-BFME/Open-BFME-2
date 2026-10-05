// ?positionStartSpots@@YAXPAVGameInfo@@PAPAVGameWindow@@PAV2@2@Z
// partial score=0.99 date=2026-10-05
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// ZH/BF1 positionStartSpots GameInfo wrapper, adapted from verified native
// 00304259..003042DD. Flag +11 and virtual +34 are target layout evidence.
// Fourth arg is GameWindow*: native callee 00303ED4 resets it via the rowed
// GadgetListBoxReset 003247E5 and appends a localized map description via
// GadgetListBoxAddEntryText 00326BEC. The callee's provider remains unresolved.
#include "ascii_string.h"
class GameWindow;
class GameSlot {
public: bool hasMap() const {return m_hasMap;}
private: char unknown00[9]; bool m_hasMap;
};
class GameInfo {
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02();
 virtual void slot03(); virtual void slot04(); virtual void slot05();
 virtual void slot06(); virtual void slot07(); virtual void slot08();
 virtual void slot09(); virtual void slot10(); virtual void slot11();
 virtual void slot12(); virtual int getLocalSlotNum() const;
 AsciiString getMap() const;
 const GameSlot *getConstSlot(int) const;
 bool isGameInProgress() const {return m_gameInProgress;}
private: char unknown04[0x11-4]; bool m_gameInProgress;
};
void positionStartSpots(AsciiString,GameWindow **,GameWindow *,GameWindow *);
void positionStartSpots(GameInfo *myGame,GameWindow **buttons,GameWindow *mapWindow,GameWindow *extra) {
 AsciiString name=myGame->getMap();
 if (!myGame->isGameInProgress()) {
  int index=myGame->getLocalSlotNum();
  if (index==-1) name=AsciiString::TheEmptyString;
  else if (!myGame->getConstSlot(index)->hasMap()) name=AsciiString::TheEmptyString;
 }
 positionStartSpots(name,buttons,mapWindow,extra);
}
