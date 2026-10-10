// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /ICode/GameEngine/Source/Common /Ireference/shims/moduledata /ICode/Libraries/Include
// Retail41505B..415122 (199B), existing neutral owner/method pins retained.
// Caller415122 invokes this for each 48B announcer; reset414F5E and tracker
// growth414DAA already own the same28/2C player state and1C/20 vector.
// Native consumes event8, thresholdC and each canonical44B tracker count1C/
// position20; original helper name and complete receiver type remain unknown.
// Canonical headers supply tracker/announcer ABI; prefix views borrow fields
// without asserting a second original class layout. No clean named reference
// helper was found; target accesses and existing providers establish behavior.
// Short-circuit assignment delays playerCount load past the player comparison;
// duplicated report calls preserve the native shared argument tail.
// stlport
#include "ScoredKillEvaAnnouncerView.h"
class PlayerList;extern PlayerList *ThePlayerList;
struct PlayerListUpdateView{char pad[0x10];Player *localPlayer;int playerCount;};
class Eva{public:void reportEvaEvent(int,const Coord3D*,int);};extern Eva *TheEva;
class Rva00414F5EHost{public:void run();};
struct AnnouncerUpdateView{char pad[8];int event;unsigned threshold;char pad10[12];_STL::vector<ScoredKillTracker> trackers;Player *localPlayer;int seenPlayers;};
struct TrackerUpdateView{char pad[0x1c];int count;Coord3D position;};
class Rva00414B0A{public:void rva0041505B();void rva00414B0A();};
void Rva00414B0A::rva0041505B(){
 AnnouncerUpdateView *self=(AnnouncerUpdateView*)this;
 PlayerListUpdateView *players=(PlayerListUpdateView*)ThePlayerList;
 int count;
 if(self->localPlayer!=players->localPlayer || (count=players->playerCount,self->seenPlayers>count)){((Rva00414F5EHost*)this)->run();return;}
 if(self->seenPlayers<count)((ScoredKillEvaAnnouncer*)this)->addMoreTrackersForNewPlayers();
 _STL::vector<ScoredKillTracker>::iterator i=self->trackers.begin(),end=self->trackers.end();
 unsigned total=0;Coord3D point;point.x=0;point.y=0;point.z=0;
 for(;i!=end;++i){
  const Coord3D *position=&((TrackerUpdateView*)i)->position;
  if(total>=self->threshold)break;
  int kills=((const int*)position)[-1];total+=kills;
  if(kills>0)point=*position;
 }
 if(total>=self->threshold){Coord3D zero;zero.x=0;zero.y=0;zero.z=0;if(point==zero)TheEva->reportEvaEvent(self->event,0,0);else TheEva->reportEvaEvent(self->event,&point,0);}
}
