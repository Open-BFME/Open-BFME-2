// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ScriptEngine::executeScript, retail 0x00209E15 (606B; ret 8).
//
// Identity (target): the WorldBuilder twin 0xB3C1D0 (callgraph match 1.0)
// has the same callees in the same order. It saves and restores the
// condition-team field, iterates the condition team's instances with
// TeamPrototype::iterate_TeamInstanceList (named in WB), and calls
// evaluateConditions 0x00209748, the cdecl _appendMessage 0x002053FA with
// (true, false) / (false, false), and executeActions 0x0020C5C7. Retail reads
// the callees at their REL32s: the condition-team-name getter 0x002041E1
// (Script+0x44), resolveName 0x002046C0, the two-argument
// TeamFactory::findTeamPrototype 0x0039FE6C on TheTeamFactory,
// countTeamInstances 0x0039D954, the path join 0x0032B389 and the
// DLINK_ITERATOR<Team> member pointer 0x005C4AF5.
// +0x1A118 is m_conditionTeam: notifyOfTeamDestruction 0x002051B7 clears it
// beside m_callingTeam at +0x1A110, as Zero Hour's does.
// Donor: Zero Hour ScriptEngine.cpp executeScript, both branches and the
// one-shot deactivation. BFME2 drops the curTime, isActive, difficulty and
// frame-to-evaluate gates (evaluateAndProgressAllSequentialScripts' caller
// applies them). It also passes the script and its name through
// evaluateConditions/executeActions, and logs the scope-qualified name.
// The getter keeps Zero Hour's name getConditionTeamName by that donor
// shape, and its setter 0x002041FC is the address-named method beside it.
#include "ascii_string.h"
#include "string_base.h"

// Retail registers no unwind state for the getter temporary across this
// call (0x00209E40), which only a non-throwing declaration reproduces.
template <> bool StringBase<char>::isEmpty() const throw();

class ScriptEngine;
class Script;
class ScriptAction;
class Player;
class Team;

void _appendMessage(const AsciiString &str, bool isTrueMessage, bool msgOnly);
AsciiString Rva0032B389Join(const AsciiString &a, const AsciiString &b);

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

class ScriptEngine
{
public:
	bool evaluateConditions(Script *pScript, Team *thisTeam, Player *player);
	AsciiString rva002046C0(const AsciiString &name);	// 0x002046C0, resolveName
	void executeScript(Script *pScript, const AsciiString &name);

protected:
	void executeActions(ScriptAction *pActionHead, void *a, void *b);

private:
	char m_unknown0[0x1A10C];
	AsciiString m_currentScope;		// +0x1A10C
	char m_unknown1A110[0x1A118 - 0x1A110];
	Team *m_conditionTeam;			// +0x1A118
};

class Script
{
public:
	AsciiString getConditionTeamName() const;
	ScriptAction *getAction() { return m_action; }
	ScriptAction *getFalseAction() { return m_actionFalse; }
	bool isOneShot() { return m_isOneShot; }
	void deactivate() { m_isActive = false; }

private:
	char m_unknown0[0x29];
	bool m_isOneShot;				// +0x29
	char m_unknown2A[0x34 - 0x2A];
	ScriptAction *m_action;			// +0x34
	ScriptAction *m_actionFalse;	// +0x38
	char m_unknown3C[0x40 - 0x3C];
	bool m_isActive;				// +0x40
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

#include "Common/Snapshot.h"

class TeamPrototype
{
public:
	int countTeamInstances();
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const;
private:
	unsigned char m_pad00[0x334];
	Team *m_dlinkhead_TeamInstanceList;	// +0x334
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
};

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
{
	return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
}

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &name, const AsciiString &qualifiedName);
};
extern TeamFactory *TheTeamFactory;

void ScriptEngine::executeScript(Script *pScript, const AsciiString &name)
{
	Team *pSavConditionTeam = m_conditionTeam;
	TeamPrototype *pProto = NULL;

	if (!((const StringBase<char> &)pScript->getConditionTeamName()).isEmpty()) {
		AsciiString teamName = pScript->getConditionTeamName();
		AsciiString scopedName = rva002046C0(teamName);
		pProto = TheTeamFactory->findTeamPrototype(scopedName, teamName);
	}

	if (pProto && pProto->countTeamInstances() > 0) {
		for (DLINK_ITERATOR<Team> iter = pProto->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			m_conditionTeam = iter.cur();
			if (evaluateConditions(pScript, NULL, NULL)) {
				if (pScript->getAction()) {
					_appendMessage(Rva0032B389Join(m_currentScope, name), true, false);
					executeActions(pScript->getAction(), pScript, (void *)&name);
				}
				if (pScript->isOneShot())
					pScript->deactivate();
			} else if (pScript->getFalseAction()) {
				_appendMessage(Rva0032B389Join(m_currentScope, name), false, false);
				executeActions(pScript->getFalseAction(), pScript, (void *)&name);
			}
		}
	} else {
		m_conditionTeam = NULL;
		if (evaluateConditions(pScript, NULL, NULL)) {
			if (pScript->getAction()) {
				_appendMessage(Rva0032B389Join(m_currentScope, name), true, false);
				executeActions(pScript->getAction(), pScript, (void *)&name);
			}
			if (pScript->isOneShot())
				pScript->deactivate();
		} else if (pScript->getFalseAction()) {
			_appendMessage(Rva0032B389Join(m_currentScope, name), false, false);
			executeActions(pScript->getFalseAction(), pScript, (void *)&name);
			if (pScript->isOneShot())
				pScript->deactivate();
		}
	}
	m_conditionTeam = pSavConditionTeam;
}
