// cl: /Oi /DNDEBUG /MD
// ??0Condition@@QAE@XZ 0x003B26DF 48B
// Evidence: vtable 0x81F3F8 (Condition sibling of ScriptAction 0x81F3FC);
// zero type/parms/next, rep-stosd parms (/Oi), trailing ints and flags;
// caller 0x003B6D92. Retail vftable 0x81F3F8 has only the deleting
// destructor; the next word belongs to ScriptAction's separate vftable.
#include <string.h>

typedef bool Bool;
typedef int Int;

enum { MAX_PARMS = 12 };

#include "../../../Include/GameLogic/ScriptParameter.h"

#include "../../../Include/GameLogic/ScriptCondition.h"

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
