// stlport
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?Rva003BCA43Do@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BCA43 26B: script undoNamedMapReveal then tail-jump rva00357D52 same name. Evidence: push [esp+4] mov ecx g_Va call undoNamedMapReveal mov ecx g_Va jmp rva00357D52; callees rowed; callers 0x003CD6B1 0x003CD6FB; sibling Rva003BCA12Do same AsciiString stdcall shape.
#include "ascii_string.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
void ScriptActions::Rva003BCA43Do(const AsciiString &name)
{
	TheScriptEngine->undoNamedMapReveal(name);
	TheScriptEngine->rva00357D52(name);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
