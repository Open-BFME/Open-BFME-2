// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// WB136EAF0 names AIBuilder::update; native4ECB19..4ECD9F RET0 full646.
// BF1/ZH lack this BF2 controller. Caller SkirmishAI and existing owner rows
// prove AIBuilder; accessed fields and virtual slots below are target facts.
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
#include <vector>
#include <list>
class Player;class Object{public:char pad[0x74];ObjectID id;};
extern GameLogic*TheGameLogic;
class Rva004E9378{public:bool rva004E9378();};
class Rva00506B1B{public:void rva00506B2F();};
class Rva0055ADD8{public:int rva0055ADD8(int);};
class AIBuildable{public:int doCanMake(Player*);bool doBuild(Player*);};
class AIUnitBuilder{public:Object*Rva005982EA(const AsciiString*,_STL::vector<ObjectID>*,bool);};
struct Rva005996FFArg;
class Rva005996FF{public:void rva005996FF(Rva005996FFArg*,bool);};
class AIDozerManager{public:void*rva00599870(const Coord3D&,int);void rva00599EDC();char data[0x14];};
// Existing dozer callee pin retains its opaque four-byte return spelling;
// this caller consumes those bits as ObjectID without dereferencing them.
class Rva004ECB19Entry{
public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
 virtual bool slot04();virtual void slot05();virtual void slot06();virtual void slot07(int);
 virtual void slot08();virtual void slot09();virtual void slot10();virtual bool slot11();
 virtual void slot12();virtual Coord3D slot13();
 float word04;ObjectID producer08;AsciiString name0C;char gap10[0x28-0x10];bool flag28;
};
class AIBuilder{
public:void update();void rva004ECA01();void rva004EC700();void moneySaverUpdate();
 Player*owner00;char gap04[0x130-4];_STL::vector<void*>entries130;_STL::list<int>orders13C;AIDozerManager dozer140;
};
void AIBuilder::update(){
 _STL::list<int>::iterator order=orders13C.begin();
 while(order!=orders13C.end()){
  if(((Rva004E9378*)*order)->rva004E9378())order=orders13C.erase(order);else ++order;
 }
 rva004ECA01();
 ((Rva00506B1B*)((char*)this+4))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0xE4))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0x38))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0x90))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0xC0))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0x108))->rva00506B2F();
 ((Rva00506B1B*)((char*)*(void**)((char*)this+0x12C)+0xC))->rva00506B2F();
 _STL::vector<void*>::iterator it=entries130.begin();
 while(it!=entries130.end()){
  Rva004ECB19Entry*entry=(Rva004ECB19Entry*)*it;
  if(((Rva004E9378*)entry)->rva004E9378())it=entries130.erase(it);
  else{entry->slot05();++it;}
 }
 if(!entries130.empty()){
  unsigned dozerCount=((_STL::list<int>*)((char*)&dozer140+4))->size();
  rva004EC700();
  for(it=entries130.begin();it!=entries130.end();++it){
   Rva004ECB19Entry*entry=(Rva004ECB19Entry*)*it;bool assigned=false;
   if(entry->slot11()){
    Object*created=((AIUnitBuilder*)((char*)this+0x38))->Rva005982EA(&entry->name0C,0,false);
    if(created){
    entry->producer08=created->id;assigned=true;}else{if(0){AsciiString unused;}entry->producer08=INVALID_OBJECT_ID;continue;}
   }
   if(entry->slot04()&&entry->flag28){entry->producer08=(ObjectID)(unsigned)dozer140.rva00599870(entry->slot13(),0);assigned=true;}
   int can=((AIBuildable*)entry)->doCanMake(owner00);
   if(can==0||(can==8&&dozerCount>0)||can==2){
    Rva004ECB19Entry*selected=entry;
    bool success=false;
    if(can==0){
     if(((AIBuildable*)selected)->doBuild(owner00)){
      orders13C.push_back((const int&)selected);selected->slot07(1);
      if(selected->slot04())((Rva005996FF*)&dozer140)->rva005996FF((Rva005996FFArg*)TheGameLogic->findObjectByID(selected->producer08),false);
      success=true;
     }else ((Rva0055ADD8*)selected)->rva0055ADD8((int)owner00);
     entries130.erase(it);
    }
    if(!success&&assigned)selected->producer08=INVALID_OBJECT_ID;
    break;
   }
   if(assigned)entry->producer08=INVALID_OBJECT_ID;
   if(can==10)((Rva0055ADD8*)entry)->rva0055ADD8((int)owner00);
  }
 }
 for(it=entries130.begin();it!=entries130.end();){
  if(((Rva004E9378*)*it)->rva004E9378())it=entries130.erase(it);else ++it;
 }
 dozer140.rva00599EDC();moneySaverUpdate();
}
