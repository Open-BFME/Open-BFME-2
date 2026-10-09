// cl: /O1 /Ob2 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Reference semantic guide: BF1f989 GettingBuiltBehaviorCompletion.cpp,
// its owned555B primary completion helper. Target454B5C..454DF9 adds gated
// completion, worker-kind handling, voice event and ControlBar dirty notification.
// Layout, branch gates, widths and call arguments measured in native and WB116EAF0.
#include <list>
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Drawable;
class Thing { public:Drawable *getDrawable() const; };
enum ObjectStatusTypes { STATUS_NONE=0 };
enum CommandSourceType { SOURCE_NONE=0 };
class AICommandInterface { public:void aiIdle(CommandSourceType); };
class Rva001E702E { public:void rva001E702E(Thing *,int,int); };
template<int N> class CompletionAISlots:public CompletionAISlots<N-1>{public:virtual void gap(char (*)[N]);};
template<>class CompletionAISlots<1>{public:virtual void gap(char (*)[1]);};
class AIUpdateInterface:public CompletionAISlots<110>{
public:
 virtual bool completionMoveEnabled();
 void ignoreObstacle(const Object *);
 unsigned char pad4[0x1f0-4];Rva001E702E *locomotor;
};
class CompletionBodyView {
public:virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual float health();virtual void slot5();virtual float maxHealth();
};
struct CompletionTemplateView {unsigned char pad[0x108];unsigned int kind[7];};
struct CompletionModelFlags {
 unsigned int words[19];
 __forceinline unsigned test(int i)const{return words[i>>5]&(1u<<(i&31));}
 __forceinline void clear(int i){words[i>>5]&=~(1u<<(i&31));}
 __forceinline void set(int i){words[i>>5]|=1u<<(i&31);}
};
class Object:public Thing {
public:
 void rva0028AFE7(Object *);
 void rva0028AE6D();
 void setStatus(ObjectStatusTypes,bool);
 float rva00263763(const void *)const;
 __forceinline void clearCondition(int i){if(flags.test(i)){flags.clear(i);rva0028AE6D();}}
 __forceinline void setCondition(int i){if(!flags.test(i)){flags.set(i);rva0028AE6D();}}
 unsigned char pad0[4];CompletionTemplateView *tmplate;
 unsigned char pad8[0x38-8];Coord3D position;
 unsigned char pad44[0x7c-0x44];ObjectID builderID;
 unsigned char pad80[0xb8-0x80];float radius;
 unsigned char padBC[0x10c-0xbc];CompletionModelFlags flags;
 unsigned char pad158[0x254-0x158];CompletionBodyView *body;AIUpdateInterface *ai;
 unsigned char pad25c[0x280-0x25c];float construction;
};
class DrawableList:public _STL::list<Drawable *>{public:~DrawableList()throw();};
class GameMessage {public:enum Type{COMPLETED=0x7e2};};
class PickAndPlayInfo;
void pickAndPlayUnitVoiceResponse(const DrawableList *,GameMessage::Type,PickAndPlayInfo *);
class ControlBar;
extern ControlBar *TheControlBar;
extern GameLogic *TheGameLogic;
class CompletionInterface {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void complete(Object *);
 virtual void slot4();virtual void slot5();virtual bool active();virtual void slot7();
 virtual void slot8();virtual void slot9();virtual void slot10();virtual bool checkCompletion();
};
struct CompletionData {unsigned char pad[0x20];unsigned int timer;};
class GettingBuiltBehavior {
public:
 void rva00454B5C();
 void *vptr;const CompletionData *data;Object *object;
 unsigned char padC[0x20-0xc];CompletionInterface iface;
 int state;unsigned int timer;int value2c;
 bool flag30,flag31,flag32,flag33,flag34,flag35,flag36;
 unsigned char pad37[0x3c-0x37];bool flag3c,flag3d;
};
void GettingBuiltBehavior::rva00454B5C()
{
 Object *obj=object;
 CompletionBodyView *body=obj->body;
 if(!body)return;
 bool complete=iface.checkCompletion();
 Object *builder=TheGameLogic->findObjectByID(obj->builderID);
 if(flag3d && (complete || body->health()>=body->maxHealth()) &&
    (obj->construction>=100.0f || obj->construction==-1.0f)) {
   obj->rva0028AFE7(builder);
   if(builder && builder->ai && builder!=obj && (builder->tmplate->kind[0]&0x4000)) {
     if(flag3c){
       builder->ai->ignoreObstacle(obj);
       AIUpdateInterface *workerAI=builder->ai;
       ((AICommandInterface *)((char *)workerAI+0x20))->aiIdle((CommandSourceType)2);
       flag30=true;
     } else {obj->rva0028AFE7(0);flag3c=false;}
   } else if(!builder)flag3c=false;
   if(!complete || !(obj->tmplate->kind[0]&0x20000)) {obj->clearCondition(3);obj->clearCondition(4);}
   obj->clearCondition(67);obj->clearCondition(69);obj->clearCondition(68);
   obj->setStatus((ObjectStatusTypes)0x14,false);
   obj->setStatus((ObjectStatusTypes)2,false);
   if(iface.active())iface.complete(0);
   if(!flag33 && TheGameLogic->getFrame()>=5){
     DrawableList list;
     list.push_back(obj->getDrawable());
     pickAndPlayUnitVoiceResponse(&list,GameMessage::COMPLETED,0);
   }
   timer=data->timer;flag33=true;flag36=false;flag3d=false;
   *((bool *)((char *)TheControlBar+0x28))=true;
 } else {
 AIUpdateInterface *workerAI;
 if(!flag33 && !flag30 && builder && builder!=obj && (workerAI=builder->ai) && workerAI->completionMoveEnabled()) {
   const float &radius=builder->radius*1.5f;
   if(obj->rva00263763(builder)>radius*radius)builder->setCondition(100);
   builder->ai->locomotor->rva001E702E(builder,(int)&obj->position,0);
 }
 }
}
