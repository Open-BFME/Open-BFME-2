// ?canDoSpecialPowerAtLocation@ActionManager@@QAE_NPBVObject@@PBUCoord3D@@W4CommandSourceType@@PBVSpecialPowerTemplate@@0I_N@Z
// Retail 0x0041D60B (3709 B, EH handler 0x00786B5D). Stack homes: friend_getFinalOverride is declared
// throw() (retail 0x288609 is a 24-byte pointer walk), so its call no longer carries the function's
// last EH-state alias set; the castle-check distance is computed in its own block.
// cl: /O1 /arch:SSE /G7 /MD /GX /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// Retail RVA 41D60B; WB 110D180.
// Extent: 3521 instruction bytes through41E3CC, then188 switch bytes through41E488.
// Native RET1C and callers establish thiscall with seven arguments.
// WB ActionManager.cpp1782..2370 establishes identity and debug control flow.
// GeneralsMD ActionManager::canDoSpecialPowerAtLocation is the semantic guide;
// donor checkout cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Native BFME2 decides
// the cases, validator order, virtual slots, offsets, constants and callees.
// Address-derived helper/view names below preserve existing ledger spellings;
// their semantic role names are structural inferences, not new identities.
//
// This version has the native 1035-instruction sequence, branch/call/table
// relationships, frame 0x2B4 and every stack home of retail.
// Updated canonical handle/query declarations; see crack-j-0041d60b.json.
// See reverse/attempt_support/crack-e-0041d60b.json for the audited
// instructions, switch entries, EH states, stack homes and rejected trials.
// Helper41C9C4 must use the corrected member owner from commit5f1baada20.
// Session 2026-10-20 (opus): stack-home packing study in
// reverse/attempt_support/crack-o-0041d60b.md; farm-lever body kept at b1fa024ca3.
// Session 2026-10-20 (opus, agY): the frame residue was three EH-alias conflicts.
// A throwing call outside any destructor EH state also may-use the context set of
// the last EH funclet (case 0x48's scope, which holds every switch3 temporary, since
// MSVC hoists switch-body temporaries to the switch scope). That made the 0x55 alive
// and filter (may-def'd by the getRadius call) and the 0x52 castle delta (may-def'd by
// the shared ~GeometryInfo cleanup of the castle return) conflict with the healing
// alive and case 0x48 filter temporaries. Overridable::friend_getFinalOverride cannot
// throw (pointer walk), so it is declared throw(); the 0x52 castle distance is computed
// in its own block, so delta is out of scope at the castle return. Retail keeps the
// state reset before ~GeometryInfo, so that destructor stays throwing.
#include "Coord3D.h"
struct ActionLocationCoord:Coord3D {
 ActionLocationCoord(const Coord3D &p) { x=p.x;y=p.y;z=p.z; }
};
enum CommandSourceType { CMD_FROM_PLAYER };
enum SpecialPowerType { SPECIAL_INVALID };
enum NameKeyType { NAMEKEY_INVALID };
enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };
enum PathfindLayerEnum { LAYER_GROUND };
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED };
class Object; class Module; class Player; class SpecialPowerTemplate;
template<int N> class BitFlags { public: unsigned words[7]; };
extern BitFlags<116> KINDOFMASK_NONE;
class BfmeFixedStorage0004543D { public: BfmeFixedStorage0004543D(int,int); unsigned words[7]; };
struct Rva00045411BitSet { Rva00045411BitSet(int,int); unsigned words[7]; };
struct Rva0006EE7A { Rva0006EE7A(int,int,int); unsigned words[7]; };
class Rva002618A2 { public: Rva002618A2() {} Rva002618A2 *rva002618FA(int,int,int,int,int,int); unsigned words[7]; };
class Rva000421C8 {
public:
 Rva000421C8():next(0) {}
 virtual ~Rva000421C8() {}
 virtual bool allow(Object *)=0;
 virtual int getPlayerMask() { return -1; }
 Rva000421C8 *link(Rva000421C8 *);
 Rva000421C8 *next;
};
class Rva0004584D:public Rva000421C8 {
public:
 Rva0004584D(const BfmeFixedStorage0004543D &,const BfmeFixedStorage0004543D &);
 virtual ~Rva0004584D() {}
 virtual bool allow(Object *);
 BfmeFixedStorage0004543D yes,no;
};
class Rva0026119DFilter:public Rva000421C8 { public: virtual bool allow(Object *); };
// Native BFBC90 filter: object +8, relationship mask +C, bool +10.
class Rva00260EB1Filter:public Rva000421C8 {
public:
 Rva00260EB1Filter(const Object *o,int r,bool b):object(o),relationship(r),match(b) {}
 virtual bool allow(Object *);
 virtual int getPlayerMask();
 const Object *object; int relationship; bool match;
};
class BfmeRefCF { public: BfmeRefCF *bfmeAssignCF(const BfmeRefCF &); void *data; };
#include "PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
class GeometryInfo {
public:
 GeometryInfo(GeometryType,bool,float,float,float);
 virtual ~GeometryInfo();
 bool CollidesWith(const Coord3D &,float,const GeometryInfo &,const Coord3D &,float) const;
 char fields[0x58];
};
class Overridable { public: const Overridable *friend_getFinalOverride() const throw(); };
class SpecialPowerTemplate:public Overridable {
public:
 const SpecialPowerTemplate *final() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
 __declspec(dllimport) __forceinline SpecialPowerType getSpecialPowerType() const { return final()->type; }
 float getRadius() const { return final()->radius54; }
 float getRange() const { return final()->range50; }
 char pad[0x1c]; SpecialPowerType type; char pad20[0x30]; float range50,radius54;
};
#define V10(P) virtual void P##0();virtual void P##1();virtual void P##2();virtual void P##3();virtual void P##4();virtual void P##5();virtual void P##6();virtual void P##7();virtual void P##8();virtual void P##9();
class SpecialPowerModuleInterface {
public:
 virtual void v0(); virtual void v1(); virtual float getPercentReady() const;
 V10(a) virtual void v13();virtual void v14();virtual void v15();virtual void v16();virtual void v17();
 virtual bool ready(const Coord3D *);
};
class Rva00368594CmpBoolField { public: bool get() const; };
class ActionAIView { public: V10(a) V10(b) V10(c) V10(d) V10(e) V10(f) V10(g) V10(h) V10(i)
 virtual void v90();virtual void v91();virtual void v92();virtual void v93();virtual void v94();virtual void v95();virtual void v96();
 virtual Rva00368594CmpBoolField *specialAbility();
};
class BodyInterface { public: virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual float getHealth() const;virtual void v5();virtual float getMaxHealth() const; };
class Thing { public: bool isAnyKindOf(const BitFlags<69> &) const; };
struct Rva0028AC4EEntry;
class Object:public Thing {
public:
 bool hasSpecialPower(SpecialPowerType) const;
 SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *) const;
 Player *getControllingPlayer() const;
 protected: Module *findModule(NameKeyType) const; friend class ActionManager; public:
 const Rva0028AC4EEntry *rva0028AC4E() const;
 const Coord3D *position() const { return (const Coord3D *)((const char *)this+0x38); }
 const GeometryInfo &geometry() const { return *(const GeometryInfo *)((const char *)this+0xa8); }
 float angle() const { return *(const float *)((const char *)this+0x44); }
 float radius() const { return *(const float *)((const char *)this+0xb8); }
 ActionAIView *ai() const { return *(ActionAIView *const *)((const char *)this+0x258); }
 BodyInterface *body() const { return *(BodyInterface *const *)((const char *)this+0x254); }
 float construction() const { return *(const float *)((const char *)this+0x280); }
 const char *objectTemplate() const { return *(const char *const *)((const char *)this+4); }
};
class Player { public: int getPlayerIndex() const { return index; } char pad[0x54]; int index; };
class Locomotor { public: float getMaxSpeed(Object *) const; };
class Rva00395A60 { public: float rva00395A60(); };
class CastleBehavior { public: static NameKeyType rva0003955DA(); };
class Pathfinder { public: bool IsImpassableCell(int,int); };
class AI; extern AI *TheAI;
struct ActionAIManagerView { char pad[0x10]; Pathfinder *pathfinder; Pathfinder *getPathfinder() { return pathfinder; } };
class TerrainLogic {
public:
 V10(a) V10(b)
 virtual bool isUnderwater(float,float);
 virtual bool isCliff(float,float);
 PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
class ActionManager {
public:
 bool canDoSpecialPowerAtLocation(const Object *,const Coord3D *,CommandSourceType,const SpecialPowerTemplate *,const Object *,unsigned,bool);
 bool rva0041BA61(const Object *);
 bool rva0041C9C4(const Object *,const Coord3D *,const SpecialPowerTemplate *);
 bool rva0041CC65(const SpecialPowerTemplate *,const Coord3D *);
 bool rva0041CA9E(const Coord3D *,const Coord3D *,const SpecialPowerTemplate *);
 bool rva0041CB10(const Coord3D *,const SpecialPowerTemplate *);
 bool validLocationForCastingOnObjectFilter(const Object *,const Coord3D *,const SpecialPowerTemplate *);
 bool validateLocationForForbiddenObjects(const Object *,const Coord3D *,const SpecialPowerTemplate *);
};
#include "XYDistanceCallView.h"
// BfmeConv624.cpp owns the native 0x0027F108 query. This caller tests only
// the returned word; reuse that verified ABI without asserting a pointer result.
class BfmeThingCME { public: int rva0027F108(void *, float, int, int); };
#define STORAGE(X) (*(const BfmeFixedStorage0004543D *)&(X))
#define FILTER(K) Rva0004584D(BfmeFixedStorage0004543D(0,K),STORAGE(KINDOFMASK_NONE))

bool ActionManager::canDoSpecialPowerAtLocation(const Object *obj,const Coord3D *loc,CommandSourceType commandSource,const SpecialPowerTemplate *spTemplate,const Object *objectInWay,unsigned commandOptions,bool checkSourceRequirements)
{
 if(!spTemplate) return false;
 if(checkSourceRequirements && !obj->hasSpecialPower(spTemplate->getSpecialPowerType())) return false;
 if(rva0041BA61(obj)) return false;
 NameKeyType castleKey=CastleBehavior::rva0003955DA();
 SpecialPowerModuleInterface *mod=obj->getSpecialPowerModule(spTemplate);
 if(mod) {
  if(checkSourceRequirements) {
   if(mod->getPercentReady()<1.0f) return false;
   if(!mod->ready(0)) return false;
  }
  if(!mod->ready(loc)) return false;
  if(!rva0041CC65(spTemplate,loc)) return false;
  if(!rva0041CA9E(obj->position(),loc,spTemplate)) return false;
  if(!rva0041C9C4(obj,loc,spTemplate)) return false;
  if(!rva0041CB10(loc,spTemplate)) return false;
  if(!validLocationForCastingOnObjectFilter(obj,loc,spTemplate)) return false;
  if(!validateLocationForForbiddenObjects(obj,loc,spTemplate)) return false;
  switch(spTemplate->getSpecialPowerType()) {
  case 0x38:
   if(obj->ai() && obj->ai()->specialAbility() && !obj->ai()->specialAbility()->get()) return false;
  case 0x41:case 0x8c:
   if(TheTerrainLogic->isUnderwater(loc->x,loc->y)) return false;
  }
  switch(spTemplate->getSpecialPowerType()) {
  case 0x52:case 0x61:case 0x67:case 0x6a: {
   float radius=spTemplate->getRadius();
   GeometryInfo geometry(GEOMETRY_CYLINDER,false,20.0f,radius,radius);
   BfmeWideResult iter=ThePartitionManager->iterateObjectsInRange(loc,radius+500.0f,1,&FILTER(7),0);
   Object *target;
   while((target=iter.next())!=0) {
    float castleRadius=0.0f;
    Module *castle=target->findModule(castleKey);
    if(castle) {
     castleRadius=((Rva00395A60 *)castle)->rva00395A60();
     float distance;
     {
      ActionLocationCoord pos=*target->position();
      ActionLocationCoord delta=*loc;
      delta.x-=pos.x;delta.y-=pos.y;delta.z-=pos.z;
      distance=delta.length();
     }
     if(distance<radius+castleRadius) return false;
    } else { const GeometryInfo &other=target->geometry(); if(other.CollidesWith(*target->position(),target->angle(),geometry,*loc,0.0f)) return false; }
   }
   ActionLocationCoord center=*loc;
   int xmin=(int)(center.x-radius),xmax=(int)(center.x+radius);
   int ymin=(int)(center.y-radius),ymax=(int)(center.y+radius);
   for(int y=ymin;y<=ymax;y+=radius*0.2f) {
    for(int x=xmin;x<=xmax;x+=radius*0.2f) {
     if(TheTerrainLogic->isCliff((float)x,(float)y)) return false;
     if(TheTerrainLogic->isUnderwater((float)x,(float)y)) return false;
    }
   }
   return TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->getPlayerIndex(),loc)==CELLSHROUD_CLEAR;
  }
  case 0x55:case 0x56:case 0x5b:case 0x5d:case 0x5e:case 0x5f:case 0x73:case 0x76:case 0x78:case 0x7b:case 0x7c:case 0x7e:case 0x96: {
   float radius=spTemplate->getRadius();
   Rva0026119DFilter alive;

   Rva0004584D filter(STORAGE(KINDOFMASK_NONE),*(const BfmeFixedStorage0004543D *)Rva002618A2().rva002618FA(0,0x59,0x1e,0x2f,0x88,0xaf));
   BfmeWideResult iter=ThePartitionManager->iterateObjectsInRange(loc,radius,4,alive.link(&filter),0);
   Object *target;
   while((target=iter.next())!=0) {
    Rva0006EE7A mask(0,2,7);
    if(target->isAnyKindOf(*(const BitFlags<69> *)&mask)) {
     if(!(target->objectTemplate()[0x117]&1) && !(target->objectTemplate()[0x10e]&1)) return false;
    }
    if(*(const float *)(target->objectTemplate()+0x610)>100.0f) return false;
   }
   ((BfmeRefCF *)&iter)->bfmeAssignCF((const BfmeRefCF &)ThePartitionManager->iterateObjectsInRange(loc,radius+500.0f,0,&FILTER(0x78),0));
   while((target=iter.next())!=0) {
    Module *castle=target->findModule(castleKey);
    if(castle) {
     float castleRadius=((Rva00395A60 *)castle)->rva00395A60();
     ActionLocationCoord pos=*target->position(),delta=*loc;
     delta.x-=pos.x;delta.y-=pos.y;delta.z-=pos.z;
     float distance=delta.length();
     if(distance<radius+castleRadius) return false;
    }
   }
   ActionLocationCoord center=*loc;
   int xmin=(int)(center.x-radius),xmax=(int)(center.x+radius);
   int ymin=(int)(center.y-radius),ymax=(int)(center.y+radius);
   for(int y=ymin;y<=ymax;y+=radius*0.2f) {
    for(int x=xmin;x<=xmax;x+=radius*0.2f) {
     if(TheTerrainLogic->isCliff((float)x,(float)y)) return false;
     if(TheTerrainLogic->isUnderwater((float)x,(float)y)) return false;
    }
   }
   return TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->getPlayerIndex(),loc)==CELLSHROUD_CLEAR;
  }
  case 0x41: {
   if(!mod->ready(loc)) return false;
   Rva0004584D filter(BfmeFixedStorage0004543D(0,7),STORAGE(KINDOFMASK_NONE));
   if(ThePartitionManager->getClosestObject(loc,obj->radius(),1,&filter)) return false;
   if(TheTerrainLogic->getLayerForDestination(0,loc)!=1) return false;
   break;
  }
  case 0x8c: {
   Rva0004584D filter(BfmeFixedStorage0004543D(0,7),STORAGE(KINDOFMASK_NONE));
   if(ThePartitionManager->getClosestObject(loc,1.0f,0,&filter)) return false;
   PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(0,loc);
   if(((ActionAIManagerView *)TheAI)->getPathfinder()->IsImpassableCell((int)loc,layer)) return false;
   const Rva0028AC4EEntry *loco=obj->rva0028AC4E();
   if(loco && ((const Locomotor *)loco)->getMaxSpeed((Object *)obj)==0.0f) return false;
   break;
  }
  case 0x49: {
   PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(0,loc);
   if(((ActionAIManagerView *)TheAI)->getPathfinder()->IsImpassableCell((int)loc,layer)) return false;
   break;
  }
  }
  switch(spTemplate->getSpecialPowerType()) {
  case 10:case 0x1d:case 0x31:case 0x33:case 0x39:case 0x3b:case 0x40:case 0x44:case 0x45:case 0x47:case 0x4f:case 0x81:case 0x82:case 0x84:case 0x87:case 0x88:case 0x89:case 0x8a:case 0x8d:case 0x90:case 0x97:
   return false;
  case 0x10:case 0x1c:case 0x23:case 0x2a:case 0x2f:case 0x32:case 0x3f:case 0x41:case 0x43:case 0x50:case 0x54:case 0x6b:case 0x70:case 0x71:case 0x8c:case 0x8e:case 0x93:
   return TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->getPlayerIndex(),loc)==CELLSHROUD_CLEAR;
  case 0x34:case 0x35:case 0x36:case 0x3c:case 0x3d:case 0x3e:case 0x42:case 0x46:case 0x4b:case 0x4c:case 0x4e:case 0x51:case 0x53:case 0x58:case 0x5c:case 0x62:case 0x64:case 0x65:case 0x66:case 0x69:case 0x6c:case 0x6d:case 0x6e:case 0x72:case 0x75:case 0x77:case 0x79:case 0x7a:case 0x7d:case 0x7f:case 0x80:case 0x85:case 0x8f:case 0x98:
   return true;
  case 0x57: {
   if(spTemplate->getSpecialPowerType()==0x57) {
    int radius=(int)spTemplate->getRadius();

    BfmeWideResult iter=ThePartitionManager->iterateObjectsInRange(loc,(float)radius,0,Rva0026119DFilter().link(&FILTER(7))->link(&Rva00260EB1Filter(obj,4,false)),0);
    Object *target;
    while((target=iter.next())!=0) {
     float progress=target->construction();
     if(progress>=0.0f && progress<99.0f) continue;
     {
      float health=target->body()->getHealth(),maxHealth=target->body()->getMaxHealth();
      if(health<maxHealth) return true;
     }
    }
    return false;
   }
   return false;
  }
  case 0x59:case 0x68: {
   int radius=(int)spTemplate->getRadius();
   ActionLocationCoord center=*loc;
   int xmin=(int)(center.x-radius),xmax=(int)(center.x+radius);
   int ymin=(int)(center.y-radius),ymax=(int)(center.y+radius);
   for(int y=ymin;y<=ymax;y+=radius/5) for(int x=xmin;x<=xmax;x+=radius/5)
    if(TheTerrainLogic->isCliff((float)x,(float)y)) return false;
   return (TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->getPlayerIndex(),loc)!=CELLSHROUD_SHROUDED) ? true : false;
  }
  case 0x5a:case 0x6f: return true;
  case 0x63: {
   if(ThePartitionManager->getClosestObject(loc,200.0f,0,&FILTER(0x3c))) return false;
   ActionLocationCoord center=*loc;
   int xmin=(int)(center.x-200.0f),xmax=(int)(center.x+200.0f);
   int ymin=(int)(center.y-200.0f),ymax=(int)(center.y+200.0f);
   for(int y=ymin;y<=ymax;y+=40) for(int x=xmin;x<=xmax;x+=40)
    if(TheTerrainLogic->isCliff((float)x,(float)y)) return false;
   return (TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->getPlayerIndex(),loc)==CELLSHROUD_CLEAR) ? true : false;
  }
  case 0x48:case 0x49:case 0x4a: {
   int radius=(int)spTemplate->getRadius();
   ActionLocationCoord center=*loc;
   int xmin=(int)(center.x-radius),xmax=(int)(center.x+radius);
   int ymin=(int)(center.y-radius),ymax=(int)(center.y+radius);
   for(int y=ymin;y<=ymax;y+=radius/5) for(int x=xmin;x<=xmax;x+=radius/5) {
    if(TheTerrainLogic->isCliff((float)x,(float)y)) return false;
    if(TheTerrainLogic->isUnderwater((float)x,(float)y)) return false;
   }
   if(ThePartitionManager->getClosestObject(loc,(float)radius,0,&FILTER(0x3c))) return false;
   return (TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->getPlayerIndex(),loc)==CELLSHROUD_CLEAR) ? true : false;
  }
  case 0x92: {
   float range=spTemplate->getRange();
   if(((Rva000CBA20 *)obj)->distSq((const Rva000CBA20Point *)loc)<=range*range) return true;
   return false;
  }
  case 0x38:case 0x4d:case 0x60:case 0x86:case 0x91:case 0x94:case 0x95:case 0x99:
   return TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->getPlayerIndex(),loc)!=CELLSHROUD_SHROUDED;
  case 0x27: return reinterpret_cast<BfmeThingCME *>(TheTerrainLogic)->rva0027F108(const_cast<Coord3D *>(loc),5.0f,1,1)!=0;
  }
 }
 return false;
}
