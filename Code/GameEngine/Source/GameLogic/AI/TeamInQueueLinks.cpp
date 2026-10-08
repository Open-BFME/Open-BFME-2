// cl: /DNDEBUG /MD
//
// TeamInQueue's MAKE_DLINK members for TeamBuildQueue and TeamReadyQueue
// (Zero Hour's GameEngine/Include/Common/GameCommon.h, GeneralsMD tree vendored
// under reference/open-bfme-1/inputs/reference), kept out of line by retail
// and called from the AIPlayer queue members (AIPlayerTeamQueues.cpp):
//  - dlink_isInList_TeamBuildQueue 0x004F0341 (26 bytes) and
//    dlink_isInList_TeamReadyQueue 0x004EF342 (26 bytes);
//  - dlink_removeFrom_TeamBuildQueue 0x004F0372 (48 bytes) and
//    dlink_removeFrom_TeamReadyQueue 0x004F03AF (48 bytes, defined in
//    TeamInQueueBuildPredicates.cpp).
// Layout (target evidence): build-queue links (prev, next) at +0x04 / +0x08,
// ready-queue links at +0x0C / +0x10.
typedef bool Bool;
#define NULL 0

class TeamInQueue
{
public:
	TeamInQueue *dlink_prev_TeamBuildQueue() const { return m_dlink_TeamBuildQueue.m_prev; }
	TeamInQueue *dlink_next_TeamBuildQueue() const { return m_dlink_TeamBuildQueue.m_next; }
	void dlink_swapLinks_TeamBuildQueue()
	{
		TeamInQueue *originalNext = m_dlink_TeamBuildQueue.m_next;
		m_dlink_TeamBuildQueue.m_next = m_dlink_TeamBuildQueue.m_prev;
		m_dlink_TeamBuildQueue.m_prev = originalNext;
	}
	Bool dlink_isInList_TeamBuildQueue(TeamInQueue *const *pListHead) const;
	void dlink_prependTo_TeamBuildQueue(TeamInQueue **pListHead);
	void dlink_removeFrom_TeamBuildQueue(TeamInQueue **pListHead);

	Bool dlink_isInList_TeamReadyQueue(TeamInQueue *const *pListHead) const;
	void dlink_removeFrom_TeamReadyQueue(TeamInQueue **pListHead);
private:
	struct DLINK
	{
		TeamInQueue *m_prev;
		TeamInQueue *m_next;
	};
	void *m_vtbl;
	DLINK m_dlink_TeamBuildQueue; // +0x04
	DLINK m_dlink_TeamReadyQueue; // +0x0C
};

// ------------------------------------------------------------------------------------------------
Bool TeamInQueue::dlink_isInList_TeamBuildQueue(TeamInQueue *const *pListHead) const
{
	return *pListHead == this || m_dlink_TeamBuildQueue.m_prev || m_dlink_TeamBuildQueue.m_next;
}

void TeamInQueue::dlink_removeFrom_TeamBuildQueue(TeamInQueue **pListHead)
{
	if (m_dlink_TeamBuildQueue.m_next)
		m_dlink_TeamBuildQueue.m_next->m_dlink_TeamBuildQueue.m_prev = m_dlink_TeamBuildQueue.m_prev;
	if (m_dlink_TeamBuildQueue.m_prev)
		m_dlink_TeamBuildQueue.m_prev->m_dlink_TeamBuildQueue.m_next = m_dlink_TeamBuildQueue.m_next;
	else
		*pListHead = m_dlink_TeamBuildQueue.m_next;
	m_dlink_TeamBuildQueue.m_prev = 0;
	m_dlink_TeamBuildQueue.m_next = 0;
}

Bool TeamInQueue::dlink_isInList_TeamReadyQueue(TeamInQueue *const *pListHead) const
{
	return *pListHead == this || m_dlink_TeamReadyQueue.m_prev || m_dlink_TeamReadyQueue.m_next;
}

// Native-neighbor home suggested by repair_queue dest: 4F03A2 ends at
// this file's existing 4F03AF queue helper; 4F0334 ends at existing4F0341.
// This organization does not establish that the address-owned carriers below
// are TeamInQueue or that their raw words are links. Those identities remain
// unknown; each carrier states only its independently witnessed accesses.
// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705
// game/GameEngine/Source/Common/R2SmallMemberOps.cpp /O1 /arch:SSE /G7
// supplies the high-first pair swap expression. Target independently proves
// each complete RET-bounded leaf: 4F0334..4F0341 exchanges raw32 +4/+8;
// 4F03A2..4F03AF exchanges raw32 +C/+10. Each reads high then low, writes
// high then low, and has an ECX receiver with no stack arguments or calls.
// Unsigned carriers describe only raw32 access. Original classes, field
// meanings, signedness and any relationship between these owners are unknown.
class Rva004F0334WordSwap
{
public:
    void swap();
private:
    char leading[4];
    unsigned low;
    unsigned high;
};
void Rva004F0334WordSwap::swap()
{
    unsigned held = high;
    high = low;
    low = held;
}

class Rva004F03A2WordSwap
{
public:
    void swap();
private:
    char leading[0xC];
    unsigned low;
    unsigned high;
};
void Rva004F03A2WordSwap::swap()
{
    unsigned held = high;
    high = low;
    low = held;
}
