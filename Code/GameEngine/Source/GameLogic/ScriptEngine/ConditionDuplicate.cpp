// cl: /Oi /DNDEBUG /MD /EHsc
// ?duplicate@Condition@@QBEPAV1@XZ @0x003B5B07 157B chain from typed ctor 0x003B5AC7.
// Evidence: calls new 0x0002FDA0 typed ctor 0x003B5AC7 Rva assign 0x003B270F plus self recursion for next chain; pin exists; donor BFME1 Condition_duplicate.cpp run() const deep copy with both-bounds loop and flag copies.
typedef bool Bool;
typedef int Int;

enum { MAX_PARMS = 12 };

#include "../../../Include/GameLogic/ScriptParameter.h"

class MemoryPool;

#include "../../../Include/GameLogic/Rva0034FE00.h"

#include "../../../Include/GameLogic/ScriptCondition.h"

Condition *Condition::duplicate(void) const
{
	Condition *pNew = new Condition((ConditionType)m_conditionType);
	Int i;
	for (i = 0; i < m_numParms && i < pNew->m_numParms; i++) {
		*(Rva0034FE00 *)pNew->m_parms[i] = *(Rva0034FE00 *)m_parms[i];
	}
	pNew->m_nextCondition = m_nextCondition ? m_nextCondition->duplicate() : 0;
	pNew->m_flag4C = m_flag4C;
	pNew->m_b4D = m_b4D;
	return pNew;
}
