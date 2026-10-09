// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// BF1 f98983a7d CastleBehaviorIsPlayerAllowedToCapture.cpp guides the
// algorithm; target's CAMP string proves the method name. Original class
// spelling remains uncertain, so the receiver is address-qualified.
// Native397EAC..397F45 RET8: owner8, Player name4C, template name64,
// ID74 and logic frame40 are target facts. Target has no override walk or
// logic-level log guard. The second input is carried as an opaque ABI word.
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern "C" int __cdecl fprintf(void *,const char *,...);
extern "C" void *theLogicRandomLogFile;
class Player { public: char pad[0x4C]; AsciiString name; };
class ThingTemplate { public: char pad[0x64]; AsciiString name; };
class Object {
public:
 Player *getControllingPlayer() const;
 void *vtable; ThingTemplate *type;
 char pad8[0x74-8]; int id;
};
extern GameLogic *TheGameLogic;
class Rva003973EB { public: bool rva003973EB(Player *,int); };
class Rva00397EAC {
public:
 bool isPlayerAllowedToCapture(Player *,int);
 void *vtable; const void *data; Object *owner;
};
bool Rva00397EAC::isPlayerAllowedToCapture(Player *player,int arg)
{
 Object *object=owner;
 bool alreadyMyCastle = player == object->getControllingPlayer();
 union DecisionWord { bool allowed; int alignmentWord; } decision;
 decision.allowed = reinterpret_cast<Rva003973EB *>(this)->rva003973EB(player,arg);
 if (theLogicRandomLogFile) {
  const char *callerName=object->getControllingPlayer()->name.str();
  int id=object->id;
  const char *castleName=object->type->name.str();
  fprintf(theLogicRandomLogFile,
   "CAMP: Frame %d: Castle %s(%d) ::isPlayerAllowedToCapture() called by %s -- alreadyMyCastle=%d, playerAllowedToCapture=%d",
   TheGameLogic->getFrame(),castleName,id,callerName,alreadyMyCastle,decision.allowed);
 }
 return decision.allowed & (signed char)(alreadyMyCastle ? 0 : -1);
}
