// ?positionStartSpots@@YAXPAVGameInfo@@PAPAVGameWindow@@PAV2@2@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// ZH/BF1 positionStartSpots GameInfo wrapper, adapted from verified native
// 00304259..003042DD. Flag +11 and virtual +34 are target layout evidence.
//
// The fourth argument is target-specific: this overload forwards a GameWindow*
// at [ebp+0x14] to the callee at 0x00303ED4, which the retail REL32 at
// 0x003042BD reads directly. That callee is a 901-byte body with no ledger row,
// so it is bound through an address-derived pin rather than a named provider.
// Its own body calls rowed GadgetListBoxReset 0x003247E5 and
// GadgetListBoxAddEntryText 0x00326BEC, which is what supports reading the
// forwarded pointer as the map-description listbox; that callee's application
// element identity is NOT claimed here, only the argument it receives.
//
// The body otherwise matches all 132 retail bytes exactly; the sole open item
// before the pin was the unresolved REL32 above.
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
