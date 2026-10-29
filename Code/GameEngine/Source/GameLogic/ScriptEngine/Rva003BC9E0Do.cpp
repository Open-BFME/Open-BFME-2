// stlport
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?Rva003BC9E0Do@ScriptActions@@QAEXABVAsciiString@@M00@Z @0x003BC9E0 50B: script creates BfmeStringRecord via rva00358853 with param float and 0 then doNamedMapReveal same name. Evidence: sibling Rva003BCA12Do same shape with 0.0f and 1; callees rowed rva00358853 doNamedMapReveal; TheScriptEngine global; caller 0x003CD699 unclaimed.
#include "ascii_string.h"
struct BfmeStringRecord00204A30;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
void ScriptActions::Rva003BC9E0Do(const AsciiString &text0, float f, const AsciiString &text1, const AsciiString &name)
{
	TheScriptEngine->createNamedMapReveal(name, text0, f, text1, 0);
	TheScriptEngine->doNamedMapReveal(name);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
