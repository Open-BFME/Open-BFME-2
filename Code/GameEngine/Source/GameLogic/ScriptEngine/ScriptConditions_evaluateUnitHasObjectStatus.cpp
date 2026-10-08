// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateUnitHasObjectStatus@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E5AE9 40B. BFME1 donor ScriptConditions.cpp evaluateUnitHasObjectStatus;
// BFME2 getUnitNamed takes the Parameter (matched 0x003588E7) and asks the
// rowed Object::testStatus 0x0004E536 with the parameter's int.
#include "ascii_string.h"
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
class Parameter
{
public:
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class Object
{
public:
    bool testStatus(ObjectStatusTypes status) const;
};
class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *parameter);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateUnitHasObjectStatus(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateUnitHasObjectStatus(Parameter *unitParm, Parameter *statusParm)
{
    Object *object = TheScriptEngine->getUnitNamed(unitParm);
    if (!object)
        return false;
    return object->testStatus((ObjectStatusTypes)statusParm->m_int);
}
