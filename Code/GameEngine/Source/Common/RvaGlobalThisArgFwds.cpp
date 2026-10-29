// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG
// Global-this forwards that pass their own stack arguments straight through:
// mov ecx, [global]; jmp <method>. Same shape as the parameterless forwards
// in RvaGlobalThisFwds.cpp and the 0x00203688 host forward, with the callee
// reusing the caller's arguments in place. The forwarding classes are not
// recovered (address-derived views); the callees are the rows at the jump
// targets.
//  - 0x003BC577: TheScriptEngine -> rva0035818E(const AsciiString &, Coord3D *)
//  - 0x003BC9D5: TheScriptEngine -> doObjectTypeListMaintenance(name, type, add)
#include "ascii_string.h"

struct Coord3D;

#include "../../Include/GameLogic/ScriptEngine.h"

extern ScriptEngine *TheScriptEngine;

class Rva003BC577
{
public:
	void rva003BC577(const AsciiString &name, Coord3D *pos);
};

void Rva003BC577::rva003BC577(const AsciiString &name, Coord3D *pos)
{
	TheScriptEngine->rva0035818E(name, pos);
}

class Rva003BC9D5
{
public:
	void rva003BC9D5(const AsciiString &listName, const AsciiString &objectType, bool addObject);
};

void Rva003BC9D5::rva003BC9D5(const AsciiString &listName, const AsciiString &objectType, bool addObject)
{
	TheScriptEngine->doObjectTypeListMaintenance(listName, objectType, addObject);
}
