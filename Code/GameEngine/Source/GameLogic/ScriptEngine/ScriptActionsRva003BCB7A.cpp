// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -MD -Oy- -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// Native 003BCB7A..003BCBC7 RET0C. BFME1 donor 7dff0a4a9e937818d2731f9861ade1815663b9db,
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp,
// ScriptActions::doAddCommandBarButton supplies the semantic lead. Target
// agrees on named factory/control-bar lookups and override call, with a
// 32-slot limit and command-set string at template+70 (donor: 20 and +2C).
// Retain an address-derived stdcall name: the unused receiver does not by
// itself establish the action's original owner/name.
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"
class ThingTemplate;
class ThingFactory;
extern ThingFactory *TheThingFactory;
#include "../../../Include/Common/ThingFactory.h"
class CommandButton;
#include "../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;
extern GameLogic *TheGameLogic;

void ScriptActions::Rva003BCB7A(const AsciiString &buttonName, const AsciiString &objectType, int slot)
{
 void *subject = (void *)TheThingFactory->findTemplate(objectType);
 if (subject == 0) return;
 const CommandButton *button = TheControlBar->findCommandButton(buttonName);
 if (button == 0) return;
 --slot;
 if (slot < 0 || slot >= 32) return;
 TheGameLogic->setControlBarOverride(*(const AsciiString *)((const char *)subject + 0x70), slot, button);
}
