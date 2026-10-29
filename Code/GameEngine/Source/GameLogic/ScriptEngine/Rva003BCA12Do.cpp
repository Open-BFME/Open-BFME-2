// stlport
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?Rva003BCA12Do@ScriptActions@@QAEXABVAsciiString@@00@Z @0x003BCA12 49B: script creates BfmeStringRecord via rva00358853 with 0.0f and 1 then doNamedMapReveal same name. Evidence: push 1 fldz push [esp+0xc] push ecx mov ecx,[0x00DFE16C]=g_Va009FE16C fstp [esp] push [esp+0x10] push [esp+0x1c] call rva00358853 then push [esp+0xc] mov ecx g_Va call doNamedMapReveal ret 0xc; callees rowed; caller 0x003CD6E3; sibling Rva003BC123Do same AsciiString stdcall shape.
#include "ascii_string.h"
struct BfmeStringRecord00204A30;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
void ScriptActions::Rva003BCA12Do(const AsciiString &text0, const AsciiString &text1, const AsciiString &name)
{
	TheScriptEngine->createNamedMapReveal(name, text0, 0.0f, text1, 1);
	TheScriptEngine->doNamedMapReveal(name);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
