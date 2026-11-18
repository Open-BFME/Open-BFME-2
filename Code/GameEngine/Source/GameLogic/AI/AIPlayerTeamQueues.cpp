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
// body 0x004F035B, rowed as the placeholder Rva00160530::set and called
// through that spelling. Layout (target evidence): TeamInQueue's build-queue links
// (prev, next) at +0x04 / +0x08 and ready-queue links at +0x0C / +0x10;
// AIPlayer's heads at +0x04 (build) and +0x08 (ready).
//
// AIPlayer::aiPreTeamDestroy 0x004F0819 (143 bytes) is ZH's walk of both
// queues with DLINK_ITERATOR, deleting (virtual destructor, then the global
// operator delete) each entry whose team (+0x1C) is the dying one and
// restarting the walk after every removal.
#include <stddef.h>
#include "../../../Include/Common/ScalarTypes.h"
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

// The rowed build-queue prepend 0x004F035B (TeamInQueue at its +0 links).
class Rva00160530
{
public:
	void set(Rva00160530 **pListHead);
};

#include "TeamInQueue.h"

#include "../../../Include/GameLogic/AIPlayerClass.h"

// Inline here: retail inlines both membership tests into the queue bodies below and
// keeps their out-of-line copies 0x004F03DF and 0x004EF373 from this unit.
inline Bool AIPlayer::isInList_TeamBuildQueue(TeamInQueue *teamInQueue) const { return teamInQueue->dlink_isInList_TeamBuildQueue(&m_teamBuildQueue.m_head); }
inline Bool AIPlayer::isInList_TeamReadyQueue(TeamInQueue *teamInQueue) const { return teamInQueue->dlink_isInList_TeamReadyQueue(&m_teamReadyQueue.m_head); }

// File-local walks over AIPlayer's queue heads; retail inlines them into aiPreTeamDestroy.
static inline DLINK_ITERATOR<TeamInQueue> iterateTeamBuildQueue(TeamInQueue *head)
{
	return DLINK_ITERATOR<TeamInQueue>(head, &TeamInQueue::dlink_next_TeamBuildQueue);
}
static inline DLINK_ITERATOR<TeamInQueue> iterateTeamReadyQueue(TeamInQueue *head)
{
	return DLINK_ITERATOR<TeamInQueue>(head, &TeamInQueue::dlink_next_TeamReadyQueue);
}

// ------------------------------------------------------------------------------------------------
void AIPlayer::prependTo_TeamBuildQueue(TeamInQueue *teamInQueue)
{
	if (!isInList_TeamBuildQueue(teamInQueue))
		((Rva00160530 *)teamInQueue)->set((Rva00160530 **)&m_teamBuildQueue.m_head);
}

void AIPlayer::removeFrom_TeamBuildQueue(TeamInQueue *teamInQueue)
{
	if (isInList_TeamBuildQueue(teamInQueue))
		teamInQueue->dlink_removeFrom_TeamBuildQueue(&m_teamBuildQueue.m_head);
}

void AIPlayer::reverse_TeamBuildQueue()
{
	TeamInQueue *cur = m_teamBuildQueue;
	TeamInQueue *prev = NULL;
	while (cur)
	{
		TeamInQueue *originalNext = cur->dlink_next_TeamBuildQueue();
		cur->dlink_swapLinks_TeamBuildQueue();
		prev = cur;
		cur = originalNext;
	}
	m_teamBuildQueue = prev;
}

void AIPlayer::removeFrom_TeamReadyQueue(TeamInQueue *teamInQueue)
{
	if (isInList_TeamReadyQueue(teamInQueue))
		teamInQueue->dlink_removeFrom_TeamReadyQueue(&m_teamReadyQueue.m_head);
}

// AIPlayer::removeAll_TeamReadyQueue is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/AI/AIPlayer_Rva004F0499.cpp (0x004F0499).

void AIPlayer::aiPreTeamDestroy(const Team *deletedTeam)
{
	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterateTeamBuildQueue(m_teamBuildQueue); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team->m_team == deletedTeam)
			{
				removeFrom_TeamBuildQueue(team);
				::delete team;
				iter = iterateTeamBuildQueue(m_teamBuildQueue);
			}
		}
	}
	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterateTeamReadyQueue(m_teamReadyQueue); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team->m_team == deletedTeam)
			{
				removeFrom_TeamReadyQueue(team);
				::delete team;
				iter = iterateTeamReadyQueue(m_teamReadyQueue);
			}
		}
	}
}
