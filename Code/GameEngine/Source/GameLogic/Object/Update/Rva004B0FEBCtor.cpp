// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native4B0EE5..4B0FA0 constructor of the filter whose predicate4B0FEB
// is already recovered. VtableC56520 slots395A19/4B0FEB/4B0D28 and
// caller4B17B6 (EmotionTrackerUpdate secondary-this minus10) establish
// identity. ZH PartitionFilter base supplies chain/destructor role;
// target alone establishes24B layout, two masks and shroud counters.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Player {public:__forceinline int getPlayerIndex()const{return index;}char pad[0x54];int index;};
class Object {public:Player *getControllingPlayer()const;char pad[0x38];Coord3D pos;};
class EmotionTrackerUpdate {public:char pad[8];Object *object;};
class PlayerList {public:int getPlayersWithRelationship(int,unsigned,bool);};extern PlayerList *ThePlayerList;
struct BfmePointFD;
class Rva00739830 {public:int rva00739830(const BfmePointFD *,int,unsigned)const;};// Global type follows the existing FXListDoFXPos provider.
class PartitionManager;extern PartitionManager *TheShroudManager;
class Rva000421C8 {public:Rva000421C8():next(0){}__declspec(noinline) virtual ~Rva000421C8();virtual bool allow(Object*)=0;virtual int getPlayerMask();Rva000421C8 *next;};
class Rva004B0FEB:public Rva000421C8 {public:Rva004B0FEB(EmotionTrackerUpdate*);virtual bool allow(Object*);virtual int getPlayerMask();
 EmotionTrackerUpdate *module;Object *object;Player *player;int enemyCount,allyCount;Object *cached;bool tested;
};
Rva004B0FEB::Rva004B0FEB(EmotionTrackerUpdate *m):module(m),cached(0),tested(false) {
 object=m->object;enemyCount=0;allyCount=0;player=object?object->getControllingPlayer():0;
 if(player){unsigned allies=ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),3,false);
 unsigned enemies=ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),4,false);
 enemyCount=((Rva00739830 *)TheShroudManager)->rva00739830((const BfmePointFD *)&object->pos,1,enemies);
 allyCount=((Rva00739830 *)TheShroudManager)->rva00739830((const BfmePointFD *)&object->pos,1,allies);}
}

Rva000421C8::~Rva000421C8() {}
int Rva004B0FEB::getPlayerMask(){if(object && player)return ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),4,false);return 0;}
