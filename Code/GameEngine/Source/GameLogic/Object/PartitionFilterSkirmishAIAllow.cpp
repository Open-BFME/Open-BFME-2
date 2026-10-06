// cl: /O1 /EHsc /MD /arch:SSE
// PartitionFilterSkirmishAI::Allow, retail 0x00261535 (55B), from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function, its
// callee and asserts m_searcherAI; retail supplies the bytes.
//
// PartitionFilterSkirmishAI (target layout): the searching object at +0x08
// and its skirmish AI at +0x0C, whose tactical AI is at +0x164. Only a
// searcher in AI state 0x21 (the attack-move state; the getter 0x00260DED is
// rowed under a placeholder name) consults the tactical AI. Reading the
// searcher's AI twice (folded by cl) is what keeps this in esi and the
// searcher in edi as retail does; TacticalAI::checkEnemyForAttackMove
// (0x002C600A, WB callgraph name) is pinned.

typedef bool Bool;
typedef int Int;

class AIUpdateInterface
{
public:
	Int rva00260DED() const;			// 0x00260DED, current state id
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai;			// +0x258
};

class TacticalAI
{
public:
	Bool checkEnemyForAttackMove(Object *searcher, Object *enemy);	// 0x002C600A
};

class SkirmishAI
{
public:
	unsigned char m_pad000[0x164];
	TacticalAI *m_tacticalAI;			// +0x164
};

enum { AI_STATE_ATTACK_MOVE = 0x21 };

class PartitionFilterSkirmishAI
{
public:
	virtual Bool Allow(Object *objOther);

private:
	unsigned char m_pad04[4];
	Object *m_searcher;				// +0x08
	SkirmishAI *m_searcherAI;			// +0x0C (WB member name)
};

// PartitionFilterSkirmishAI::Allow, retail 0x00261535.
Bool PartitionFilterSkirmishAI::Allow(Object *objOther)
{
	Object *searcher = m_searcher;
	if (searcher->getAIUpdateInterface() && searcher->getAIUpdateInterface()->rva00260DED() == AI_STATE_ATTACK_MOVE)
	{
		TacticalAI *tactical = m_searcherAI->m_tacticalAI;
		return tactical->checkEnemyForAttackMove(searcher, objOther);
	}
	return false;
}
