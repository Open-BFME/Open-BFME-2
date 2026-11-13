// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C5535Do@ScriptActions@@QAEXVAsciiString@@@Z @0x003C5535 113B
// Sibling of Rva003C5405Do (ScriptActions_garrison.cpp, same evidence): the
// timer's internal name is the script-resolved name (ScriptEngine
// resolveName 0x002046C0) plus '/' plus the timer name; TheInGameUI's
// 0x002A44D5 member (class Rva002A44D5 in the ledger) then takes that name, as
// addNamedTimer 0x002A5A50 does for Rva003C5405Do. Zero Hour's counterpart
// removes a named timer from the display.
#include "ascii_string.h"

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &s);
};

#include "../../../Include/Common/Rva002A44D5.h"

class InGameUI;
extern InGameUI *TheInGameUI;

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C5535Do(AsciiString timerName)
{
	AsciiString tmp = ((Rva002046C0Owner *)TheScriptEngine)->resolveName(timerName);
	tmp += '/';
	tmp += timerName;
	((Rva002A44D5 *)TheInGameUI)->rva002A44D5(tmp);
}
