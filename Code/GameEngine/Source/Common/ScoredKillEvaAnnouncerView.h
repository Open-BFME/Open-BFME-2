#ifndef BFME_SCORED_KILL_EVA_ANNOUNCER_VIEW_H
#define BFME_SCORED_KILL_EVA_ANNOUNCER_VIEW_H
#include <vector>
#include "ScoredKillTrackerView.h"
class Player;
class ScoredKillEvaAnnouncer {
public:
 // Table83A09C has four slots. Only the transfer's original name is proven.
 virtual void *slot00(int);
 virtual void slot04();
 virtual const char *slot08();
 virtual void DoXfer(Xfer *);
 void addMoreTrackersForNewPlayers();
private:
 // Borrowed48B prefix; native414DAA and414EA1 independently consume it.
 char unknown04[0x0c];
 unsigned lifetime;
 Rva00360D26Member filter;
 bool perPlayer,localOnly;
 char pad1A[2];
 _STL::vector<ScoredKillTracker> trackers;
 Player *localPlayer;
 int seenPlayers;
};
#endif
