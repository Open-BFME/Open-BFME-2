// ?rva00397D0A@CastleBehavior@@QAEX_N@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Target326B and WB ebb1c0 corroborate module ownership/owned-building flow;
// original method name unresolved. Target establishes offsets and callees;
// size()>0 reproduces the signed shift in the native count check. Both static
// key unwind states and native strings match all 326 bytes.
// Target callback producer/status cleanup395EB8 independently recovered.
#include <vector>
#include "GameLogicObjectLookupView.h"
enum NameKeyType{NAMEKEY_INVALID=0};
enum ObjectStatusTypes{STATUS79=79};
enum DamageType{DAMAGE8=8};enum DeathType{DEATH0=0};
class Module;class Object{friend class CastleBehavior;protected:Module*findModule(NameKeyType)const;public:void kill(DamageType,DeathType);};
class NameKeyGenerator{public:NameKeyType nameToKey(const char*);};extern NameKeyGenerator*TheNameKeyGenerator;
class FXList{public:static void doFXObj(const FXList*,const Object*,const Object*);};
class LifetimeUpdate{public:void rva003A4AD2();};
class Rva002918E0Object{public:void rva004B239A(unsigned char,unsigned char);};
extern GameLogic*TheGameLogic;
struct CastleData{char pad[0x48];const FXList*fx;};
class CastleBehavior{public:void rva00397D0A(bool);void rva00395EB8(Object*);void rva00397B03(ObjectStatusTypes,bool);char prefix[4];CastleData*data;Object*object;char pad0C[0x5C];_STL::vector<ObjectID>owned68;};
void CastleBehavior::rva00397D0A(bool killObjects){
 _STL::vector<ObjectID>*vec=&owned68;
 for(_STL::vector<ObjectID>::iterator it=vec->begin();it!=owned68.end();++it){
 Object*owned=TheGameLogic->findObjectByID(*it);if(!owned)continue;
 rva00395EB8(owned);
 if(killObjects){owned->kill(DAMAGE8,DEATH0);}else{
  static NameKeyType key=TheNameKeyGenerator->nameToKey("EntEnragedUpdate");
  Module*m=owned->findModule(key);if(m)((Rva002918E0Object*)m)->rva004B239A(1,1);
  static NameKeyType lifetime=TheNameKeyGenerator->nameToKey("LifetimeUpdate");
  m=owned->findModule(lifetime);if(m)((LifetimeUpdate*)m)->rva003A4AD2();
 }
 }
 if(vec->size()>0 && !killObjects && data->fx) FXList::doFXObj(data->fx,object,0);
 vec->erase(vec->begin(),vec->end());rva00397B03(STATUS79,false);
}
