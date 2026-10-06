// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003E859E@ScriptConditions@@IAE_NPAVParameter@@0@Z @0x003E859E 66B.
// Target evidence: the evaluateCondition jump table (0x007EC5C0) sends case
// 143 here, and initConditionTemplates gives template 143 the internal name
// TEAM_HAS_CUSTOM_STATE (case 11, TEAM_STATE_IS, goes to 0x003E9471). This row
// was first landed as evaluateTeamStateIs from the ZH donor shape; that name
// was wrong. BFME2-only condition with no donor method name, so the method
// keeps an address name. It asks a Team method (0x003A3717, a lookup in the
// +0x48 container, address-named and pinned from this sole call site).
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class Team
{
public:
    bool rva003A3717(const AsciiString &stateName);
};
class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, bool);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool rva003E859E(Parameter *, Parameter *);
};
bool ScriptConditions::rva003E859E(Parameter *teamParm, Parameter *stateParm)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    if (!team)
        return false;
    return team->rva003A3717(stateParm->getString()) ? true : false;
}
