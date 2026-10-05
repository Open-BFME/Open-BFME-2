// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// ?Rva003C3A3FSet@@YGXABVAsciiString@@H@Z @0x003C3A3F 58B (dump range 18).
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

class ScriptEngine
{
public:
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003C3A3FSet(const AsciiString &name, int v)
{
	PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(name);
	if (trig == 0)
		return;
	Rva002872BA *m = TheTriggerManager;
	if (m == 0)
		return;
	m->rva002872BA(trig, v, 0);
}
