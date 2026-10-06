// ?Rva003C2019Do@@YGXPBVAsciiString@@PAVParameter@@_N@Z
// partial score=0.92 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD
//
// ?Rva003C2019Do@@YGXPBVAsciiString@@PAX0@Z @0x003C2019 99B (dump range 18).
// Script name/object glue: when the flag is set, copies a string from
// param+0x10 (explicit arithmetic, matching the mov+add) and fires the
// pinned ScriptEngine 0x00208A09 member; otherwise resolves the object
// through rowed getUnitNamed and fires the rowed ScriptEngine 0x00208968
// and 0x0020A5FF members. Parameter/string/flag identities unproven.
#include "ascii_string.h"

class Parameter;
class Object;

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
	void rva00208A09(AsciiString copy, const AsciiString &name);
	void rva00208968(const AsciiString &name, Object *obj);
	void rva0020A5FF(Object *obj, const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003C2019Do(const AsciiString *name, Parameter *param, bool flag)
{
	if (flag != 0) {
		TheScriptEngine->rva00208A09(*(const AsciiString *)((const char *)param + 0x10), *name);
	} else {
		Object *obj = TheScriptEngine->getUnitNamed(param);
		if (obj == 0)
			return;
		TheScriptEngine->rva00208968(*name, obj);
		TheScriptEngine->rva0020A5FF(obj, *name);
	}
}
