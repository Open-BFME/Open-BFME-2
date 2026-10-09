#ifndef BFME_SCORED_KILL_TRACKER_VIEW_H
#define BFME_SCORED_KILL_TRACKER_VIEW_H
// Native55A998 constructor and55AB99 copy plus414520 teardown and55AA68
// transfer prove this44B view. Table83A08C has destructor/load/name/xfer.
// The scalar at0C remains unnamed. Position construction is a12B member
// wrapper around canonical Coord3D: native initializes it after the count.
#include <list>
#define BFME_SNAPSHOT_NAME_SLOT 1
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS 1
#include "Common/Snapshot.h"
#undef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#undef BFME_SNAPSHOT_NAME_SLOT
#include "../../../Libraries/Include/Lib/Coord3D.h"
class Rva00360D26Member {
public:
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
 virtual ~ScoredKillTracker();
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName() const;
 virtual void DoXfer(Xfer *);
 // Native55A892..55A8E2 filters by the20-player mask at0C and then
 // applies the indexed ObjectFilter at8 with the tracked owner at14.
 // Its original method name remains unknown. Nonvirtual; layout unchanged.
 bool rva0055A892(const class Object *);
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
#endif
