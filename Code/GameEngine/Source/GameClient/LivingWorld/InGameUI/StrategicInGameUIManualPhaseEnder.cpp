// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::ManualPhaseEnder (WorldBuilder
// StrategicInGameUIManualPhaseEnder.cpp). Target facts for Translate
// 0x005CD8F7 (thiscall, ret 4): on message type 0x16, unless TheInGameUI's
// vslot 95 holds, when the message's first argument byte is 0x39 it ends
// the phase (0x005CD8A5, WorldBuilder OnEndPhase) and consumes the message.
// Called by the strategic phase behaviors' translateGameMessage.

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

union GameMessageArgumentType
{
	int integer;
	unsigned char byteValue;
};

#include "../../../../Include/Common/MessageStream.h"

// TheInGameUI viewed by slot: vslot 95 (+0x17C) returns a bool.
#include "../../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

#include "../../../../Include/GameLogic/ManualPhaseEnder.h"
namespace StrategicInGameUI
{
}

GameMessageDisposition StrategicInGameUI::ManualPhaseEnder::Translate(const GameMessage *msg)
{
	if (msg->getType() == 0x16 && !TheInGameUI->slot95() && msg->getArgument(0)->byteValue == 0x39)
	{
		OnEndPhase();
		return DESTROY_MESSAGE;
	}
	return KEEP_MESSAGE;
}

#include "../../../../Include/Common/Rva0042D6AEPtrChaseField.h"
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
#include "../../../../Include/Common/DelegateDesc.h"
inline DelegateDesc phaseDelegate(StrategicInGameUI::ManualPhaseEnder *object, void (StrategicInGameUI::ManualPhaseEnder::*method)()) { DelegateDesc result(object,method);return result; }
class Rva00579E47 {
public:
 Rva00579E47(const DelegateDesc &);
 ~Rva00579E47() { if(ptr) ReleaseTreeHintRef00217D4C(ptr); }
 TargetRef00217D4C *ptr;
};
class ManualPhaseButton {
public:
 virtual void slot0();
 virtual void slot1(bool);
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5(const Rva00579E47 &);
};
struct ManualPhaseView {
 char unknown0[4]; Rva0042D6AEPtrChaseField *hud;
 char unknown8[4]; bool registered;
};
// Native5CD938..5CD9AE and WB15B63A0 identify Update: obtain the end-phase
// button from the HUD at+4, bind OnEndPhase once, show it and set flag+C.
// Returning the two-word delegate descriptor by value preserves the native
// pointer-to-member materialization. Its counted wrapper dies before Show.
void StrategicInGameUI::ManualPhaseEnder::Update() {
 ManualPhaseView *state=(ManualPhaseView *)this;
 if(!state->registered) {
  ManualPhaseButton *button=(ManualPhaseButton *)state->hud->get();
  if(button) {
   {
    DelegateDesc desc=phaseDelegate(this,&ManualPhaseEnder::OnEndPhase);
    Rva00579E47 callback(desc);
    button->slot5(callback);
   }
   button->slot1(true);
   state->registered=true;
  }
 }
}

class Rva005CCBB0 {
public:
 void rva005CCBC0();
 void rva005CCBB0();
};
bool __cdecl hasListeners(void *);
void __cdecl Rva005CD877Visit(void *);
void __cdecl Rva005CD813Visit(void *);
class ManualPhaseEndHook {public:virtual void invoke();};
struct ManualPhaseEndView {
 ManualPhaseEndHook *hook;
 void *hud;
 Rva005CCBB0 *listeners;
};
// Native5CD8A5..5CD8F7 (82B), WB15B64E0 OnEndPhase. The fallback
// restores ESI and tail-dispatches slot0; it is a complete function boundary.
// Listener helper names remain the separately verified opaque owners.
void StrategicInGameUI::ManualPhaseEnder::OnEndPhase()
{
 if(TheInGameUI->slot95())return;
 ManualPhaseEndView *state=(ManualPhaseEndView*)this;
 if(state->listeners && hasListeners(state->listeners)) {
  state->listeners->rva005CCBC0();
  state->listeners->rva005CCBB0();
  Rva005CD877Visit(state->listeners);
  Rva005CD813Visit(state->listeners);
 }else state->hook->invoke();
}
