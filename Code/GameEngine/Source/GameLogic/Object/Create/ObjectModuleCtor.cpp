// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ??0ObjectModule@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x00306AA7
// (106B). Dedicated TU (the caller BehaviorModule 0x253330 lives in
// CreateModule.cpp, so this body cannot live there without capturing its
// call locally).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/Thing/Module.cpp,
// retained as an unrowed definition there): base Module init plus a null-moduleData
// throw plus m_object = AsObject(thing). Three BFME2 deltas:
//  - Module is slim single-inheritance here (retail stores only one vptr and
//    makes no base call), so the TU carries a TU-local Module view (4-byte
//    m_moduleData, visible inline ctor, declare-only dtor for EH tracking;
//    funclet relocs are out-of-range-skipped per the ModuleDataCtor idiom).
//  - `throw INI_INVALID_DATA` is the INIException filler idiom (explicit
//    cdecl filler call plus direct noreturn _CxxThrowException, sibling
//    getNextToken template): filler pin 0x2F681, throw pin 0x629094, message
//    "module data may not be null\n" byte-read from retail rdata.
//  - DEBUG_ASSERTCRASH vanishes in NDEBUG; AsObject stays as the
//    null-guarded ternary over Thing slot 8 (asObjectMeth, BFME1 name).

class ModuleData;
class Object;
class Player;
typedef int Bool;

class Thing
{
public:
	virtual void opaqueSlot0(); // slot 0 (unproven)
	virtual void opaqueSlot4(); // slot 4 (unproven)
	virtual Object *asObjectMeth(); // slot 8 (BFME1 name, position from retail)
};

#include "../../../../Include/Common/Module.h"

#include "../../../../Include/Common/ObjectModule.h"

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};


// ??0ObjectModule@@QAE@PAVThing@@PBVModuleData@@@Z
ObjectModule::ObjectModule(Thing *thing, const ModuleData *moduleData)
	: Module(moduleData)
{
	if (!moduleData) {
		throw INIException(3, "module data may not be null\n");
	}
	m_object = thing ? thing->asObjectMeth() : 0;
}
