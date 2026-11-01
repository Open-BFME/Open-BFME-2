// cl: /DNDEBUG /MD

// ?insert@BFME2RespawnRuleTree@@QAE?AURespawnInsertResult@@ABURespawnRule@@@Z,
// retail 0x004AFB2B, 35 bytes. Hidden-result wrapper: runs the tree's unique
// insertion worker into a stack result, then copies the node pointer and the
// freshness flag out to the hidden return slot.

struct RespawnRule;
struct RespawnInsertResult
{
public:
	RespawnInsertResult() {}
	RespawnInsertResult(const RespawnInsertResult &other)
	{
		node = other.node;
		inserted = other.inserted;
	}
	void *node; // +0x00
	bool inserted; // +0x04
	char m_pad05[0x3];
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
