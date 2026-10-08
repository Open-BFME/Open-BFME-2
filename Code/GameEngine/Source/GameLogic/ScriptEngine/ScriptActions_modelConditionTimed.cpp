// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// WB 0x0100D3E0 unnamed ScriptActions member, retail 0x003C596A (150B): find
// the model-condition flag a script names (the 591 ModelConditionNames at
// 0x00DBAA98) and set it on the named unit for a time given in seconds,
// converted to logic frames (Object 0x002949AE, WorldBuilder's
// BitFlags<591>::SetBit caller in Object.cpp). Built without /arch:SSE: the
// seconds-to-frames product goes through x87 and _ftol2 in retail.

#include "ascii_string.h"

extern const char *const ModelConditionNames[];
extern const int g_009BA4E4;	// logic frames per second

class Object
{
public:
	void rva002949AE(int flag, int frames, float value);
};

class ScriptEngine
{
public:
	Object *getUnitNamed(const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void rva003C596A(const AsciiString &unitName, const AsciiString &flagName,
		float seconds, float value);
};

void ScriptActions::rva003C596A(const AsciiString &unitName, const AsciiString &flagName,
	float seconds, float value)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj)
		return;
	int flag = -1;
	int frames = 0;
	bool found = false;
	for (int i = 0; i < 591; ++i) {
		AsciiString name(ModelConditionNames[i]);
		if (flagName.compare(name) == 0) {
			flag = i;
			found = true;
			frames = (int)(g_009BA4E4 * seconds);
			break;
		}
	}
	if (found)
		obj->rva002949AE(flag, frames, value);
}
