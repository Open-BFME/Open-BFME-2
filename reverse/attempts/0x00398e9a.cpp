// ?rva00398E9A@CastleBehavior@@QAEXXZ
// partial score=0.870247 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
#include <vector>
#include <set>
#include <string.h>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
class Player;
class Team;
class ThingTemplate {public:char pad[0x618];int weight;};
class Rva0028BAC0Host {public:void rva0028BAC0();};
class Object {public:Player *getControllingPlayer() const;void setTeam(Team*);void rva0028DCC4();void rva0028D253();char pad[4];ThingTemplate *type;char pad8[0x38-8];Coord3D pos;char pad44[0x304-0x44];Team *team;};
enum Relationship {ENEMY=0,NEUTRAL=1,ALLY=2};
class Player {public:Relationship getRelationship(const Team*) const;char pad[0x54];int index;char pad58[4];void *state;char pad60[0x2ec-0x60];Team *team;};
enum NameKeyType {INVALID_KEY=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);}; extern NameKeyGenerator *TheNameKeyGenerator;
class PlayerList {public:Player* findPlayerWithNameKey(NameKeyType);Player*getNthPlayer(int);};extern PlayerList *ThePlayerList;
class GameLogic {public:char pad[0x40];unsigned frame;};extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
class Rva000421C8 {public:Rva000421C8():next(0){}virtual ~Rva000421C8(){}virtual bool allow(Object*)=0;virtual int getPlayerMask(){return -1;}Rva000421C8 *link(Rva000421C8*);Rva000421C8 *next;};
class Rva0026119DFilter:public Rva000421C8 {public:virtual bool allow(Object*);};
class BfmeFixedStorage0004543D {public:BfmeFixedStorage0004543D(){memset(words,0,sizeof(words));}BfmeFixedStorage0004543D(int,int) throw();BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&) throw();unsigned words[7];};
extern unsigned char g_00DFEFA4StoragePrototype[28];
class Rva003959FA:public Rva000421C8 {public:Rva003959FA(const BfmeFixedStorage0004543D&) throw();virtual bool allow(Object*);BfmeFixedStorage0004543D mask;};
class PartitionFilterRejectByKindOf:public Rva000421C8 {public:PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&) throw();virtual bool allow(Object*);BfmeFixedStorage0004543D a,b;};
struct Rva001408C0Target;
class Rva00395D18:public _STL::set<Rva001408C0Target*> {public:~Rva00395D18();};
class Rva00395F57 {public:bool canUnpack(bool);};
class Rva00397EAC {public:bool isPlayerAllowedToCapture(Player*,int);};
class CastleData {public:char pad[0x28];float radius;char pad2c[0x10];bool disabled;};
class CastleBehavior {public:void rva00398E9A();void *vtable;CastleData *data;Object *owner;};
void CastleBehavior::rva00398E9A(){
 if(!((Rva00395F57*)this)->canUnpack(false))return;
 Object *object=owner;
 if(!object)return;
 Player *civilian=ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey("PlyrCivilian"));
 const CastleData *d=data;
 if(d->radius<=0.0f || d->disabled)return;
 Coord3D pos;pos.x=object->pos.x;pos.y=object->pos.y;pos.z=object->pos.z;
 BfmeFixedStorage0004543D flags;flags.words[0]|=0xf00;
 BfmeWideResult result=ThePartitionManager->iterateObjectsInRange(&pos,d->radius,0,
  PartitionFilterRejectByKindOf(BfmeFixedStorage0004543D(0,127),*(BfmeFixedStorage0004543D*)g_00DFEFA4StoragePrototype).link(Rva003959FA(flags).link(&Rva0026119DFilter())),0);
 int initial=-1;_STL::vector<int> weights(20U,initial);
 Rva00395D18 players;
 bool hostile=false;
 Object *candidate;
 while((candidate=result.next())!=0){
  Rva001408C0Target *entry=(Rva001408C0Target*)candidate->getControllingPlayer();
  Player *player=(Player*)entry;
  if(player==civilian)continue;
  for(Rva00395D18::iterator it=players.begin();it!=players.end();++it){
   Player *other=(Player*)*it;
   if(player->getRelationship(other->team)!=ALLY){hostile=true;break;}
  }
  players.insert(entry);
  int value=player->state==0?2:1;
  int index=player->index;
  if(weights[index]<0)weights[index]=value;
  weights[index]+=value;
  weights[index]+=value*candidate->type->weight;
 }
 int chosen=-1;int largest=chosen;
 for(int i=0;i<20;++i){if(weights[i]>largest){chosen=i;largest=weights[i];}}
 Team *team;
 Player *player;
 if(chosen!=-1 && (player=ThePlayerList->getNthPlayer(chosen)) && !hostile){
  team=player->team;
  if(team==object->team)return;
  if(((Rva00397EAC*)this)->isPlayerAllowedToCapture(player,2)){object->setTeam(team);((Rva0028BAC0Host*)object)->rva0028BAC0();object->rva0028DCC4();object->rva0028D253();}
  return;
 }else{
  if(TheGameLogic->frame<=5 || !civilian || civilian==object->getControllingPlayer() || !civilian->team)return;
  team=civilian->team;
 }
 object->setTeam(team);
 ((Rva0028BAC0Host*)object)->rva0028BAC0();
 object->rva0028DCC4();
 object->rva0028D253();
}
