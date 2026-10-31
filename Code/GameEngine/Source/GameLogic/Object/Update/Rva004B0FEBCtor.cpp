// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native4B0EE5..4B0FA0 constructor of the filter whose predicate4B0FEB
// is already recovered. VtableC56520 slots395A19/4B0FEB/4B0D28 and
// caller4B17B6 (EmotionTrackerUpdate secondary-this minus10) establish
// identity. ZH PartitionFilter base supplies chain/destructor role;
// target alone establishes24B layout, two masks and shroud counters.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Include/Common/Player.h"
class Object {public:Player *getControllingPlayer()const;char pad[0x38];Coord3D pos;};
class EmotionTrackerUpdate {public:class TauntPointFilter;char pad[8];Object *object;};
class PlayerList {public:int getPlayersWithRelationship(int,unsigned,bool);};extern PlayerList *ThePlayerList;
struct BfmePointFD;
class Rva00739830 {public:int rva00739830(const BfmePointFD *,int,unsigned)const;};// Global type follows the existing FXListDoFXPos provider.
class PartitionManager;extern PartitionManager *TheShroudManager;
class Rva000421C8 {public:Rva000421C8():next(0){}virtual ~Rva000421C8();virtual bool Allow(Object*)=0;virtual int getPlayerMask();Rva000421C8 *next;};
// Name: WorldBuilder twin 0x01230A20 EmotionTrackerUpdate::TauntPointFilter::Allow (call graph)
// names slot 1 and this nested class; the slot-2 and constructor names follow from it.
class EmotionTrackerUpdate::TauntPointFilter:public Rva000421C8 {public:TauntPointFilter(EmotionTrackerUpdate*);virtual bool Allow(Object*);virtual int getPlayerMask();
 EmotionTrackerUpdate *module;Object *object;Player *player;int enemyCount,allyCount;Object *cached;bool tested;
};
EmotionTrackerUpdate::TauntPointFilter::TauntPointFilter(EmotionTrackerUpdate *emotionTrackerUpdate):module(emotionTrackerUpdate),cached(0),tested(false) {
 object=emotionTrackerUpdate->object;enemyCount=0;allyCount=0;player=object?object->getControllingPlayer():0;
 if(player){unsigned allies=ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),3,false);
 unsigned enemies=ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),4,false);
 enemyCount=((Rva00739830 *)TheShroudManager)->rva00739830((const BfmePointFD *)&object->pos,1,enemies);
 allyCount=((Rva00739830 *)TheShroudManager)->rva00739830((const BfmePointFD *)&object->pos,1,allies);}
}

inline Rva000421C8::~Rva000421C8() {}
int EmotionTrackerUpdate::TauntPointFilter::getPlayerMask(){if(object && player)return ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),4,false);return 0;}
