// cl: /O1 /DNDEBUG /MD
//
// Condition and ScriptAction destructors (0x003B4230, 0x003B43CC; 92B each),
// ported from the Zero Hour donor (GameLogic/ScriptEngine/Scripts.cpp). Each
// installs its own vftable (0x00C1F3F8, 0x00C1F3FC) and is the callee of its
// slot-0 scalar deleting destructor (0x003B4A78, 0x003B53F7); the names are
// the pins those carry (Condition's dtor is protected: MAE).
//
// The parameter array at +0x0C (count +0x08) is cleared through the rowed
// address-named Parameter destructor 0x000B9AAA and operator delete; the
// chain at +0x3C is unlinked one element at a time, as the donor does to stop
// recursion. Retail frees each chain element with flag 0 to its slot-0
// deleting destructor and passes the returned block to operator delete: the
// global-scope ::delete through a virtual destructor, where the donor calls
// deleteInstance.
//
// Target facts: offsets, vftables, callees and the ::delete shape come from
// the retail bytes. Carried from the donor: the names and field meanings.

class Rva000B9AAA
{
public:
	~Rva000B9AAA();
};

class Condition
{
protected:
	virtual ~Condition();

private:
	int m_conditionType;		// +0x04
	int m_numParms;				// +0x08
	Rva000B9AAA *m_parms[12];	// +0x0C
	Condition *m_nextAndCondition;	// +0x3C
};

Condition::~Condition()
{
	int i;
	for (i = 0; i < m_numParms; i++)
	{
		if (m_parms[i])
			delete m_parms[i];
		m_parms[i] = 0;
	}
	Condition *cur = m_nextAndCondition;
	while (cur)
	{
		Condition *next = cur->m_nextAndCondition;
		cur->m_nextAndCondition = 0;
		::delete cur;
		cur = next;
	}
}

class ScriptAction
{
public:
	virtual ~ScriptAction();

private:
	int m_actionType;			// +0x04
	int m_numParms;				// +0x08
	Rva000B9AAA *m_parms[12];	// +0x0C
	ScriptAction *m_nextAction;	// +0x3C
};

ScriptAction::~ScriptAction()
{
	int i;
	for (i = 0; i < m_numParms; i++)
	{
		if (m_parms[i])
			delete m_parms[i];
		m_parms[i] = 0;
	}
	ScriptAction *cur = m_nextAction;
	while (cur)
	{
		ScriptAction *next = cur->m_nextAction;
		cur->m_nextAction = 0;
		::delete cur;
		cur = next;
	}
}
