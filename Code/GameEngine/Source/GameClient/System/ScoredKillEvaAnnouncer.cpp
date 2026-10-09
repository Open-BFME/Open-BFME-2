// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
#include <vector>
#include "../../Common/ScoredKillEvaAnnouncerView.h"
class Player;
class PlayerList {public:Player *getNthPlayer(int);};
extern PlayerList *ThePlayerList;
struct AnnouncerPlayersView {char pad[0x14];int count;};
struct AnnouncerPlayerMaskView {char pad[0x54];unsigned bit;};
// WB12B4A70 names this method. Native414DAA..414EA1 proves the local
// player mask and per-player tracker creation plus keeper hookup at+3BC.
void ScoredKillEvaAnnouncer::addMoreTrackersForNewPlayers() {
 unsigned mask;
 if(localOnly) {if(!localPlayer)return;mask=1u<<reinterpret_cast<AnnouncerPlayerMaskView *>(localPlayer)->bit;}
 else mask=0xfffff;
 if(perPlayer) {
  if(trackers.empty()) {
   trackers.push_back(ScoredKillTracker(lifetime,filter,mask));
   trackers.back().hookToKeeper(reinterpret_cast<Rva0039BCF8 *>(reinterpret_cast<char *>(localPlayer)+0x3bc));
  }
 } else {
  for(int i=seenPlayers;i<reinterpret_cast<AnnouncerPlayersView *>(ThePlayerList)->count;++i) {
   trackers.push_back(ScoredKillTracker(lifetime,filter,mask));
   Player *player=ThePlayerList->getNthPlayer(i);
   trackers.back().hookToKeeper(reinterpret_cast<Rva0039BCF8 *>(reinterpret_cast<char *>(player)+0x3bc));
  }
 }
 seenPlayers=reinterpret_cast<AnnouncerPlayersView *>(ThePlayerList)->count;
}
template void _STL::vector<ScoredKillTracker>::push_back(const ScoredKillTracker &);
