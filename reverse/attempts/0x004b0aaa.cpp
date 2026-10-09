// ?loadTrigger@AIGateUpdate@@QAEXXZ
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// WB122F280 names loadTrigger; native4B0AAA..4B0C27 is381B. BF1
// PolygonTrigger donor supplies registration/name purpose; native virtual
// shape/name40/id44 and100B extent use verified CastleBehavior sibling.
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
class AIGatePoint:public Coord2D {public:__forceinline AIGatePoint(const AIGatePoint &p){x=p.x;y=p.y;} };
class Rva00330C50Interface {public:~Rva00330C50Interface(){} virtual void s0()=0;virtual void s1()=0;virtual void s2()=0;virtual void s3()=0;virtual void s4()=0;virtual void s5()=0;virtual void s6()=0;};
class PolygonTrigger:public virtual Rva00330C50Interface {public:
 PolygonTrigger(int);static void addPolygonTrigger(PolygonTrigger *); __forceinline int getID()const{return id;} __forceinline StringBase<char> &getName(){return *(StringBase<char> *)&name;}
 virtual void *deleteInstance(int);virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();
 char pad08[0x38];AsciiString name;int id;char pad48[0x14];
};
typedef char PolygonExtent[sizeof(PolygonTrigger)==100?1:-1];
class PolygonPointCalls {public:virtual void slot0();virtual void addBoundaryPoint(const AIGatePoint &);};
class Rva002E3766Holder {public:void set(int,int);};
extern int Rva00A03D80;
class Object;
struct AIGateUpdateModuleData {char pad[8];float width,height;};
class AIGateUpdate {public:
 void loadTrigger();AIGatePoint rva004B0A24(float,float);
 static void rva004B09E7(Object *,AIGateUpdate *,bool);
 char pad00[4];const AIGateUpdateModuleData *data;Object *object;char pad0C[0x18];int triggerID,count28,count2C;bool loaded,enabled;
};
void AIGateUpdate::loadTrigger() {
 const AIGateUpdateModuleData *d=data;
 if(d->width>0.0f && d->height>0.0f) {
  float halfX=d->width*0.5f,halfY=d->height*0.5f;
  PolygonTrigger *polygon=new PolygonTrigger(1);
  void (PolygonPointCalls::*add)(const AIGatePoint &)=&PolygonPointCalls::addBoundaryPoint;
  (((PolygonPointCalls*)polygon)->*add)(rva004B0A24(halfX,halfY));
  (((PolygonPointCalls*)polygon)->*add)(rva004B0A24(halfX,-halfY));
  (((PolygonPointCalls*)polygon)->*add)(rva004B0A24(-halfX,-halfY));
  (((PolygonPointCalls*)polygon)->*add)(rva004B0A24(-halfX,halfY));
  ((Rva002E3766Holder*)polygon)->set((int)&AIGateUpdate::rva004B09E7,(int)this);
  AsciiString name;name.format("AIGateUpdateTrigger_%d",Rva00A03D80++);
  StringBase<char> &polygonName=polygon->getName();
  polygonName.set(*(const StringBase<char> *)&name);PolygonTrigger::addPolygonTrigger(polygon);triggerID=polygon->getID();
 }
 loaded=true;
}
