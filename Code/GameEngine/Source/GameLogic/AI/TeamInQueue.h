#pragma once
// Retail table C62B78: deleting dtor4EF606, empty post-load B3FD0,
// name getter4EF600, xfer4F19F6. Constructor4EF5CE and allocations prove 0x30.
// Field offsets are witnessed by the queue, xfer and AIPlayer consumers.
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
class Team;
class WorkOrder;
enum ObjectID;
class TeamInQueue : public Snapshot {
public:
    // AIPlayerTeamBuild.cpp defines this constructor and WorkOrder's ahead of
    // their users without an exception specification, so cl infers they
    // cannot throw and its new-expressions carry no EH cleanup state (Zero
    // Hour's are inline in AIPlayer.h); other units say throw() instead.
#ifdef BFME_AIPLAYER_QUEUE_CTORS
    TeamInQueue();
#else
    TeamInQueue() throw();
#endif
    virtual ~TeamInQueue();
    TeamInQueue *dlink_prev_TeamBuildQueue() const { return m_prev; }
    TeamInQueue *dlink_next_TeamBuildQueue() const { return m_next; }
    TeamInQueue *dlink_next_TeamReadyQueue() const { return m_nextReady; }
    void dlink_swapLinks_TeamBuildQueue() {
        TeamInQueue *originalNext=m_next;
        m_next=m_prev;
        m_prev=originalNext;
    }
    bool dlink_isInList_TeamBuildQueue(TeamInQueue *const *head) const;
    bool dlink_isInList_TeamReadyQueue(TeamInQueue *const *head) const;
    void dlink_prependTo_TeamBuildQueue(TeamInQueue **head);
    void dlink_removeFrom_TeamBuildQueue(TeamInQueue **head);
    void dlink_removeFrom_TeamReadyQueue(TeamInQueue **head);
    bool isAllBuilt();
    bool isMinimumBuilt();
    bool areBuildsComplete();
    bool isBuildTimeExpired();
    bool includesADozer();
    void disband();
    __forceinline void deleteInstance() { ::delete this; }
protected:
    // Snapshot slots 1-3 follow the spelling the included Snapshot base selected, so they always override.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif
public:
    TeamInQueue *m_prev;         // +04
    TeamInQueue *m_next;         // +08
    TeamInQueue *m_prevReady;    // +0C
    TeamInQueue *m_nextReady;    // +10
    WorkOrder *m_workOrders;     // +14
    bool m_priorityBuild;       // +18
    Team *m_team;               // +1C
    int m_unknown20;            // +20: constructor clears; purpose unknown
    int m_frameStarted;         // +24
    bool m_sentToStartLocation; // +28
    bool m_stopQueueing;        // +29
    bool m_reinforcement;       // +2A
    ObjectID m_reinforcementID; // +2C
};
typedef char TeamInQueueRetailSize[(sizeof(TeamInQueue)==0x30)?1:-1];
