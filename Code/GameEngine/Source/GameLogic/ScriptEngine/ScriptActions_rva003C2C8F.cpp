// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C2C8FDo@ScriptActions@@QAEXPAVParameter@@0@Z @0x003C2C8F 73B
// Script set counter from unit's ExperienceTracker float at Object+0x264 inner +0x10.
// Evidence: rowed getUnitNamed 0x003588E7 via g_Va009FE16C, pin bfmeCounter 0x0020874B
// by value via StringBase copy 0x000365F0 temp, cvttss2si float to int, ret 8 stdcall,
// callers 0x003CE1AF, neighbours Rva003C2A29 0x003C2A29 Rva003C2E61 0x003C2E61.
#include "ascii_string.h"

class Parameter
{
public:
	char m_pad[0x10];
	AsciiString m_string;
};

class ExperienceTracker
{
public:
	char m_pad[0x10];
	float m_10;
};

class Object
{
public:
	char m_pad[0x264];
	ExperienceTracker *m_264;
};

struct ScriptCounter
{
	int m_value;
};

#include "../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C2C8FDo(Parameter *parameter, Parameter *b)
{
	Object *obj = TheScriptEngine->getUnitNamed(parameter);
	if (obj == 0)
		return;
	ExperienceTracker *tracker = obj->m_264;
	if (tracker == 0)
		return;
	ScriptCounter *counter = TheScriptEngine->bfmeCounter(b->m_string);
	counter->m_value = (int)tracker->m_10;
}
