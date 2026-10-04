// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE2 /O1
// ?evaluateTeamInsideAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z
// @0x003E5E7D 130B. ZH/BFME1 donor body (some inside or all inside), same
// shape as the matched evaluateTeamInsideAreaEntirely sibling; Team methods
// someInsideSomeOutside 0x0039E50D and allInside 0x0039E3C8 are rowed.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class PolygonTrigger;
class Team { public: bool someInsideSomeOutside(PolygonTrigger *, unsigned int); bool allInside(PolygonTrigger *, unsigned int); };
class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, bool);
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{ protected: bool evaluateTeamInsideAreaPartially(Parameter *, Parameter *, Parameter *); };
bool ScriptConditions::evaluateTeamInsideAreaPartially(Parameter *teamParm, Parameter *triggerParm, Parameter *typeParm)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(triggerParm->getString());
    if (trigger == 0) return false;
    if (team) return (team->someInsideSomeOutside(trigger, (unsigned int)typeParm->m_int) ||
                      team->allInside(trigger, (unsigned int)typeParm->m_int));
    return false;
}
