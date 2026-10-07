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

class Rva00261C89
{
public:
    bool rva00261C89();
};

class Object
{
public:
    Rva00261C89 *getValue04() const { return m_value04; }
    const float *getPosition() const
    {
        return m_position;
    }
private:
    char m_pad00[4];
    Rva00261C89 *m_value04;
    char m_pad08[0x30];
    float m_position[3];
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

// Native 0x003E6032..0x003E609F is a cdecl callback returning full EAX.
// Object positions agree with the named-area sibling at +0x38/+0x3C/+0x40.
// The context contains a point, squared-distance limit, counter and maximum.
// Its original callback and context names remain unknown.
struct Rva003E6032Context
{
    float point[3];
    float limit0C;
    int count10;
    int maximum14;
};

int Rva003E6032(Object *object, Rva003E6032Context *context)
{
    Rva00261C89 *value = object->getValue04();
    if (value && value->rva00261C89())
    {
        const float *position = object->getPosition();
        float dx = position[0] - context->point[0];
        float dy = position[1] - context->point[1];
        float dz = position[2] - context->point[2];
        float distanceSquared = dz*dz + dy*dy + dx*dx;
        if (distanceSquared > context->limit0C)
        {
            ++context->count10;
            if (context->count10 > context->maximum14)
                return 0;
        }
    }
    return 1;
}
