// cl: /G7 /O1 /arch:SSE /Ob2 /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /I.
// GettingBuiltBehavior::rva0045479A, retail 0x0045479A (513 B): the per-tick
// self-heal gate of the construction behavior (owned caller 0x00454DF9). Original
// method name unknown; WB 0x0116FCD0 has the same call graph (target fact).
// The primary receiver and fields follow the owned ctor and interface sibling units.
// Target facts from the retail EH map (3 states): the range filter is a TEMPORARY of the
// iterateObjectsInRange call (state 0 over the call, the result object registered twice:
// state 1 under it, state 2 after it), so the result is destroyed with the unwind state -1.
// Structural inferences (codegen levers, no behavioural meaning): the scoped `out`
// local lets it share a frame slot with `body`; the dead `if (0) throw 1;` after the last
// statement restores sibling-block frame slot merging that an EH object otherwise disables.
#include "ascii_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
class Player;
#include "../../../../Include/GameLogic/PartitionFilter.h"
#include "../../../../Include/GameLogic/Rva002614ECFilter.h"
class Rva0045342FBody {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual float health();virtual void slot5();virtual float maxHealth();
};
struct GettingBuiltTemplateView { unsigned char pad[0x11b]; unsigned char kindFlags; };
class Object {
public:
 Player *getControllingPlayer() const;
 bool rva0028C264(int *,int);
 unsigned char pad0[4];GettingBuiltTemplateView *tmplate;
 unsigned char pad8[0x38-8];Coord3D position;
 unsigned char pad44[0x7c-0x44];ObjectID builderID;
 unsigned char pad80[0x254-0x80];Rva0045342FBody *body;
 unsigned char pad258[0x438-0x258];unsigned char privateStatus;
};
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
struct GettingBuiltBehaviorTickData {
 unsigned char pad[0x14];AsciiString builder;
 unsigned char pad18[0x2c-0x18];bool nearby;
 unsigned char pad2d[0x40-0x2d];void *filter;
 float radius;bool countdown;
};
class GettingBuiltTickInterface {
public:
 virtual void slot0();virtual void start(bool);virtual void slot2();virtual void slot3();
 virtual void slot4();virtual void slot5();virtual bool active();
};
// 0x00453124 is the matched BfmeThingE63::isValid (BfmeConv815.cpp); called on this.
#include "../../../../Include/GameLogic/Module/BfmeThingE63.h"
class GettingBuiltBehavior {
public:
 void rva00453D92();bool rva00453DCF();void rva0045479A();
 void *vptr;const GettingBuiltBehaviorTickData *data;Object *object;
 unsigned char padC[0x20-0xc];GettingBuiltTickInterface iface;
 int state;float timer;unsigned char pad2c[0x35-0x2c];bool flag35;
 unsigned char pad36[0x3e-0x36];bool flag3e;
};
void GettingBuiltBehavior::rva0045479A()
{
 rva00453D92();flag3e=rva00453DCF();
 const GettingBuiltBehaviorTickData *gettingBuiltBehaviorTickData=data;
 Object *obj=object;
 {
 Rva0045342FBody *body=obj->body;
 if (!body) return;
 if (obj->privateStatus&1) {
   if (!gettingBuiltBehaviorTickData->nearby) return;
   BfmeWideResult result=ThePartitionManager->iterateObjectsInRange(&obj->position,gettingBuiltBehaviorTickData->radius,1,&Rva002614ECFilter(&gettingBuiltBehaviorTickData->filter,obj->getControllingPlayer(),true),0);
   Object *found;
   while ((found=result.next())!=0) if (found!=obj && !(found->privateStatus&1)) return;
 }
 if (!(body->health()<body->maxHealth())) return;
 }
 if (reinterpret_cast<BfmeThingE63 *>(this)->isValid()) return;
 bool busy;
 {
 int out=0;
 busy=!flag35 && obj->rva0028C264(&out,4);
 }
 Object *builder=TheGameLogic->findObjectByID(obj->builderID);
 bool special=builder && (builder->tmplate->kindFlags&0x10);
 if (gettingBuiltBehaviorTickData->builder.isEmpty() && (!builder || builder==obj || special)) {
   if (!busy && !iface.active()) {
     if (gettingBuiltBehaviorTickData->countdown) { if(timer>0.0f)timer-=1.0f;if(timer>0.0f)return; }
     else if (timer<0.0f)return;
     iface.start(true);
   }
 } else {
   if (builder && !(builder->privateStatus&1)) return;
   if (timer>0.0f && !busy)timer-=1.0f;
   if (timer<=0.0f)iface.start(true);
 }

 if (0) throw 1;
}
