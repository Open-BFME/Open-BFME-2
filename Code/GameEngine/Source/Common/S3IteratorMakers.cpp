// Two iterator makers (trimmed from a four-maker donor; the other two are
// declared-only here).
//
// Each returns an eight-byte record through a hidden pointer. The record is
// built by a constructor in the return expression so the compiler writes
// through the return slot directly.

// BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 repaired the
// S3IteratorMakers donor's false data owners as code addresses. Target facts:
// the second words at4EF622 and4F07D3 are the rowed next-link getter bodies
// 30F45F (+8) and1DB09D (+10). AIPlayerTeamBuild.cpp independently identifies
// both as TeamInQueue build/ready getters through the target queue walks.
// Callable declarations only: no fields, instances or function bodies are
// used here. The real rowed providers remain owners of both implementations.
class TeamInQueue
{
public:
    virtual ~TeamInQueue();
    TeamInQueue *dlink_next_TeamBuildQueue() const;
    TeamInQueue *dlink_next_TeamReadyQueue() const;
};
typedef TeamInQueue *(TeamInQueue::*BfmeNextLink)() const;

struct BfmeIterator
{
	BfmeIterator(void *node, void *owner)
	{
		m_bfmeNode = node;
		m_bfmeOwner = owner;
	}

    BfmeIterator(void *node, BfmeNextLink next)
    {
        m_bfmeNode = node;
        m_bfmeNext = next;
    }

    void *m_bfmeNode; // +0x00
    union
    {
        void *m_bfmeOwner; // opaque pointer-word variant at+4
        BfmeNextLink m_bfmeNext; // genuine callable variant at+4
    };
};


class Gen_000CBB80
{
public:
	BfmeIterator bfmeMake(void);
};


class Gen_00161290
{
public:
	BfmeIterator bfmeMake(void);

private:
	char m_bfmeHead[0x4];
	void *m_bfmeNode;					// +0x4
};


class Gen_001612B0
{
public:
	BfmeIterator bfmeMake(void);

private:
	char m_bfmeHead[0x8];
	void *m_bfmeNode;					// +0x8
};

class Gen_004C14F0
{
public:
	BfmeIterator bfmeMake(void);
};

// ?bfmeMake@Gen_00161290@@QAE?AUBfmeIterator@@XZ
BfmeIterator Gen_00161290::bfmeMake(void)
{
	return BfmeIterator(m_bfmeNode, &TeamInQueue::dlink_next_TeamBuildQueue);
}

// ?bfmeMake@Gen_001612B0@@QAE?AUBfmeIterator@@XZ
BfmeIterator Gen_001612B0::bfmeMake(void)
{
	return BfmeIterator(m_bfmeNode, &TeamInQueue::dlink_next_TeamReadyQueue);
}

// The same clean donor supplies its fourth pair-return expression. Target
// independently proves2DF9BF..2DF9CD, afterRET8 at2DF9BC and before the
// next constructor: ECX receiver, raw pointer-word load at0, hidden output
// pointer at[esp+4], stores this then the loaded word, andRET4. The original
// owner, record type and purpose are unknown. BfmeIterator is retained only
// as the donor's eight-byte pair carrier; no iterator identity is asserted.
class Rva002DF9BFPairOwner
{
public:
    BfmeIterator make();
private:
    void *first;
};
BfmeIterator Rva002DF9BFPairOwner::make()
{
    return BfmeIterator(this, first);
}
