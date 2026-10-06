// cl: /Oi /DNDEBUG /MD
// ??0Condition@@QAE@XZ 0x003B26DF 48B
// Evidence: vtable 0x81F3F8 (Condition sibling of ScriptAction 0x81F3FC);
// zero type/parms/next, rep-stosd parms (/Oi), trailing ints and flags;
// caller 0x003B6D92.
#include <string.h>

typedef bool Bool;
typedef int Int;

enum { MAX_PARMS = 12 };

class Parameter
{
};

class MemoryPool;

class Condition
{
protected:
	virtual ~Condition();
private:
	virtual MemoryPool *getObjectMemoryPool();
public:
	enum ConditionType { CONDITION_FALSE = 0 };
	Condition();
	Condition(ConditionType type);
	void setConditionType(ConditionType type);

private:
	Int m_conditionType;
	Int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	Condition *m_nextCondition;
	Int m_x40;
	Int m_x44;
	Int m_x48;
	Bool m_flag4C;
	unsigned char m_b4D;
	char m_pad[2];
};

Condition::Condition() :
	m_conditionType(0),
	m_numParms(0),
	m_nextCondition(0),
	m_x40(0),
	m_x44(0),
	m_x48(0),
	m_flag4C(true),
	m_b4D(0)
{
	memset(m_parms, 0, sizeof(m_parms));
}

Condition::Condition(ConditionType type) :
	m_conditionType(type),
	m_numParms(0),
	m_nextCondition(0),
	m_x40(0),
	m_x44(0),
	m_x48(0),
	m_flag4C(true),
	m_b4D(0)
{
	memset(m_parms, 0, sizeof(m_parms));
	setConditionType(type);
}
