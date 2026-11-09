// cl: /Ob0
// The 32B list check-then-remove at 0x004F040F is rowed as
// AIPlayer::removeFrom_TeamBuildQueue in AIPlayerTeamQueues.cpp.
typedef bool Bool;

struct BfmeNode_00161220
{
	void *m_vptr;
	BfmeNode_00161220 *m_next04;
	BfmeNode_00161220 *m_previous08;
	BfmeNode_00161220 *m_next0C;
	BfmeNode_00161220 *m_previous10;

	Bool isInList04(BfmeNode_00161220 **head) const;
	Bool isInList0C(BfmeNode_00161220 **head) const;
	void rva004F03AF(BfmeNode_00161220 **head);
};

// 0x004EF383 is AIPlayer::prependTo_TeamReadyQueue: WorldBuilder's AIPlayer.h inline (score 4)
// and Zero Hour's checkQueuedTeams call it with the entry right after removeFrom_TeamBuildQueue.
class TeamInQueue;

#include "../../Include/GameLogic/AIPlayerClass.h"

// Native4EF39A calls the independently byte-verified/link-clean23-byte
// second-list prepend4EF35C with its node receiver and supplied head.
// This declaration adds no receiver layout or original type claim.
class Rva004EF35CAppendABI
{
public:
    void prepend(void **head);
};
// The membership test and the link are the rowed
// TeamInQueue::dlink_isInList_TeamReadyQueue and Rva00160620::set.
#include "../GameLogic/AI/TeamInQueue.h"
class Rva00160620
{
public:
	void set(Rva00160620 **head);
};

void AIPlayer::prependTo_TeamReadyQueue(TeamInQueue *team)
{
    TeamInQueue **readyQueueHead = &m_teamReadyQueue.m_head;
    if (!team->dlink_isInList_TeamReadyQueue(readyQueueHead))
        ((Rva00160620 *)team)->set((Rva00160620 **)readyQueueHead);
}
