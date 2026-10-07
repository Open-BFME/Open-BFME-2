// cl: /DNDEBUG /MD
//
// AIPlayer's team build / ready queues: Zero Hour's MAKE_DLINK_HEAD
// (AIPlayer) and MAKE_DLINK (TeamInQueue) members for TeamBuildQueue and
// TeamReadyQueue (GameEngine/Include/Common/GameCommon.h and
// GameLogic/AIPlayer.h, GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). Retail keeps these inlines out of
// line (target evidence: the call chains 0x004F042F -> 0x004F040F ->
// 0x004F0341 / 0x004F0372 and 0x004F0499 -> 0x004F0479 -> 0x004EF342 /
// 0x004F03AF):
//  - (the TeamInQueue link bodies are in TeamInQueueLinks.cpp: compiled in
//    this unit cl inlines them, retail calls them);
//  - AIPlayer::prependTo_TeamBuildQueue 0x004F03EF (32 bytes),
//    removeFrom_TeamBuildQueue 0x004F040F (32 bytes),
//    (removeAll_TeamBuildQueue 0x004F042F is in AIPlayer_Rva004F0499.cpp),
//    reverse_TeamBuildQueue 0x004F0456 (35 bytes),
//    removeFrom_TeamReadyQueue 0x004F0479 (32 bytes) and
//    removeAll_TeamReadyQueue 0x004F0499 (39 bytes).
// dlink_prependTo_TeamBuildQueue is the rowed byte-identical BFME 1 donor
// body 0x004F035B. Layout (target evidence): TeamInQueue's build-queue links
// (prev, next) at +0x04 / +0x08 and ready-queue links at +0x0C / +0x10;
// AIPlayer's heads at +0x04 (build) and +0x08 (ready).
//
// AIPlayer::aiPreTeamDestroy 0x004F0819 (143 bytes) is ZH's walk of both
// queues with DLINK_ITERATOR, deleting (virtual destructor, then the global
// operator delete) each entry whose team (+0x1C) is the dying one and
// restarting the walk after every removal.
typedef bool Bool;
#define NULL 0
class Team;

template <class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = (m_cur->*m_getNextFunc)(); }
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class TeamInQueue
{
public:
	virtual ~TeamInQueue();
	TeamInQueue *dlink_prev_TeamBuildQueue() const { return m_dlink_TeamBuildQueue.m_prev; }
	TeamInQueue *dlink_next_TeamBuildQueue() const { return m_dlink_TeamBuildQueue.m_next; }
	TeamInQueue *dlink_next_TeamReadyQueue() const { return m_dlink_TeamReadyQueue.m_next; }
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
	DLINK m_dlink_TeamBuildQueue; // +0x04
	DLINK m_dlink_TeamReadyQueue; // +0x0C
	char m_pad14[0x1C - 0x14];
public:
	Team *m_team;		// +0x1C
};

class AIPlayer
{
public:
	Bool isInList_TeamBuildQueue(TeamInQueue *o) const { return o->dlink_isInList_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue); }
	void prependTo_TeamBuildQueue(TeamInQueue *o);
	void removeFrom_TeamBuildQueue(TeamInQueue *o);
	typedef void (*RemoveAllProc_TeamBuildQueue)(TeamInQueue *o);
	void removeAll_TeamBuildQueue(RemoveAllProc_TeamBuildQueue p = NULL);
	void reverse_TeamBuildQueue();
	DLINK_ITERATOR<TeamInQueue> iterate_TeamBuildQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_dlinkhead_TeamBuildQueue, &TeamInQueue::dlink_next_TeamBuildQueue);
	}

	Bool isInList_TeamReadyQueue(TeamInQueue *o) const { return o->dlink_isInList_TeamReadyQueue(&m_dlinkhead_TeamReadyQueue); }
	void removeFrom_TeamReadyQueue(TeamInQueue *o);
	typedef void (*RemoveAllProc_TeamReadyQueue)(TeamInQueue *o);
	void removeAll_TeamReadyQueue(RemoveAllProc_TeamReadyQueue p = NULL);
	DLINK_ITERATOR<TeamInQueue> iterate_TeamReadyQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_dlinkhead_TeamReadyQueue, &TeamInQueue::dlink_next_TeamReadyQueue);
	}
	void aiPreTeamDestroy(const Team *deletedTeam);
private:
	void *m_vtbl;
	TeamInQueue *m_dlinkhead_TeamBuildQueue; // +0x04
	TeamInQueue *m_dlinkhead_TeamReadyQueue; // +0x08
};

// ------------------------------------------------------------------------------------------------
void AIPlayer::prependTo_TeamBuildQueue(TeamInQueue *o)
{
	if (!isInList_TeamBuildQueue(o))
		o->dlink_prependTo_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue);
}

void AIPlayer::removeFrom_TeamBuildQueue(TeamInQueue *o)
{
	if (isInList_TeamBuildQueue(o))
		o->dlink_removeFrom_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue);
}

void AIPlayer::reverse_TeamBuildQueue()
{
	TeamInQueue *cur = m_dlinkhead_TeamBuildQueue;
	TeamInQueue *prev = NULL;
	while (cur)
	{
		TeamInQueue *originalNext = cur->dlink_next_TeamBuildQueue();
		cur->dlink_swapLinks_TeamBuildQueue();
		prev = cur;
		cur = originalNext;
	}
	m_dlinkhead_TeamBuildQueue = prev;
}

void AIPlayer::removeFrom_TeamReadyQueue(TeamInQueue *o)
{
	if (isInList_TeamReadyQueue(o))
		o->dlink_removeFrom_TeamReadyQueue(&m_dlinkhead_TeamReadyQueue);
}

// AIPlayer::removeAll_TeamReadyQueue is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/AI/AIPlayer_Rva004F0499.cpp (0x004F0499).

void AIPlayer::aiPreTeamDestroy(const Team *deletedTeam)
{
	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team->m_team == deletedTeam)
			{
				removeFrom_TeamBuildQueue(team);
				::delete team;
				iter = iterate_TeamBuildQueue();
			}
		}
	}
	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamReadyQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team->m_team == deletedTeam)
			{
				removeFrom_TeamReadyQueue(team);
				::delete team;
				iter = iterate_TeamReadyQueue();
			}
		}
	}
}
