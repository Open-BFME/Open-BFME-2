// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C3A3FSet@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003C3A3F 58B (dump range 18).
// Trigger-area int setter: copies the name through the rowed StringBase
// copy ctor, resolves the area through rowed ScriptEngine 0x0035768D
// getQualifiedTriggerAreaByName, and applies the pinned 0x002872BA
// (area, value, 0) member on the manager global when both are non-null.
#include "ascii_string.h"

typedef bool Bool;

class PolygonTrigger;
class Rva002872BA
{
public:
	void rva002872BA(void *p, int a, int b);
};
extern Rva002872BA *TheTriggerManager;

// LINK: 0x002872BA is rowed as FireLogicSystem::rva002872BA(PolygonTrigger const*, int, bool) (FireLogicSystem rows); the old
// (void*, int, int) call shape is kept through a member-pointer cast.
class FireLogicSystem
{
public:
	void rva002872BA(const PolygonTrigger *p, int a, bool b);
};
typedef void (FireLogicSystem::*FireLogicSystemWordShape)(void *, int, int);

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C3A3FSet(const AsciiString &name, int v)
{
	PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(name);
	if (trig == 0)
		return;
	Rva002872BA *m = TheTriggerManager;
	if (m == 0)
		return;
	(((FireLogicSystem *)m)->*reinterpret_cast<FireLogicSystemWordShape>(&FireLogicSystem::rva002872BA))(trig, v, 0);
}
