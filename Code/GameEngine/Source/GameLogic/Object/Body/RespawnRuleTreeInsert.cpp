// cl: /O1 /DNDEBUG /MD

// ?insert@BFME2RespawnRuleTree@@QAE?AURespawnInsertResult@@ABURespawnRule@@@Z,
// retail 0x004AFB2B, 35 bytes. Hidden-result wrapper: runs the tree's unique
// insertion worker into a stack result, then copies the node pointer and the
// freshness flag out to the hidden return slot.

struct RespawnRule;
struct RespawnInsertResult
{
	void *m_node;
	bool m_fresh;

	RespawnInsertResult() {}
	RespawnInsertResult(const RespawnInsertResult &other)
	{
		m_node = other.m_node;
		m_fresh = other.m_fresh;
	}
};

class BFME2RespawnRuleTree
{
public:
	RespawnInsertResult insert(const RespawnRule &rule);
	RespawnInsertResult *insertUnique(RespawnInsertResult *out, const RespawnRule &rule);
};

// ?insert@BFME2RespawnRuleTree@@QAE?AURespawnInsertResult@@ABURespawnRule@@@Z
RespawnInsertResult BFME2RespawnRuleTree::insert(const RespawnRule &rule)
{
	RespawnInsertResult result;
	insertUnique(&result, rule);
	return result;
}
