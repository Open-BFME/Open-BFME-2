// cl: /I. /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
class WWMath{public:static float __fastcall Inv_Sqrt(float);};struct AttributeLocalVector{float X,Y,Z;AttributeLocalVector(){} AttributeLocalVector(float x,float y,float z):X(x),Y(y),Z(z){} AttributeLocalVector(const AttributeLocalVector&v):X(v.X),Y(v.Y),Z(v.Z){} float Length2()const{return X*X+Y*Y+Z*Z;} __forceinline void Normalize(){float len2=Length2();if(len2!=0.0f){float inv=WWMath::Inv_Sqrt(len2);X*=inv;Y*=inv;Z*=inv;}} static float Dot_Product(const AttributeLocalVector&a,const AttributeLocalVector&b){return a.X*b.X+a.Y*b.Y+a.Z*b.Z;}};
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
// Native 00508987..00508B9E, RET8. The named AttributeModifierNugget
// parser 002CC64B and field table 00864300 identify the owner; constructor
// 00508BE5 and destructor 00508CF7 corroborate name128/angle134/mask138/FX13C.
// BFME1 575ba2b04 vector normalization and Coord3D point operations guide
// the arithmetic; target calls/layouts are independently measured. Explicit
// point set/sub close the two X/Z load operands, as in the Paralyze sibling.
// The local vector type avoids competing with shared Vector3 constructor copies.
// Receiver/provider view spellings remain ABI names, not application identity.
struct AttributeLocalPoint:Coord3D{__forceinline void set(const float*p){x=p[0];y=p[1];z=p[2];} __forceinline void sub(const float*p){x-=p[0];y-=p[1];z-=p[2];}};
class FXList;
class AttributeModifierPoolUpdate {public:void rva00403415(int*,int);};
class Made002CC64B;
class Object {
 friend class Made002CC64B;
 AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate()const;
public:
 char pad[8];float matrix[12];Coord3D position;
 bool addAttributeModifierToPool(const AsciiString&,int);
};
enum NameKeyType{KEY0=0};class NameKeyGenerator{public:NameKeyType nameToKey(const char*);};extern NameKeyGenerator *TheNameKeyGenerator;
class AttributeModifierStore{public:int rva00214713(int);void*getDuration(int);};extern AttributeModifierStore *TheAttributeModifierStore;
class FXList {public:static void doFXObj(const FXList*,const Object*,const Object*);};
extern GameLogic *TheGameLogic;
float Cos(float);
struct Rva00508987Weapon {char pad[8];ObjectID id;};
class Made002CC64B {public:
 void rva00508987(Rva00508987Weapon*,Object*);
 char pad[0x128];AsciiString name;char pad12c[8];float angle;int mask;FXList *fx;
};
void Made002CC64B::rva00508987(Rva00508987Weapon *weapon,Object *target){
 Object*source=TheGameLogic->findObjectByID(weapon->id);
 if(angle<3.1415927f && source){
  AttributeLocalPoint delta;delta.set(&target->position.x);delta.sub(&source->position.x);
  AttributeLocalVector facing(source->matrix[0],source->matrix[4],source->matrix[8]);
  AttributeLocalVector direction(delta.x,delta.y,delta.z);
  facing.Normalize();direction.Normalize();
  if(AttributeLocalVector::Dot_Product(direction,facing)<Cos(angle))return;
 }
 if(!name.isEmpty()){
  target->addAttributeModifierToPool(name,-1);
  AttributeModifierPoolUpdate *pool=target->findAttributeModifierPoolUpdate();
  if(pool){
   int index=TheAttributeModifierStore->rva00214713((int)TheNameKeyGenerator->nameToKey(name.str()));
   int duration=(int)TheAttributeModifierStore->getDuration(index);
   if(duration>0){
    pool->rva00403415(&mask,TheGameLogic->getFrame()+duration);
    if(fx)FXList::doFXObj(fx,target,0);
   }
  }
 }
}
