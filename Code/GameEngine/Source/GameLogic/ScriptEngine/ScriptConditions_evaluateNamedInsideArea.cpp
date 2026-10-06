// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ScriptConditions::evaluateNamedInsideArea, target 0x003E5EFF (116 bytes).
// Identity: target retrieves the named unit and trigger, converts the unit's
// three position coordinates to ints, then calls the trigger point test.

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

class Object
{
public:
    const float *getPosition() const
    {
        return (const float *)((const char *)this + 0x38);
    }
};

class ICoord3D
{
public:
    int x, y, z;
};

class PolygonTrigger
{
public:
    Bool pointInTrigger(const ICoord3D &position);
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
    Bool evaluateNamedInsideArea(Parameter *, Parameter *);
};


Bool ScriptConditions::evaluateNamedInsideArea(
    Parameter *unitParm, Parameter *triggerParm)
{
    Object *object = TheScriptEngine->getUnitNamed(unitParm);
    if (!object)
        return false;

    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(
        triggerParm->getString());
    if (!trigger)
        return false;

    const float *sourcePosition = object->getPosition();
    float pCoord[3] = { sourcePosition[0], sourcePosition[1], sourcePosition[2] };
    ICoord3D position;
    position.x = (int)pCoord[0];
    position.y = (int)pCoord[1];
    position.z = (int)pCoord[2];
    return trigger->pointInTrigger(position);
}
