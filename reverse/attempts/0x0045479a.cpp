// ?rva0045479A@GettingBuiltBehavior@@QAEXXZ
// partial score=0.91 date=2026-10-09
// cl: /O1 /Ob2 /arch:SSE /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
// Native45479A..45499B complete EH body, WB116FCD0 same call graph.
// The primary GettingBuiltBehavior receiver and fields follow owned ctor
// and interface sibling units. Original method name unknown.
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
class Player;
class Rva000421C8 {
public:
 Rva000421C8():m_next(0){}
 virtual ~Rva000421C8(){}
 virtual bool allow(Object *)=0;
 virtual int getPlayerMask();
 Rva000421C8 *m_next;
};
class Rva002614ECFilter : public Rva000421C8 {
public:
 Rva002614ECFilter(const void *f,Player *p,bool m):m_what(f),m_player(p),m_match(m){}
 virtual bool allow(Object *);
 const void *m_what;Player *m_player;bool m_match;
};
class Rva0045342FBody {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual float health();virtual void slot5();virtual float maxHealth();
};
struct GettingBuiltTemplateView { unsigned char pad[0x11b]; unsigned char kindFlags; };
enum ObjectID { INVALID_ID = 0 };
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
class GameLogic { public:Object *findObjectByID(ObjectID); };
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
class GettingBuiltBehavior {
public:
 void rva00453D92();bool rva00453DCF();void rva0045479A();
private:
 bool rva00453124();
public:
 void *vptr;const GettingBuiltBehaviorTickData *data;Object *object;
 unsigned char padC[0x20-0xc];GettingBuiltTickInterface iface;
 int state;float timer;unsigned char pad2c[0x35-0x2c];bool flag35;
 unsigned char pad36[0x3e-0x36];bool flag3e;
};
void GettingBuiltBehavior::rva0045479A()
{
 rva00453D92();flag3e=rva00453DCF();
 const GettingBuiltBehaviorTickData *d=data;
 Object *obj=object;
 {
 Rva0045342FBody *body=obj->body;
 if (!body) return;
 if (obj->privateStatus&1) {
   if (!d->nearby) return;
   Rva002614ECFilter filter(&d->filter,obj->getControllingPlayer(),true);
   BfmeWideResult result=ThePartitionManager->iterateObjectsInRange(&obj->position,d->radius,1,&filter,0);
   Object *found;
   while ((found=result.next())!=0) if (found!=obj && !(found->privateStatus&1)) return;
 }
 if (!(body->health()<body->maxHealth())) return;
 }
 if (rva00453124()) return;
 int out=0;
 bool busy=!flag35 && obj->rva0028C264(&out,4);
 Object *builder=TheGameLogic->findObjectByID(obj->builderID);
 bool special=builder && (builder->tmplate->kindFlags&0x10);
 if (d->builder.isEmpty() && (!builder || builder==obj || special)) {
   if (!busy && !iface.active()) {
     if (d->countdown) { if(timer>0.0f)timer-=1.0f;if(timer>0.0f)return; }
     else if (timer<0.0f)return;
     iface.start(true);
   }
 } else {
   if (builder && !(builder->privateStatus&1)) return;
   if (timer>0.0f && !busy)timer-=1.0f;
   if (timer<=0.0f)iface.start(true);
 }
}
