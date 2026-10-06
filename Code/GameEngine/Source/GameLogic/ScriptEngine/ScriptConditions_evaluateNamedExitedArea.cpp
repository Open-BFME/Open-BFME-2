// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateNamedExitedArea@ScriptConditions@@IAE_NPAVParameter@@0@Z @0x003E6D60 74B.
// ZH donor ScriptConditions.cpp in donor order; BFME2 getUnitNamed takes the
// Parameter (matched 0x003588E7); Object::didEnter/didExit
// are pinned. Same style as the matched evaluateNamedInsideArea sibling.
typedef bool Bool;
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8];
    int m_int;
    float m_real;
    AsciiString m_string;
    unsigned char m_afterString[8];
    unsigned int m_objectId;
};
class PolygonTrigger;
class ThingTemplate
{
public:
    unsigned char m_pad[0x113];
    unsigned char m_kindOf113; // KindOf bits; 0x02 here is the inert flag
};
class Object
{
public:
    Bool isKindOfInert() const { return (m_template->m_kindOf113 & 0x02) != 0; }
    Bool didEnter(PolygonTrigger *trigger);
    Bool didExit(PolygonTrigger *trigger);
private:
    void *m_vtbl;
    ThingTemplate *m_template; // +0x04
};
class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *parameter);
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    Bool evaluateNamedExitedArea(Parameter *, Parameter *);
};
Bool ScriptConditions::evaluateNamedExitedArea(Parameter *unitParm, Parameter *triggerParm)
{
    Object *unit = TheScriptEngine->getUnitNamed(unitParm);
    if (!unit)
        return false;
    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(triggerParm->getString());
    if (!trigger)
        return false;
    return unit->didExit(trigger);
}
