// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BFME1 donor: ScriptConditionsTriggerAreas.cpp.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class PolygonTrigger;
class Team { public: bool allInside(PolygonTrigger *, unsigned int); };
class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, bool);
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{ protected: bool evaluateTeamInsideAreaEntirely(Parameter *, Parameter *, Parameter *); };
bool ScriptConditions::evaluateTeamInsideAreaEntirely(Parameter *teamParm, Parameter *triggerParm, Parameter *typeParm)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(triggerParm->getString());
    if (trigger == 0) return false;
    if (team) return team->allInside(trigger, (unsigned int)typeParm->m_int);
    return false;
}
