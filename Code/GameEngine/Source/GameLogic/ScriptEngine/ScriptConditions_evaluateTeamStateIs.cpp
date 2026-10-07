// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateTeamStateIs and
// evaluateTeamStateIsNot. Target evidence: the evaluateCondition jump table
// (0x007EC5C0) sends cases 11 and 12 to 0x003E9471 and 0x003E94E5, which
// initConditionTemplates names TEAM_STATE_IS and TEAM_STATE_IS_NOT; both
// compare the team state string at +0x44 with a copied parameter string via
// the rowed StringBase<char>::compare 0x000069D6.
// The shared AsciiString compare declaration is nonthrowing: retail stores
// no EH state for the copied name around the comparison. Its existing ABI
// spelling resolves directly to the verified StringBase worker.

//
// ?evaluateHasUnits@ScriptConditions@@IAE_NPAVParameter@@@Z @ 0x003E9373 254B
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateHasUnits, verbatim.
// Target evidence: the jump table sends case 10 to 0x003E9373, which
// initConditionTemplates names TEAM_HAS_UNITS; the body compares the
// "<This Team>" literal (0x0081531C) with the rowed compare 0x000069B1,
// resolves teams with the rowed getTeamNamed 0x003584E9 and reads the
// prototype name through Team+0x30 / TeamPrototype+0x14 with the
// TheEmptyString fallback, as ZH's Team::getName does. 0x0039DEC4 (rowed
// rva0039DEC4@Team) is ZH's Team::hasAnyUnits by its body: it skips dead,
// destroyed, structure, projectile and mine members. 0x003A2659 is ZH's
// one-argument TeamFactory::findTeamPrototype: it splits the qualified name
// and forwards to the two-argument findTeamPrototype 0x0039FE6C. The instance
// walk loads the member pointer 0x009C4AF5 (DLINK_ITERATOR<Team>).
#include "ascii_string.h"

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
	unsigned char m_afterString[8];
};

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

#include "Common/Snapshot.h"

class Team;

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const;
private:
	unsigned char m_pad00[0x14];
	AsciiString m_name; // +0x14
	unsigned char m_pad18[0x334 - 0x18];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	const AsciiString &getState() const { return m_state; }
	const AsciiString &getName() const
	{
		return m_proto == NULL ? AsciiString::TheEmptyString : m_proto->getName();
	}
	// Zero Hour's Team::hasAnyUnits; the ledger keeps the address name.
	bool rva0039DEC4();
	Team *dlink_next_TeamInstanceList() const;
private:
	unsigned char m_pad08[0x30 - 0x08];
	TeamPrototype *m_proto; // +0x30
	unsigned char m_pad34[0x44 - 0x34];
	AsciiString m_state; // +0x44
};

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
{
	return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
}

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
};
extern ScriptEngine *TheScriptEngine;

#define THIS_TEAM "<This Team>"

class ScriptConditions
{
protected:
	bool evaluateHasUnits(Parameter *);
	bool evaluateTeamStateIs(Parameter *, Parameter *);
	bool evaluateTeamStateIsNot(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateHasUnits(Parameter *pTeamParm)
{
	AsciiString desiredTeamName = pTeamParm->getString();
	// If they are calling a <this team> condition, do it.
	if (desiredTeamName.compare(THIS_TEAM) == 0) {
		Team *theTeam = TheScriptEngine->getTeamNamed(desiredTeamName, false);
		if (theTeam) {
			return (theTeam->rva0039DEC4());
		}
		return false;
	}
	Team *thisTeam = TheScriptEngine->getTeamNamed(THIS_TEAM, false);
	if (thisTeam && thisTeam->getName() == desiredTeamName) {
		return thisTeam->rva0039DEC4();
	}

	TeamPrototype *pProto = NULL;
	pProto = TheTeamFactory->findTeamPrototype(desiredTeamName);

	if (pProto) {
		for (DLINK_ITERATOR<Team> iter = pProto->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			if (iter.cur()->rva0039DEC4()) {
				return true;
			}
		}
	}
	return false;
}
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
