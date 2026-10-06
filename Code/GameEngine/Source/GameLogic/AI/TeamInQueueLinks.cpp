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
