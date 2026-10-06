// cl: /DNDEBUG /MD /EHsc
//
// ScriptActions::doNamedSetRepulsor, retail 0x003BEEAE, 35 bytes.
// Target evidence: action template 0x1EB is NAMED_SET_REPULSOR and executeAction
// calls VA 0x007BEEAE; Ghidra boundary is 0x003BEEAE/35. Retail calls the
// named-object lookup at 0x003588E7, tests for null, then invokes the matched
// Object::setStatus at 0x0023DB0E with status mask 8 and the action flag.
// Donor facts: BFME1 ScriptActions.cpp maps this action to doNamedSetRepulsor,
// which resolves the named object and toggles OBJECT_STATUS_REPULSOR.

extern class ScriptEngine *TheScriptEngine;

class AsciiString;
class Object;

enum ObjectStatusTypes
{
    OBJECT_STATUS_REPULSOR = 8
};

class ScriptEngine
{
public:
    Object *getUnitNamed(const AsciiString &);
};

class Object
{
public:
    void setStatus(ObjectStatusTypes, bool);
};

class ScriptActions
{
protected:
    void doNamedSetRepulsor(const AsciiString &, bool);
};

void ScriptActions::doNamedSetRepulsor(const AsciiString &unitName, bool repulsor)
{
    ScriptEngine *scriptEngine = *(ScriptEngine **)&TheScriptEngine;
    Object *theSrcUnit = scriptEngine->getUnitNamed(unitName);
    if (!theSrcUnit) {
        return;
    }
    theSrcUnit->setStatus(OBJECT_STATUS_REPULSOR, repulsor);
}
