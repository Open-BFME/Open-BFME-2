// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateTeamStateIs and
// evaluateTeamStateIsNot. Target evidence: the evaluateCondition jump table
// (0x007EC5C0) sends cases 11 and 12 to 0x003E9471 and 0x003E94E5, which
// initConditionTemplates names TEAM_STATE_IS and TEAM_STATE_IS_NOT; both
// compare the team state string at +0x44 with a copied parameter string via
// the rowed StringBase<char>::compare 0x000069D6.
// The shared AsciiString compare declaration is nonthrowing: retail stores
// no EH state for the copied name around the comparison. Its existing ABI
// spelling resolves directly to the verified StringBase worker.

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
	const AsciiString &getState() const { return m_state; }
	unsigned char m_pad00[0x44];
	AsciiString m_state;
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
	bool evaluateTeamStateIs(Parameter *, Parameter *);
	bool evaluateTeamStateIsNot(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateTeamStateIs(Parameter *pTeamParm, Parameter *pStateParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	AsciiString stateName = pStateParm->getString();
	if (theTeam) {
		return (theTeam->getState() == stateName);
	}
	return false;
}
bool ScriptConditions::evaluateTeamStateIsNot(Parameter *pTeamParm, Parameter *pStateParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	AsciiString stateName = pStateParm->getString();
	if (theTeam) {
		return (!(theTeam->getState() == stateName));
	}
	return false;
}
