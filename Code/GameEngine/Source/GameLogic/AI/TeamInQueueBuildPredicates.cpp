// cl: /O1 /Ob0
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/AI/TeamInQueueBuildPredicates.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: TeamInQueue::isMinimumBuilt 0x004F06A6 (39B),
// TeamInQueue::areBuildsComplete 0x004F06CD (24B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Retail BFME1 TeamInQueue work-order checks. Identity evidence:
// targets/game/reverse/identity_evidence/0x00160f80-team-in-queue-build-predicates.md.
// The retail queue has a vptr at +0, four link pointers at +4..+0x10,
// and the work-order head at +0x14. The native Zero Hour member names
// are retained, while offsets below are witnessed by the retail methods.

struct WorkOrder
{
	char m_unreconstructed_00[8];
	unsigned int m_factoryID;     // +0x08
	WorkOrder *m_next;             // +0x0C
	int m_numCompleted;            // +0x10
	int m_numRequired;             // +0x14
	bool m_required;               // +0x18
};

class TeamInQueue
{
public:
	virtual ~TeamInQueue();
	bool isAllBuilt();
	bool isMinimumBuilt();
	bool areBuildsComplete();
	void dlink_removeFrom_TeamReadyQueue(TeamInQueue **head);

private:
	TeamInQueue *m_previousBuild; // +04
	TeamInQueue *m_nextBuild; // +08
	TeamInQueue *m_previousReady; // +0C
	TeamInQueue *m_nextReady; // +10
	WorkOrder *m_workOrders;       // +0x14
};


// ?isMinimumBuilt@TeamInQueue@@QAE_NXZ
bool TeamInQueue::isMinimumBuilt()
{
	for (WorkOrder *order = m_workOrders; order; order = order->m_next)
	{
		int count = order->m_numCompleted;
		if (order->m_factoryID != 0)
			++count;
		if (order->m_numRequired > count && order->m_required)
			return false;
	}
	return true;
}

// ?areBuildsComplete@TeamInQueue@@QAE_NXZ
bool TeamInQueue::areBuildsComplete()
{
	WorkOrder *order = m_workOrders;
	while (order)
	{
		if (order->m_factoryID != 0)
			return false;
		order = order->m_next;
	}
	return true;
}

// Whole BFME1 AIPlayerQueueTeardown.cpp at1281192f682ce6f29b8f06b7daea4b5e8fdfbb24
// supplies the two-list unlink protocol. Native Ghidra4F03AF/48 RET4
// independently witnesses next+10 and previous+0C, neighbour repairs,
// the supplied-head store only when previous is null, and both clears.
// Native4F0479/32 checks rowed4EF342 with AIPlayer+8, then calls this
// entry with the same node/head arguments. The Ready/Build labels come
// from the reference DLINK declaration order; target bytes prove offsets
// and relationships, not the original spelling or the full class layout.
// Existing work-order methods continue to read the unchanged pointer+14.
void TeamInQueue::dlink_removeFrom_TeamReadyQueue(TeamInQueue **head)
{
    if (m_nextReady)
        m_nextReady->m_previousReady = m_previousReady;
    if (m_previousReady)
        m_previousReady->m_nextReady = m_nextReady;
    else
        *head = m_nextReady;
    m_previousReady = 0;
    m_nextReady = 0;
}

// Whole BFME1 AIPlayerQueueTeardown.cpp and actual AIPlayer.cpp@1281192
// supply the queue-delete protocol. BFME2 native4F05D8 explicitly loads
// callback4F05C0 for both drain loops. Previous getter RET4F05BF, full
// callback RET4F05D5 and next Ghidra entry4F05D6/26 prove this22B
// address-taken boundary omitted by the function inventory.
// Known target vtable C62B78 slot0 is rowed deleting destructor4EF606:
// calls4F05F0, frees only when flags&1, then returns its receiver.
// Global-qualified delete reproduces native flags0 followed by global
// operator delete2FD60; ordinary delete uses flags1 and is not exact.
// That global provider independently byte-verifies and links in mem_ops.
// Reuse the existing TeamInQueue view and virtual destructor declaration;
// the original callback spelling and complete class layout remain unknown.
void rva004F05C0(TeamInQueue *entry)
{
    if (entry)
        ::delete entry;
}
