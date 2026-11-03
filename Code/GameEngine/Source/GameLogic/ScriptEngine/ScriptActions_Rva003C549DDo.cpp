// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C549DDo@ScriptActions@@QAEXVAsciiString@@ABV2@@Z @0x003C549D 152B
// Byte twin of Rva003C5405Do (ScriptActions_garrison.cpp, same evidence) with the
// countdown flag set: the timer's internal name is the script-resolved name
// (resolveName 0x002046C0) plus '/' plus the timer name, the label is fetched
// through TheGameText slot 0x38, and InGameUI::addNamedTimer 0x002A5A50 adds a
// countdown timer.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &s);
};

#include "../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C549DDo(AsciiString timerName, const AsciiString &label)
{
	AsciiString tmp = ((Rva002046C0Owner *)TheScriptEngine)->resolveName(timerName);
	tmp += '/';
	tmp += timerName;
	TheInGameUI->addNamedTimer(tmp, TheGameText->fetch(label), true);
}
