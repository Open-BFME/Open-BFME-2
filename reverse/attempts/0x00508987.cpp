// ?rva00508987@Made002CC64B@@QAEXPAURva00508987Weapon@@PAVObject@@@Z
// partial score=0.9954787515429377 date=2026-10-10
// cl: /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "vector3.h"
#include "GameLogicObjectLookupView.h"
// Native00508987..00508B9E full535B; Made002CC64B parser2CC64B
// establishes AttributeModifierNugget ownership. Constructor508BE5 and
// destructor508CF7 agree with128 name/134 angle/138 mask/13C FX fields.
// Current function name is neutral; source lookup and angular condition,
// attribute pool calls, positive duration and optionalFX follow target bytes.
// BFME1 vector3.h supplies source normalization. Component subtractions are
// essential: fused delta expressions diverge; only two X/Z operand bytes
// in the second squared-length load order remain.
class FXList;
class AttributeModifierPoolUpdate {public:void rva00403415(int*,int);};
class Made002CC64B;
class Object {
 friend class Made002CC64B;
 AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate()const;
public:
 char pad[8];float matrix[12];Vector3 position;
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
  Vector3 delta(target->position);
  delta.X-=source->position.X;delta.Y-=source->position.Y;delta.Z-=source->position.Z;
  Vector3 facing(source->matrix[0],source->matrix[4],source->matrix[8]);
  Vector3 direction(delta);
  facing.Normalize();direction.Normalize();
  if(Vector3::Dot_Product(direction,facing)<Cos(angle))return;
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
