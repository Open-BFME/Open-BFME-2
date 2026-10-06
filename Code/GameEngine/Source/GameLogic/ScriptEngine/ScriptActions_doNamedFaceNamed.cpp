// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Target identity: action-template index 0x133 is NAMED_FACE_NAMED and
// executeAction case 0x133 calls VA 0x007C99C1 (RVA 0x003C99C1), 99 bytes.
// The body resolves a named unit, resolves a second by-value name through the
// address-derived ScriptEngine helper at 0x358752, validates AIUpdateInterface
// at Object+0x258, clears its waypoint queue, leaves the unit's group, then
// calls aiFaceObject with source 1. BFME1 donor maps that operation to
// doNamedFaceNamed. The second resolver remains deliberately opaque.

#include "ascii_string.h"

class Object;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };
class ScriptEngine
{
public:
    Object *getUnitNamed(const AsciiString &);
};
class Rva00358752Opaque
{
public:
    Object *lookupUnitByValue(AsciiString);
};
class AICommandInterface
{
public:
    void aiFaceObject(Object *, CommandSourceType);
};
class AIUpdateInterface
{
public:
    char pad[0x20];
    AICommandInterface command;
    void clearWaypointQueue();
};
class Object
{
public:
    void leaveGroup();
    AIUpdateInterface *aiUpdate() const
    {
        return *(AIUpdateInterface **)((const char *)this + 0x258);
    }
};
class ScriptActions
{
protected:
    void doNamedFaceNamed(const AsciiString &, const AsciiString &);
};
extern ScriptEngine *TheScriptEngine;

void ScriptActions::doNamedFaceNamed(const AsciiString &unitName,
    const AsciiString &faceUnitName)
{
    Object *unit = TheScriptEngine->getUnitNamed(unitName);
    if (!unit) return;
    Object *faceUnit = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(
        (AsciiString &)faceUnitName);
    if (!faceUnit) return;
    AIUpdateInterface *ai = unit->aiUpdate();
    if (!ai) return;
    ai->clearWaypointQueue();
    unit->leaveGroup();
    ai->command.aiFaceObject(faceUnit, CMD_FROM_SCRIPT);
}
