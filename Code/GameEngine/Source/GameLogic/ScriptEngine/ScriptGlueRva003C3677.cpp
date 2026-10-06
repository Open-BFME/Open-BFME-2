// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
//
// ?Rva003C3677Do@@YGXPAVParameter@@@Z @0x003C3677 73B (dump range 18).
// Object flag dispatch: string copy from param+0x10 (explicit arithmetic),
// object lookup through rowed lookupUnitByValue 0x00358752 (called through
// the Rva00358752Opaque view like landed doTeamEnterNamed), rowed GameLogic
// 0x0023D0B7 int gate, then the rowed GameLogic 0x0023D0C2 member with
// (object, int). Parameter/flag identities unproven.
#include "ascii_string.h"

class Parameter;
class Object;

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString s);
};

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

class GameLogic
{
public:
	int rva0023D0B7();
	void rva0023D0C2(Object *obj, int v);
};
extern GameLogic *TheGameLogic;

void __stdcall Rva003C3677Do(Parameter *param)
{
	Object *obj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(*(const AsciiString *)((const char *)param + 0x10));
	if (obj == 0)
		return;
	int v = TheGameLogic->rva0023D0B7();
	if (v == 0)
		return;
	TheGameLogic->rva0023D0C2(obj, v);
}
