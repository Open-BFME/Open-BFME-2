// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD /Oy-
// Native 003BCB7A..003BCBC7 RET0C. BFME1 donor 7dff0a4a9e937818d2731f9861ade1815663b9db,
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp,
// ScriptActions::doAddCommandBarButton supplies the semantic lead. Target
// agrees on named factory/control-bar lookups and override call, with a
// 32-slot limit and command-set string at template+70 (donor: 20 and +2C).
// Retain an address-derived stdcall name: the unused receiver does not by
// itself establish the action's original owner/name.
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"
class ThingFactory;
extern ThingFactory *TheThingFactory;
class Rva002D06CA
{
public:
 void *rva002D06CA(const AsciiString *name);
};
class CommandButton;
class ControlBar
{
public:
 const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;
extern GameLogic *TheGameLogic;
class Rva0024792FHelper
{
public:
 void rva0024792F(const AsciiString &commandSet, int slot, const CommandButton *button);
};

void __stdcall Rva003BCB7A(const AsciiString &buttonName, const AsciiString &objectType, int slot)
{
 void *subject = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&objectType);
 if (subject == 0) return;
 const CommandButton *button = TheControlBar->findCommandButton(buttonName);
 if (button == 0) return;
 --slot;
 if (slot < 0 || slot >= 32) return;
 ((Rva0024792FHelper *)TheGameLogic)->rva0024792F(*(const AsciiString *)((const char *)subject + 0x70), slot, button);
}
