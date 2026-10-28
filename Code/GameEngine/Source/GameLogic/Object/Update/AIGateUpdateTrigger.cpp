// cl: /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii

struct GateOffset {
 float X,Y,Z;
 GateOffset(float xCoord,float yCoord,float zCoord):X(xCoord),Y(yCoord),Z(zCoord){}
 __forceinline void rotate(float s,float c) {
  float tx=X,ty=Y;
  X=c*tx-s*ty;
  Y=s*tx+c*ty;
 }
};
// WB122F280 names loadTrigger; native4B0AAA..4B0C27 is381B. BF1
// PolygonTrigger donor supplies registration/name purpose; native virtual
// shape/name40/id44 and100B extent use verified CastleBehavior sibling.
// Retail keeps the CRT float wrappers from other units: import them here so
// this unit inlines them without emitting its own competing out-of-line copies.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")
#include "ascii_string.h"
#include "reference/shims/wwmath/Vector2.h"
class Rva00330C50Interface {public:~Rva00330C50Interface(){} virtual void s0()=0;virtual void s1()=0;virtual void s2()=0;virtual void s3()=0;virtual void s4()=0;virtual void s5()=0;virtual void s6()=0;};
// ABI view only: external constructor166B proves its most-derived flag and
// 100-byte allocation; the loader reads name40/id44 and calls slot1.
class PolygonTrigger:public virtual Rva00330C50Interface {public:
 PolygonTrigger(int);static void addPolygonTrigger(PolygonTrigger *); __forceinline int getID()const{return id;} __forceinline StringBase<char> &getName(){return *(StringBase<char> *)&name;}
 virtual void *deleteInstance(int);virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();
 char pad08[0x38];AsciiString name;int id;char pad48[0x14];
};
typedef char PolygonExtent[sizeof(PolygonTrigger)==100?1:-1];
class PolygonPointCalls {public:virtual void slot0();virtual void addBoundaryPoint(const Vector2 &);};
class Rva002E3766Holder {public:void set(int,int);};
extern int Rva00A03D80;
enum Relationship { RELATION_0,RELATION_1,RELATION_2 };
class Object {public:Relationship getRelationship(const Object *) const;char pad[0x38];float px,py,pz,angle;};

struct AIGateUpdateModuleData {char pad[8];float width,height;};
class AIGateUpdate {public:
 void loadTrigger();Vector2 rva004B0A24(float,float);
 static void rva004B09E7(Object *,AIGateUpdate *,bool);
 char pad00[4];const AIGateUpdateModuleData *data;Object *object;char pad0C[0x18];int triggerID,count28,count2C;bool loaded,enabled;
};
// Keeping the verified rotation helper visible in this unit restores all
// native return-temporary homes; all three bodies match retail together.
void AIGateUpdate::loadTrigger() {
 const AIGateUpdateModuleData *aIGateUpdateModuleData=data;
 if(aIGateUpdateModuleData->width>0.0f && aIGateUpdateModuleData->height>0.0f) {
  float halfX=aIGateUpdateModuleData->width*0.5f,halfY=aIGateUpdateModuleData->height*0.5f;
  PolygonTrigger *polygon=new PolygonTrigger(1);
  void (PolygonPointCalls::*add)(const Vector2 &)=&PolygonPointCalls::addBoundaryPoint;
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

// Native callback4B09E7 is embedded in loadTrigger4B0AAA at4B0BBC;
// complete entry through4B0A24 is61B. It classifies the entering/leaving
// object relative to owner+8 and adjusts counters28/2C; names unresolved.
void AIGateUpdate::rva004B09E7(Object *o,AIGateUpdate *gate,bool entered) {
 Relationship relationship=o->getRelationship(gate->object);
 if(entered) {
  switch(relationship) {case RELATION_0:++gate->count2C;break;case RELATION_2:++gate->count28;break;}
 } else {
  switch(relationship) {case RELATION_0:--gate->count2C;break;case RELATION_2:--gate->count28;break;}
 }
}

// Native4B0A24..4B0AAA RET12, called four times by loadTrigger.
// Rotate the supplied XY by owner Object angle44 and translate by position38/3C.
// Helper name unknown. Retail proves an eight-byte XY result; Vector2 is the
// donor-compatible representation, not an independently recovered target type.
// WB122F5A0 inlines Vector3::Rotate_Z from vector3.h. GateOffset preserves that
// donor pattern at BFME1 revision9e3be919; local type spelling is neutral.
Vector2 AIGateUpdate::rva004B0A24(float x,float offsetY) {
 GateOffset v(x,offsetY,0);
 float a=object->angle;
 float sinAngle=(float)sin(a),c=(float)cos(a);
 const float &ss=sinAngle,&cc=c;
 v.rotate(ss,cc);
 return Vector2(object->px+v.X,object->py+v.Y);
}
