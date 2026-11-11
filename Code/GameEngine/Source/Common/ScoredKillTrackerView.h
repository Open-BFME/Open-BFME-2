#ifndef BFME_SCORED_KILL_TRACKER_VIEW_H
#define BFME_SCORED_KILL_TRACKER_VIEW_H
// Native55A998 constructor and55AB99 copy plus414520 teardown and55AA68
// transfer prove this44B view. Table83A08C has destructor/load/name/xfer.
// The scalar at0C remains unnamed. Position construction is a12B member
// wrapper around canonical Coord3D: native initializes it after the count.
#include <list>
#if !defined(__SNAPSHOT_H_)
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT 1
#define BFME_SCORED_KILL_RESTORE_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS 1
#define BFME_SCORED_KILL_RESTORE_CAPITALIZED_SLOTS
#endif
#endif
#include "Common/Snapshot.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
class Rva00360D26Member {
public:
 Rva00360D26Member();	// 0x003623E5 (row in Rva003623E5MemberCtor.cpp)
 ~Rva00360D26Member();
 int index;
};
struct ScoredKillTrackerPosition {
 Coord3D value;
 ScoredKillTrackerPosition() {value.x=0;value.y=0;value.z=0;}
 ScoredKillTrackerPosition(const ScoredKillTrackerPosition &other) {
  value.x=other.value.x;value.y=other.value.y;value.z=other.value.z;
 }
};
class Rva0039BCF8;
class ScoredKillTracker:public Snapshot {
public:
 ScoredKillTracker(unsigned,const Rva00360D26Member &,unsigned);
 ScoredKillTracker(const ScoredKillTracker &);
 ScoredKillTracker &operator=(const ScoredKillTracker &);
 virtual ~ScoredKillTracker();
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
 virtual void crc(Xfer *);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
 virtual void DoXfer(Xfer &);
#else
 virtual void DoXfer(Xfer *);
#endif
#else
 virtual void xfer(Xfer *);
#endif
 // Native55A892..55A8E2 filters by the20-player mask at0C and then
 // applies the indexed ObjectFilter at8 with the tracked owner at14.
 // Its original method name remains unknown. Nonvirtual; layout unchanged.
 bool rva0055A892(const class Object *);
 void setLifetime(unsigned);
 void setFilter(const Rva00360D26Member &);
 void setFlags(unsigned);
 void rva0055A91A();
 void hookToKeeper(Rva0039BCF8 *);
 void friend_addTrackedKill(const Coord3D *);
 void friend_update();
private:
 unsigned m_lifetime;
 Rva00360D26Member m_filter;
 unsigned m_value0c;
 Rva0039BCF8 *m_keeper;
 int m_playerIndex;
 _STL::list<int> m_trackedKills;
 int m_trackedKillsCount;
 ScoredKillTrackerPosition m_position;
};
typedef char ScoredKillTrackerSizeIs44[sizeof(ScoredKillTracker)==44?1:-1];
#ifdef BFME_SCORED_KILL_RESTORE_NAME_SLOT
#undef BFME_SCORED_KILL_RESTORE_NAME_SLOT
#undef BFME_SNAPSHOT_NAME_SLOT
#endif
#ifdef BFME_SCORED_KILL_RESTORE_CAPITALIZED_SLOTS
#undef BFME_SCORED_KILL_RESTORE_CAPITALIZED_SLOTS
#undef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#endif
