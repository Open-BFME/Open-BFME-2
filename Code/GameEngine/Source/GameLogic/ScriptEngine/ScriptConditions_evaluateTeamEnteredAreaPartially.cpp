// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateTeamEnteredAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z
// @0x003E6E0C.
// Donor: ZH ScriptConditions.cpp evaluateTeamEnteredAreaPartially; unlike the
// matched evaluateTeamInsideAreaEntirely sibling, retail tests the team
// before looking up the trigger, in donor order. TheScriptEngine is the
// global at 0x00DFE16C; getTeamNamed 0x003584E9, trigger lookup 0x0035768D,
// Team::didPartialEnter 0x0039E15D.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class PolygonTrigger;
class Team { public: bool didPartialEnter(PolygonTrigger *, unsigned int); };
class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, bool);
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{ protected: bool evaluateTeamEnteredAreaPartially(Parameter *, Parameter *, Parameter *); };
bool ScriptConditions::evaluateTeamEnteredAreaPartially(Parameter *teamParm, Parameter *triggerParm, Parameter *typeParm)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    if (!team)
        return false;
    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(triggerParm->getString());
    if (trigger)
        return team->didPartialEnter(trigger, (unsigned int)typeParm->m_int);
    return false;
}
