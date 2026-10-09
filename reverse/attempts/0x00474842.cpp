// ?rva00474842@Rva00474842@@QAEXPAVObject@@PBUCoord3D@@M_N@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /ICode/Libraries/Include
// Semantic guide: Open-BFME-1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d,
// game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/MemberTurnAndGoal0024E310.cpp.
// Native474842..474B51 RET16 and WB10B8C80 identify HordeContain member-position
// dispatch. Native supplies Object258/25C/438, AI goal1FC and slots111/113/136,
// owner2A0 target, definition240/244, formation flags120/121. Donor provides
// moving/turning/goal relationship; retail differs in terrain and flags paths.
#include "Lib/Coord3D.h"
struct Rva474842Coordinate : Coord3D {
 // ?Rva474842Coordinate::Rva474842Coordinate present-unmatched
 __forceinline Rva474842Coordinate() {}
 // ?Rva474842Coordinate::~Rva474842Coordinate present-unmatched
 __forceinline ~Rva474842Coordinate() {}
};
enum ObjectStatusTypes { Rva474842Status75=75 };
enum KindOfType { Rva474842Kind443=443 };
enum CommandSourceType { Rva474842AI=2 };
class AICommandInterface { public: void rva0045003E(int,CommandSourceType); char opaque[4]; };
class Rva001E3591 { public: bool rva001E3591(); };
class AIUpdateInterface {
public:
 bool isMoving() const;
 void rva00262AEA();
 virtual void reserved0();
 virtual void reserved1();
 virtual void reserved2();
 virtual void reserved3();
 virtual void reserved4();
 virtual void reserved5();
 virtual void reserved6();
 virtual void reserved7();
 virtual void reserved8();
 virtual void reserved9();
 virtual void reserved10();
 virtual void reserved11();
 virtual void reserved12();
 virtual void reserved13();
 virtual void reserved14();
 virtual void reserved15();
 virtual void reserved16();
 virtual void reserved17();
 virtual void reserved18();
 virtual void reserved19();
 virtual void reserved20();
 virtual void reserved21();
 virtual void reserved22();
 virtual void reserved23();
 virtual void reserved24();
 virtual void reserved25();
 virtual void reserved26();
 virtual void reserved27();
 virtual void reserved28();
 virtual void reserved29();
 virtual void reserved30();
 virtual void reserved31();
 virtual void reserved32();
 virtual void reserved33();
 virtual void reserved34();
 virtual void reserved35();
 virtual void reserved36();
 virtual void reserved37();
 virtual void reserved38();
 virtual void reserved39();
 virtual void reserved40();
 virtual void reserved41();
 virtual void reserved42();
 virtual void reserved43();
 virtual void reserved44();
 virtual void reserved45();
 virtual void reserved46();
 virtual void reserved47();
 virtual void reserved48();
 virtual void reserved49();
 virtual void reserved50();
 virtual void reserved51();
 virtual void reserved52();
 virtual void reserved53();
 virtual void reserved54();
 virtual void reserved55();
 virtual void reserved56();
 virtual void reserved57();
 virtual void reserved58();
 virtual void reserved59();
 virtual void reserved60();
 virtual void reserved61();
 virtual void reserved62();
 virtual void reserved63();
 virtual void reserved64();
 virtual void reserved65();
 virtual void reserved66();
 virtual void reserved67();
 virtual void reserved68();
 virtual void reserved69();
 virtual void reserved70();
 virtual void reserved71();
 virtual void reserved72();
 virtual void reserved73();
 virtual void reserved74();
 virtual void reserved75();
 virtual void reserved76();
 virtual void reserved77();
 virtual void reserved78();
 virtual void reserved79();
 virtual void reserved80();
 virtual void reserved81();
 virtual void reserved82();
 virtual void reserved83();
 virtual void reserved84();
 virtual void reserved85();
 virtual void reserved86();
 virtual void reserved87();
 virtual void reserved88();
 virtual void reserved89();
 virtual void reserved90();
 virtual void reserved91();
 virtual void reserved92();
 virtual void reserved93();
 virtual void reserved94();
 virtual void reserved95();
 virtual void reserved96();
 virtual void reserved97();
 virtual void reserved98();
 virtual void reserved99();
 virtual void reserved100();
 virtual void reserved101();
 virtual void reserved102();
 virtual void reserved103();
 virtual void reserved104();
 virtual void reserved105();
 virtual void reserved106();
 virtual void reserved107();
 virtual void reserved108();
 virtual void reserved109();
 virtual void reserved110();
 virtual bool slot111();
 virtual void reserved112();
 virtual bool slot113();
 virtual void reserved114();
 virtual void reserved115();
 virtual void reserved116();
 virtual void reserved117();
 virtual void reserved118();
 virtual void reserved119();
 virtual void reserved120();
 virtual void reserved121();
 virtual void reserved122();
 virtual void reserved123();
 virtual void reserved124();
 virtual void reserved125();
 virtual void reserved126();
 virtual void reserved127();
 virtual void reserved128();
 virtual void reserved129();
 virtual void reserved130();
 virtual void reserved131();
 virtual void reserved132();
 virtual void reserved133();
 virtual void reserved134();
 virtual void reserved135();
 virtual void slot136();
 char opaque04[0x20-4]; AICommandInterface command;
 char opaque24[0x140-0x24]; Rva001E3591 *path;
 char opaque144[0x1fc-0x144]; int goal;
};
class Rva00474842MemberSub { public: char opaque[0x5c]; bool paused; };
class Object {
public:
 bool testStatus(ObjectStatusTypes) const;
 bool isKindOf(KindOfType) const;
 float rva00263763(const void *) const;
 void rva0028AE6D();
 int rva0028B511() const;
 char opaque000[0x38]; Coord3D position;
 char opaque044[0x110-0x44]; unsigned modelFlags[19];
 char opaque15c[0x258-0x15c]; AIUpdateInterface *ai;
 Rva00474842MemberSub *sub;
 char opaque260[0x438-0x260]; unsigned char status438;
 __forceinline void clearMoving() {
  if (modelFlags[0] & 0x20000000) { modelFlags[0] &= ~0x20000000; rva0028AE6D(); }
 }
};
class Rva00265254 { public: Rva00265254(unsigned,unsigned,unsigned,unsigned); unsigned words[19]; };
class Rva001E42F2 { public: void rva001E42F2(const int *); };
class Rva0030A92C { public: void rva0030A92C(float); };
class TerrainLogic {
public:
 virtual void unused0();
 virtual void unused1();
 virtual void unused2();
 virtual void unused3();
 virtual void unused4();
 virtual void unused5();
 virtual void unused6();
 virtual float height(float,float,int,bool*,bool);
};
extern TerrainLogic *TheTerrainLogic;
class Rva00469012 { public: bool rva00469012(Object*,const Coord3D*); };
class Rva0046AFDEReceiver { public: bool rva0046AFDE(Object*); };
struct Rva0046E6EACoord { float x,y,z; };
struct Rva0046E6EAObject;
class Rva0046E6EA { public: bool rva0046E6EA(Rva0046E6EAObject*,const Rva0046E6EACoord*,Rva0046E6EACoord*,bool); };
class Rva00474842Iface {
public:
 virtual void unused0();
 virtual void unused1();
 virtual void unused2();
 virtual void unused3();
 virtual void unused4();
 virtual void unused5();
 virtual void unused6();
 virtual void unused7();
 virtual void unused8();
 virtual void unused9();
 virtual void unused10();
 virtual void unused11();
 virtual void unused12();
 virtual void unused13();
 virtual void unused14();
 virtual void unused15();
 virtual void unused16();
 virtual void unused17();
 virtual void unused18();
 virtual void unused19();
 virtual void unused20();
 virtual void unused21();
 virtual void unused22();
 virtual void unused23();
 virtual void unused24();
 virtual void unused25();
 virtual void unused26();
 virtual void unused27();
 virtual void unused28();
 virtual void unused29();
 virtual void unused30();
 virtual void unused31();
 virtual void unused32();
 virtual void unused33();
 virtual void unused34();
 virtual void unused35();
 virtual void unused36();
 virtual void unused37();
 virtual void unused38();
 virtual void unused39();
 virtual void unused40();
 virtual void unused41();
 virtual void unused42();
 virtual void unused43();
 virtual void unused44();
 virtual void unused45();
 virtual void unused46();
 virtual void unused47();
 virtual void unused48();
 virtual void unused49();
 virtual void unused50();
 virtual void unused51();
 virtual void unused52();
 virtual void unused53();
 virtual void unused54();
 virtual void unused55();
 virtual void unused56();
 virtual void unused57();
 virtual void unused58();
 virtual void unused59();
 virtual void unused60();
 virtual void unused61();
 virtual void unused62();
 virtual void unused63();
 virtual void unused64();
 virtual void unused65();
 virtual void unused66();
 virtual void unused67();
 virtual void unused68();
 virtual void unused69();
 virtual void unused70();
 virtual void unused71();
 virtual void unused72();
 virtual void unused73();
 virtual void unused74();
 virtual void unused75();
 virtual void unused76();
 virtual void unused77();
 virtual void unused78();
 virtual void unused79();
 virtual void unused80();
 virtual void unused81();
 virtual void unused82();
 virtual void unused83();
 virtual void unused84();
 virtual void unused85();
 virtual void unused86();
 virtual void unused87();
 virtual void unused88();
 virtual void unused89();
 virtual void unused90();
 virtual void unused91();
 virtual void unused92();
 virtual void unused93();
 virtual void unused94();
 virtual void unused95();
 virtual void unused96();
 virtual void unused97();
 virtual void unused98();
 virtual void unused99();
 virtual void unused100();
 virtual void unused101();
 virtual void unused102();
 virtual void unused103();
 virtual void unused104();
 virtual void unused105();
 virtual void unused106();
 virtual void unused107();
 virtual void unused108();
 virtual void unused109();
 virtual void unused110();
 virtual void unused111();
 virtual void unused112();
 virtual void unused113();
 virtual void unused114();
 virtual void unused115();
 virtual void unused116();
 virtual void unused117();
 virtual void unused118();
 virtual void unused119();
 virtual void unused120();
 virtual void unused121();
 virtual void unused122();
 virtual void unused123();
 virtual void unused124();
 virtual void unused125();
 virtual void unused126();
 virtual void unused127();
 virtual void unused128();
 virtual void unused129();
 virtual void unused130();
 virtual void unused131();
 virtual void unused132();
 virtual void unused133();
 virtual void unused134();
 virtual void unused135();
 virtual void unused136();
 virtual void unused137();
 virtual void unused138();
 virtual void unused139();
 virtual void unused140();
 virtual void unused141();
 virtual bool ready();
};
struct Rva00474842Definition {
 char opaque000[0x240]; bool allow;
 char opaque241[3]; float distance;
};
class Rva00474842 {
public:
 void rva00474842(Object*,const Coord3D*,float,bool);
 void rva00471464(Object*,const Coord3D*,float);
 void *vptr; Rva00474842Definition *definition; Object *owner;
 char opaque00c[0x11c-12]; Rva00474842Iface interface;
 bool flag120,flag121;
 char opaque122[0x1a4-0x122]; int field1a4;
 char opaque1a8[0x2a0-0x1a8]; int target;
};
static __forceinline const float &rva474842Min(const float &a,const float &b) {return a<b?a:b;}
void Rva00474842::rva00474842(Object *obj,const Coord3D *position,float orientation,bool flag)
{
 AIUpdateInterface *ai=obj->ai;
 Object *self=owner;
 AIUpdateInterface *selfAI=self->ai;
 Rva00474842Definition *data=definition;
 if ((obj->sub && obj->sub->paused) || (obj->status438&1) || !selfAI || !ai) return;
 if(selfAI->isMoving() && !target) {
  float distance=self->rva00263763(obj);
  Rva474842Coordinate delta;
  delta.x=obj->position.x-position->x;
  delta.y=obj->position.y-position->y;
  delta.z=0;
  float length=(delta.x*delta.x)+(delta.y*delta.y);
  distance=rva474842Min(distance,length);
  if(distance>data->distance*data->distance && !ai->slot113())
   ai->command.rva0045003E(0,Rva474842AI);
 }
 if(ai->slot111()) {
  bool held=obj->testStatus(Rva474842Status75);
  if(!selfAI->isMoving() || !held) {
   if(ai->isMoving()) ai->rva00262AEA();
   obj->clearMoving();
   ai->slot136();
   if(obj->isKindOf(Rva474842Kind443)) {
    ((Rva001E42F2*)obj)->rva001E42F2((const int*)&Rva00265254(0,103,105,443));
    ((Rva0030A92C*)obj)->rva0030A92C(TheTerrainLogic->height(obj->position.x,obj->position.y,obj->rva0028B511(),0,true));
   }
   return;
  }
 }
 data=definition;
 if(target) {
  if(ai->goal==4 && ai->path && ai->path->rva001E3591()) {flag120=true;return;}
  rva00471464(obj,position,orientation);
  return;
 }
 if(ai->goal==4 && ai->path) {flag120=true;return;}
 if(interface.ready()) {flag121=true;flag120=true;}
 if(!flag && !flag121 && ((Rva00469012*)this)->rva00469012(obj,position)==1 && !field1a4 && data->allow==true &&
  (selfAI->isMoving() || ((Rva0046AFDEReceiver*)this)->rva0046AFDE(obj))) {
  if(ai->isMoving()) ai->rva00262AEA();
  obj->clearMoving();ai->slot136();flag120=true;return;
 }
 Rva474842Coordinate dest;
 dest.x=position->x; dest.y=position->y; dest.z=position->z;
 ((Rva0046E6EA*)this)->rva0046E6EA((Rva0046E6EAObject*)obj,(const Rva0046E6EACoord*)&dest,(Rva0046E6EACoord*)self,!flag);
 rva00471464(obj,&dest,orientation);
}
