// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -ICode/GameEngine/Include -DNDEBUG -MD /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "Code/GameEngine/Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C35AADo@@YGXPBVAsciiString@@PAX_N@Z @0x003C35AA 77B (dump range 18).
// Trigger-area wiring: team-name copy, rowed ScriptEngine
// getQualifiedTriggerAreaByName, pinned 0x0052E3E6 member on the
// 0x00DFF0F8+0x10 object, flag gate, then the pinned ScriptEngine
// 0x00209811 member. All callees rowed/pinned; identities unproven.
#include "ascii_string.h"

class PolygonTrigger;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class Pathfinder
{
public:
	void rva0052E3E6(PolygonTrigger *a, bool b);
};

struct Rva00DFF0F8Obj
{
	char m_pad[0x10];
	Pathfinder *m_pathfinder;
};
extern class AI *TheAI;

void ScriptActions::Rva003C35AADo(const AsciiString *teamName, bool x, bool flag)
{
	PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(*teamName);
	if (trigger == 0)
		return;
	((Rva00DFF0F8Obj *)TheAI)->m_pathfinder->rva0052E3E6(trigger, x);
	if (flag != 0)
		return;
	TheScriptEngine->rva00209811(*teamName, x);
}

// 0x003C35F7 (18B), a vtable slot right after 0x003C35AA: 0x003C35AA on the
// same this with both arguments and true. Its owner is not recovered, so the
// call goes through a member pointer that keeps the slot's two dwords.
class Rva003C35F7
{
public:
	void rva003C35F7(int a, int b);
};

void Rva003C35F7::rva003C35F7(int a, int b)
{
	(reinterpret_cast<ScriptActions *>(this)->*reinterpret_cast<void (ScriptActions::*)(int, int, bool)>(
		&ScriptActions::Rva003C35AADo))(a, b, true);
}
