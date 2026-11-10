// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?getUnitNamed@ScriptEngine@@QAEPAVObject@@PAVParameter@@@Z
// Retail 0x003588E7, 76 bytes.
//
// Target identity: ScriptEngine::getUnitNamed taking Parameter* at slot 26
// vtable+0x68. BFME1 ScriptConditionsCanBuildAtBase spells this slot taking
// Parameter* while ZH Scripts.h gives the Parameter layout with string at
// +0x10. Target reads ObjectID at Parameter+0x24 for findObjectByID at
// 0x49DC5 then string at +0x10 for isEmpty and by-value lookupUnitByValue
// at 0x358752. 40+ script callers pass Parameter* through this slot.
//

// The ScriptActions doNamed* views call this through a BFME 1-style
// getUnitNamed(const AsciiString &) spelling pinned to this address. Their
// dispatcher (e.g. 0x003CBD8C) passes the Parameter* from getParameter
// straight through, so the pointer they forward is this function's Parameter*
// and the two spellings share one ABI. Bind theirs here until those views are
// retyped.
#pragma comment(linker, "/alternatename:?getUnitNamed@ScriptEngine@@QAEPAVObject@@ABVAsciiString@@@Z=?getUnitNamed@ScriptEngine@@QAEPAVObject@@PAVParameter@@@Z")
#include "ascii_string.h"


class Object;
#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;


#include "../../../Include/GameLogic/ScriptParameter.h"

#include "../../../Include/GameLogic/Rva00358752Opaque.h"

#include "../../../Include/GameLogic/ScriptEngine.h"

Object *ScriptEngine::getUnitNamed(Parameter *unitName)
{
    ObjectID id = (ObjectID)unitName->m_objectID;
    if (id != INVALID_OBJECT_ID) {
        Object *o = TheGameLogic->findObjectByID(id);
        if (o)
            return o;
    }
    const AsciiString &s = unitName->getString();
    if (s.isEmpty())
        return 0;
    return ((Rva00358752Opaque *)this)->lookupUnitByValue(s);
}
