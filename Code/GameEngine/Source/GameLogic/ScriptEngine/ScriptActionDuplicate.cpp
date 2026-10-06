// cl: /Oi /DNDEBUG /MD /EHsc
// ?duplicate@ScriptAction@@QBEPAV1@XZ @0x003B5449 147B chain from typed ctor 0x003B5413.
// Evidence: calls new 0x0002FDA0 typed ctor 0x003B5413 Rva assign 0x003B270F plus self recursion for next chain; donor ZH Scripts.cpp ScriptAction::duplicate const deep copy with tailByte delta.
typedef bool Bool;
typedef int Int;

enum { MAX_PARMS = 12 };

class Parameter
{
};

class Rva0034FE00
{
public:
	Rva0034FE00 &operator=(const Rva0034FE00 &other);
};

class ScriptAction
{
public:
	enum ScriptActionType { NO_OP = 5 };
	virtual ~ScriptAction();
	ScriptAction(ScriptActionType type);
	ScriptAction *duplicate(void) const;

private:
	Int m_actionType;
	Int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	ScriptAction *m_nextAction;
	Bool m_hasWarnings;
	unsigned char m_tail;
	char m_pad[2];
	Int m_bfmeTail;
};

ScriptAction *ScriptAction::duplicate(void) const
{
	ScriptAction *pNew = new ScriptAction((ScriptActionType)m_actionType);
	Int i;
	for (i = 0; i < m_numParms; i++) {
		if (pNew->m_parms[i])
			*(Rva0034FE00 *)pNew->m_parms[i] = *(Rva0034FE00 *)m_parms[i];
	}
	pNew->m_nextAction = m_nextAction ? m_nextAction->duplicate() : 0;
	pNew->m_tail = m_tail;
	return pNew;
}
