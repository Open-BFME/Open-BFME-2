// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateSkirmishPlayerIsOutsideArea@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1@Z
// @0x003E79AF 70B. BFME1 donor ScriptConditions.cpp without the player
// preflight (BFME2 only checks the trigger), then the negation of
// evaluateSkirmishPlayerHasUnitsInArea 0x003E782D (pinned from this call).
#include "ascii_string.h"
class Condition;
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class PolygonTrigger;
class ScriptEngine
{
public:
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateSkirmishPlayerHasUnitsInArea(Condition *, Parameter *, Parameter *);
    bool evaluateSkirmishPlayerIsOutsideArea(Condition *, Parameter *, Parameter *);
};
bool ScriptConditions::evaluateSkirmishPlayerIsOutsideArea(Condition *condition, Parameter *skirmishPlayerParm, Parameter *triggerParm)
{
    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(triggerParm->getString());
    if (!trigger)
        return false;
    return !evaluateSkirmishPlayerHasUnitsInArea(condition, skirmishPlayerParm, triggerParm);
}
