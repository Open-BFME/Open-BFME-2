// cl: /O1 /G7 /arch:SSE /MD /EHsc /Oi- /ICode/Libraries/Include /ICode/GameEngine/Source/Common
// Native338B 36B567 plus387B 368D12; donor revision575ba2b04; ZH AIUpdateInterface::doLocomotor
// establishes the locomotor goal dispatch purpose; BFME2 giant-bird adds aerial
// path handling and closest-object separation. WB F39B30/F39DC0 confirms
// this class/file relationship; original function names remain unproven.
// Native volatile reads at final Z then X preserve the measured operand order.
// Extended Y intermediate preserves native x87 addition without an extra FSTP. Names beyond the verified
// GiantBird owner remain address derived. Layouts and call order are native.
#include <math.h>
#include "Lib/Coord3D.h"
class Object;
class Rva00375A73Context {public:unsigned char prefix[0x54];Coord3D goal;};
class Locomotor {public:void locoUpdate_moveTowardsAngle(Object*,float);bool rva001E9A00(Object*,float,float*,Rva00375A73Context*);};
class Rva001E46E1 {public:float rva001E46E1(Object*);void rva001E546B(Object*);};
class Rva002618A2 {public:Rva002618A2*rva002618A2(int,int,int,int);unsigned words[7];};
class BfmeFixedStorage0004543D {public:unsigned char data[28];};
class Rva000421C8 {public:Rva000421C8():m_next(0){}virtual~Rva000421C8(){}virtual bool allow(Object*)=0;virtual int getPlayerMask(){return -1;}Rva000421C8*m_next;};
class Rva0004584D:public Rva000421C8 {public:Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&);virtual~Rva0004584D(){}virtual bool allow(Object*);BfmeFixedStorage0004543D m_08,m_24;};
extern unsigned char g_00DFEFA4StoragePrototype[28];
#include "PartitionRangeQueryCallView.h"
extern PartitionManager*ThePartitionManager;
float GetGameLogicRandomValueReal(float,float,char*,int);float normalizeAngle(float);
enum CommandSourceType;
class AICommandInterface {public:void aiIdle(CommandSourceType);};
class Thing {public:float getHeightAboveTerrain()const;void setPosition(const Coord3D*);};
class AIHolder {public:
virtual int rvaSlot0();
virtual int rvaSlot1();
virtual int rvaSlot2();
virtual int rvaSlot3();
virtual int rvaSlot4();
virtual int rvaSlot5();
virtual int rvaSlot6();
virtual int rvaSlot7();
virtual int rvaSlot8();
virtual int rvaSlot9();
virtual int rvaSlot10();
virtual int rvaSlot11();
virtual int rvaSlot12();
virtual int rvaSlot13();
virtual int rvaSlot14();
virtual int rvaSlot15();
virtual int rvaSlot16();
virtual int rvaSlot17();
virtual int rvaSlot18();
virtual int rvaSlot19();
virtual int rvaSlot20();
virtual int rvaSlot21();
virtual int rvaSlot22();
virtual int rvaSlot23();
virtual int rvaSlot24();
virtual int rvaSlot25();
virtual int rvaSlot26();
virtual int rvaSlot27();
virtual int rvaSlot28();
virtual int rvaSlot29();
virtual int rvaSlot30();
virtual int rvaSlot31();
virtual int rvaSlot32();
virtual int rvaSlot33();
virtual int rvaSlot34();
virtual int rvaSlot35();
virtual int rvaSlot36();
virtual int rvaSlot37();
virtual int rvaSlot38();
virtual int rvaSlot39();
virtual int rvaSlot40();
virtual int rvaSlot41();
virtual int rvaSlot42();
virtual int rvaSlot43();
virtual int rvaSlot44();
virtual int rvaSlot45();
virtual int rvaSlot46();
virtual int rvaSlot47();
virtual int rvaSlot48();
virtual int rvaSlot49();
virtual int rvaSlot50();
virtual int rvaSlot51();
virtual int rvaSlot52();
virtual int rvaSlot53();
virtual int rvaSlot54();
virtual int rvaSlot55();
virtual int rvaSlot56();
virtual int rvaSlot57();
virtual int rvaSlot58();
virtual int rvaSlot59();
virtual int rvaSlot60();
virtual int rvaSlot61();
virtual int rvaSlot62();
virtual int rvaSlot63();
virtual int rvaSlot64();
virtual int rvaSlot65();
virtual int rvaSlot66();
virtual int rvaSlot67();
virtual int rvaSlot68();
virtual int rvaSlot69();
virtual int rvaSlot70();
virtual int rvaSlot71();
virtual int rvaSlot72();
virtual int rvaSlot73();
virtual int rvaSlot74();
virtual int rvaSlot75();
virtual int rvaSlot76();
virtual int rvaSlot77();
virtual int rvaSlot78();
virtual int rvaSlot79();
virtual int rvaSlot80();
virtual int rvaSlot81();
virtual int rvaSlot82();
virtual int rvaSlot83();
virtual int rvaSlot84();
virtual int rvaSlot85();
virtual int rvaSlot86();
virtual int rvaSlot87();
virtual int rvaSlot88();
virtual int rvaSlot89();
virtual int rvaSlot90();
virtual int rvaSlot91();
virtual int rvaSlot92();
virtual int rvaSlot93();
virtual int rvaSlot94();
virtual int rvaSlot95();
virtual int rvaSlot96();
virtual int rvaSlot97();
virtual int rvaSlot98();
virtual int rvaSlot99();
virtual int rvaSlot100();
virtual int rvaSlot101();
virtual int rvaSlot102();
virtual int rvaSlot103();
virtual int rvaSlot104();
virtual int rvaSlot105();
virtual int rvaSlot106();
virtual int rvaSlot107();
virtual int rvaSlot108();
virtual int rvaSlot109();
virtual int rvaSlot110();
virtual int rvaSlot111();
virtual int rvaSlot112();
virtual int rvaSlot113();
virtual int rvaSlot114();
virtual int rvaSlot115();
virtual int rvaSlot116();
virtual int rvaSlot117();
virtual int rvaSlot118();
virtual int rvaSlot119();
virtual int rvaSlot120();
virtual int rvaSlot121();
virtual int rvaSlot122();
virtual int rvaSlot123();
virtual int rvaSlot124();
virtual int rvaSlot125();
virtual int rvaSlot126();
virtual int rvaSlot127();
virtual int rvaSlot128();
virtual int rvaSlot129();
virtual int rvaSlot130();
virtual int rvaSlot131();
virtual int rvaSlot132();
virtual int rvaSlot133();
virtual int rvaSlot134();
virtual int rvaSlot135();
virtual int rvaSlot136();
virtual int rvaSlot137();
virtual int rvaSlot138();
virtual int rvaSlot139();
virtual int rvaSlot140();
virtual int rvaSlot141();
virtual int rvaSlot142();
virtual int rvaSlot143();
};
struct TemplateView {char pad[0x108];unsigned char flags;};
enum ObjectStatusTypes;
class Object {public:
void setStatus(ObjectStatusTypes,bool);
char opaque00[4];TemplateView*template04;char pad08[0x38-8];Coord3D position;float orientation;
char pad48[0xB8-0x48];float radiusB8;char padBC[0x258-0xBC];AIHolder*ai258;
};
class AIUpdateInterface {public:void chooseGoodLocomotorFromCurrentSet();};
class GiantBirdAIUpdate {public:
int rva0036B567();void rva00368D12();
char pad00[8];Object*object08;char pad0c[0x1F0-0xC];Locomotor*locomotor1F0;
char pad1f4[0x3BD-0x1F4];bool dead3BD;char pad3be[0x4C8-0x3BE];Rva00375A73Context context4C8;
int goal528;float angle52C;float distance530;bool reached534;
};
void GiantBirdAIUpdate::rva00368D12(){
 Object*object=object08;float radius=object->radiusB8;Coord3D position;position.x=object->position.x;position.y=object->position.y;position.z=object->position.z;
 Rva002618A2 mask;
 Rva0004584D filter(*(const BfmeFixedStorage0004543D*)mask.rva002618A2(0,7,10,11),*(const BfmeFixedStorage0004543D*)g_00DFEFA4StoragePrototype);
 Object*near=ThePartitionManager->getClosestObject(&position,radius*2.0f,0,&filter);
 if(near){
  Coord3D away;away.x=position.x-near->position.x;away.y=position.y-near->position.y;away.z=0;
  away.normalize();away.x*=2.0f;away.y*=2.0f;away.z*=2.0f;
  away.x+=GetGameLogicRandomValueReal(-0.1f,0.1f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp",0xEB4);
  double dy=GetGameLogicRandomValueReal(-0.1f,0.1f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp",0xEB5)+away.y;
  position.z=((volatile float& )position.z)+away.z;position.x=((volatile float& )position.x)+away.x;position.y+=dy;((Thing*)object)->setPosition(&position);
 }
}
int GiantBirdAIUpdate::rva0036B567(){
 if(object08->template04->flags&4)return 0x3FFFFFFF;
 ((AIUpdateInterface*)this)->chooseGoodLocomotorFromCurrentSet();
 Locomotor*locomotor=locomotor1F0;
 if(locomotor && (!dead3BD || *((bool*)*(void**)((char*)locomotor+4)+0xD0))){
  switch(goal528){
   case 3:rva00368D12();((Rva001E46E1*)locomotor)->rva001E546B(object08);reached534=true;break;
   case 2:
    locomotor->locoUpdate_moveTowardsAngle(object08,angle52C);
    if(fabs(normalizeAngle(object08->orientation)-normalizeAngle(angle52C))<0.1f){
     AIHolder*ai=object08->ai258;
     ((AICommandInterface*)((char*)ai+0x20))->aiIdle((CommandSourceType)ai->rvaSlot143());return 1;
    }break;
   case 1:
    {float speed=((Rva001E46E1*)locomotor)->rva001E46E1(object08); Object*obj=object08;reached534=locomotor->rva001E9A00(obj,speed,&distance530,&context4C8);}break;
  }
  int desired=*(int*)((char*)*(void**)((char*)locomotor+4)+0xC0);
  if(((Thing*)object08)->getHeightAboveTerrain()>(float)desired)object08->setStatus((ObjectStatusTypes)6,true);else object08->setStatus((ObjectStatusTypes)6,false);
 }
 return 1;
}
