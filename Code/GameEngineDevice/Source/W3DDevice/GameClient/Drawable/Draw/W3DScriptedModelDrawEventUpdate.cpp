// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
// Native BD6C2..BDA40, 894B. W3DScriptedModelDraw particle/event update.
// WB945CC0 supplies the debug control-flow twin, not the original method name.
// ZH W3DModelDraw::handleWeaponFireFX guides the FX emission relationship;
// BF1 cee35b7d8 scripted model source has no recovered counterpart.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport, and <stddef.h> with it so
// their _errno declarations agree. /EHs lets free throw, preserving
// retail's unwind states.
#define _CRTIMP
#include <stddef.h>
#include <stdlib.h>
#undef _CRTIMP

#include "ascii_string.h"
#include "Coord3D.h"
#include <new>
class FXList;
class ParticleSystem;
struct AnimationClock {
 void *clip;float current,previous;int unused;int mode,direction;
};
// The parser and updater share the native 20-byte event base and 24-byte records.
class Rva000B6A67 {public:
 Rva000B6A67();
 int period,start,end;unsigned char loop;char pad[3];AsciiString bone;
};
class Rva000BB491:public Rva000B6A67 {
public:
 Rva000BB491(){}
 Rva000BB491(const Rva000BB491 &);
 const FXList *fx;
};
struct Rva00B9AC2:public Rva000B6A67 {
 Rva00B9AC2():events(0){}
 ~Rva00B9AC2();
 void *events;
};
class Rva000BB4AC : public Rva00B9AC2 {
public:
 Rva000BB4AC(const Rva000BB4AC &);
 // Declared, not generated: the implicit destructor this view would emit is an
 // empty COMDAT that differs from retail's out-of-line teardown row at
 // 0x000B9AC2 (Rva000B9AC2Dtor.cpp), which the census then holds against both
 // units. Binding to the rowed definition keeps this unit's link clean.
 ~Rva000BB4AC();
};
struct BfmePod32 {
 AsciiString bone;int a,b,c;void *object;int id;void *particleTemplate;char flag;char pad[3];
};
class Rva00704980 {public:
 __declspec(noinline) Rva00704980();
 int m_00,m_04,m_08,m_0C,m_10,m_14,m_18;char m_1C,m_1D,m_1E,m_1F;
};
// Strong shared constructor: both native callers retain their nugget in EDX.
Rva00704980::Rva00704980(){m_00=0;m_04=0;m_08=0;m_0C=0;m_10=0;m_14=0;m_18=0;m_1C=0;m_1D=0;m_1E=0;m_1F=0;}
struct ParticleEvent32:public Rva00704980 {
 ~ParticleEvent32(){reinterpret_cast<StringBase<char>*>(this)->clear();}
};
void Rva000B9887Init(void*,BfmePod32*);
struct ListNode {ListNode*next,*prev;void *value;};
struct Rva000BC0DBElement {double word;};
struct BfmeStringRecord000B757D {~BfmeStringRecord000B757D();};
namespace _STL {
 template<class T>class allocator;
 template<class T,class A=allocator<T> >class _List_base {public:ListNode*node;~_List_base();};
 template<class T>struct _Nonconst_traits;
 template<class T,class Traits>struct _List_iterator {
  _List_iterator(ListNode*listNode):_M_node(listNode){}
  _List_iterator(const _List_iterator&other):_M_node(other._M_node){}
  ListNode *_M_node;
 };
 template<class T,class A=allocator<T> >class list {
 public:
  list(const list&);
  __forceinline ~list(){reinterpret_cast<_List_base<int>*>(this)->~_List_base();}
  void push_back(const T&);
  _List_iterator<T,_Nonconst_traits<T> > erase(_List_iterator<T,_Nonconst_traits<T> >);
  ListNode *node;
 };
}
// STLport list::erase (0x000BC133), select-any like the template instantiation retail's unit saw.
template<class T,class A>__declspec(noinline) inline _STL::_List_iterator<T,_STL::_Nonconst_traits<T> > _STL::list<T,A>::erase(_STL::_List_iterator<T,_STL::_Nonconst_traits<T> > pos)
{
 ListNode *next=pos._M_node->next,*prev=pos._M_node->prev;
 prev->next=next;next->prev=prev;
 reinterpret_cast<T*>(&pos._M_node->value)->~T();
 free(pos._M_node);
 return _STL::_List_iterator<T,_STL::_Nonconst_traits<T> >(next);
}
namespace _STL {
 template<class T,class A=allocator<T> >class vector {public:void push_back(const T&);};
}
class Rva000B9A0E {public:void rva000B9A0E(void*,int,int);};
class RvaSmartPtr12 {public:void rva0004CBC0();};
class BfmeParticleSystemHandle {
public:
 __forceinline ~BfmeParticleSystemHandle(){if(system)reinterpret_cast<RvaSmartPtr12*>(this)->rva0004CBC0();}
 ParticleSystem *system;void *prev,*next;
 operator bool()const{return system!=0;}
 ParticleSystem *operator->()const;
};
class Rva001F3852ByteOneSetter {public:void enable();};
class ParticleSystem {public:void destroy();};
ParticleSystem *Make001FCBD7();
// ?BfmeParticleSystemHandle::operator-> present-unmatched
inline ParticleSystem*BfmeParticleSystemHandle::operator->()const {return system?system:Make001FCBD7();}
enum ParticleSystemID {INVALID_PARTICLE_SYSTEM_ID=0};
class ParticleSystemManager {private:BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);friend class W3DScriptedModelDraw;};
extern ParticleSystemManager *TheParticleSystemManager;
struct EventNugget {void *vt;int type;char pad[0x15c-8];unsigned particle;};
struct EventCollection {char pad[4];_STL::list<Rva000BC0DBElement> list;};
template<class T>struct AnimationSpan {T*first,*last,*capacity;bool empty()const{return first==last;}T*begin()const{return first;}T*end()const{return last;}};
struct AnimationState {
 char pad[0x74];_STL::list<BfmePod32> particles;
 AnimationSpan<Rva000BB491> fx;
 AnimationSpan<Rva000BB4AC> events;
};
struct AnimationDefaults {char pad[0xb8];AnimationSpan<Rva000BB491> fx;};
struct DrawableEventView {char pad[0xfc];void *object;char pad100[0x114-0x100];unsigned char status;};
struct BoneMatrix12 {float m[12];};
class BoneDraw {public:
virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual void v16();virtual void v17();virtual void v18();virtual void v19();virtual void v20();virtual void v21();virtual void v22();virtual void v23();virtual void v24();virtual void v25();virtual void v26();virtual void v27();virtual void v28();virtual void v29();virtual void v30();virtual void v31();virtual void v32();virtual void v33();virtual void v34();virtual void v35();virtual void v36();virtual void v37();virtual void v38();virtual void v39();virtual void v40();virtual void v41();virtual void v42();virtual void v43();virtual void v44();virtual void v45();virtual void v46();virtual void v47();virtual void v48();virtual void v49();virtual void v50();virtual void v51();
virtual void getBoneMatrix(BoneMatrix12*,const char*);};
class Matrix3D;
class FXList {public:static void doFXPos(const FXList*,const Coord3D*,const Matrix3D*,float,const Coord3D*);static void doFXObj(const FXList*,const class Object*,const class Object*);};
class W3DScriptedModelDraw {
public:
 void rva000BD6C2();
 void rva000BB3E6(Rva000BB491);
 char pad0[8];DrawableEventView *drawable;char padC[8];
 AnimationDefaults *defaults;AnimationState *state;
 char pad1c[0x48-0x1c];bool particlesDirty;
 char pad49[0x50-0x49];BoneDraw*drawer;char pad54[0x64-0x54];_STL::list<BfmeStringRecord000B757D> particleIDs;
 char pad68[0x110-0x68];AnimationClock clock;
};
static __declspec(noinline) bool Rva000B3AAB(const AnimationClock *clock,int frame)
{
 int current=(int)clock->current,previous=(int)clock->previous;
 if(previous==current)return false;
 if(current==frame)return true;
 switch(clock->mode){
 case 1:
  if(previous<current){if(frame>previous&&frame<current)return true;}
  else if(previous>current){if(frame>previous||frame<current)return true;}
  break;
 case 2:case 4:case 6:
  if(clock->direction==1){if(frame>previous&&frame<current)return true;}
  else{if(frame<previous&&frame>current)return true;}
  break;
 case 3:
  if(clock->direction==1){
   if(previous<current){if(frame>previous&&frame<current)return true;}
   else if(previous>current){if(frame<previous)return true;}
  }else{
   if(current<previous){if(frame<previous&&frame>current)return true;}
   else if(current>previous){if(frame>previous)return true;}
  }
  break;
 case 5:
  if(current<previous){if(frame<previous&&frame>current)return true;}
  else if(current>previous){if(frame<previous||frame>current)return true;}
  break;
 }
 return false;
}
void W3DScriptedModelDraw::rva000BD6C2()
{
 if(state){
  void*object=drawable->object;
  AnimationClock *animation=&clock;
  int frame=(int)animation->current;
  reinterpret_cast<Rva000B9A0E*>(state)->rva000B9A0E(object,0,frame);
  if(!state->fx.empty()){
   for(Rva000BB491 *it=state->fx.begin();it!=state->fx.end();++it){
    Rva000BB491 event(*it);
    bool fire=false;
    if(!event.loop){
     if((frame>=event.start&&frame<=event.end)||frame==event.start||
        (event.start<0&&(event.period==0||frame%event.period==0)))fire=true;
    }else{
     int previous=(int)animation->previous;
     if(event.end>0){
     if((frame>=event.start&&frame<=event.end)||(previous<event.start&&frame>event.end))fire=true;
    }else if(event.start>=0){
     if(Rva000B3AAB(animation,event.start))fire=true;
    }else if(event.period==0||event.period==1)fire=true;
    else if(animation->direction==1){
     for(int i=previous+1;i<=frame;++i)if(i%event.period==0)rva000BB3E6(event);
    }else{
     for(int i=previous-1;i>=frame;--i)if(i%event.period==0)rva000BB3E6(event);
     }
    }
    if(fire)rva000BB3E6(event);
   }
  }
  if(!state->events.empty()){
   for(Rva000BB4AC *it=state->events.begin();it!=state->events.end();++it){
    Rva000BB4AC copied(*it);
    Rva00B9AC2 &event=*reinterpret_cast<Rva00B9AC2*>(&copied);
    if(frame==event.start||(event.start<0&&(event.period==0||frame%event.period==0))){
     _STL::list<Rva000BC0DBElement> events(reinterpret_cast<EventCollection*>(event.events)->list);
     for(ListNode*n=events.node->next;n!=events.node;n=n->next){
      if(reinterpret_cast<EventNugget*>(n->value)->type==9){
       ParticleEvent32 particle;
       Rva000B9887Init(n->value,reinterpret_cast<BfmePod32*>(&particle));
       state->particles.push_back(*reinterpret_cast<BfmePod32*>(&particle));
       if(!(drawable->status&8))particlesDirty=true;
      }
     }
    }else if(frame>=event.end){
     _STL::list<Rva000BC0DBElement> events(reinterpret_cast<EventCollection*>(event.events)->list);
     for(ListNode*n=events.node->next;n!=events.node;n=n->next){
      if(reinterpret_cast<EventNugget*>(n->value)->type==9){
       EventNugget*nugget=reinterpret_cast<EventNugget*>(n->value);
       BfmeParticleSystemHandle system=TheParticleSystemManager->findParticleSystemByID((ParticleSystemID)nugget->particle);
       if(system){reinterpret_cast<Rva001F3852ByteOneSetter*>(system.operator->())->enable();// Equivalent paths merge after allocation, retaining the native node/nugget roles.
        if(n==n->next){system->destroy();}else{system->destroy();}}
       ListNode *id=particleIDs.node->next;
       for(;id!=particleIDs.node;id=id->next){if((unsigned)id->value==nugget->particle){particleIDs.erase(_STL::_List_iterator<BfmeStringRecord000B757D,_STL::_Nonconst_traits<BfmeStringRecord000B757D> >(id));break;}}
      }
     }
    }
   }
  }
 }
 if(defaults&&!defaults->fx.empty())
  for(Rva000BB491*it=defaults->fx.begin();it!=defaults->fx.end();++it)rva000BB3E6(*it);
}

void W3DScriptedModelDraw::rva000BB3E6(Rva000BB491 event)
{
 if(!event.fx)return;
 if(!event.bone.isEmpty()){
  BoneMatrix12 matrix;drawer->getBoneMatrix(&matrix,event.bone.str());
  Coord3D position;position.x=matrix.m[3];position.y=matrix.m[7];position.z=matrix.m[11];
  FXList::doFXPos(event.fx,&position,reinterpret_cast<const Matrix3D*>(&matrix),0,0);
 }else{
  // Retail first tests the owner word in memory and then reloads it for the
  // FX call. Keep that first access observable while retaining the actual
  // by-value record, whose complete destructor is part of native's EH graph.
  volatile DrawableEventView *holder=drawable;
  if(holder->object)FXList::doFXObj(event.fx,drawable->object?reinterpret_cast<const Object*>(drawable->object):0,0);
 }
}

// BFME1 9cbfb551 parser lead; target C48DB..C4B61, 646 bytes. The native
// token separator is at +420, the name buffer is 64 bytes, and both callers
// require the common B6D26 constructor to remain a strong definition here.
#include <string.h>
class INI {public: const char*getNextTokenOrNull(const char*);int scanInt(const char*);};
class FXList;
class FXListStore {public:const FXList*findFXList(const char*)const;};extern FXListStore*TheFXListStore;
struct TargetRef00217D4C {virtual void*destroy(unsigned);int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Rva000B3F15Payload {char pad[0x28];TargetRef00217D4C ref;};
class Rva000B3F15 {public:
 Rva000B3F15():pointer(0){}
 ~Rva000B3F15(){if(pointer)ReleaseTreeHintRef00217D4C(&pointer->ref);}
 Rva000B3F15&operator=(const Rva000B3F15&);
 Rva000B3F15Payload*pointer;
};
class Rva001E2BB0 {public:Rva000B3F15 rva001E2BB0(const char*);};
static const char*nextToken(INI*ini){const char*seps=*(const char**)((char*)ini+0x420);return ini->getNextTokenOrNull(seps);}
void rva000C48DB(void*one,void*two,void*three,void*four){
 INI*ini=(INI*)one;
 Rva000BB491 event;char fxName[64];fxName[0]=0;
 const char*token=nextToken(ini);
 while(token){
  if(strcmp(token,"Frame")==0){token=nextToken(ini);if(token)event.start=ini->scanInt(token);}
  else if(strcmp(token,"FrameStep")==0){token=nextToken(ini);if(token)event.period=ini->scanInt(token);}
  else if(strcmp(token,"FrameStop")==0){token=nextToken(ini);if(token)event.end=ini->scanInt(token);}
  else if(strcmp(token,"FireWhenSkipped")==0){event.loop=true;}
  else if(strcmp(token,"Name")==0){token=nextToken(ini);strcpy(fxName,token);if(token)event.fx=TheFXListStore->findFXList(token);}
  else if(strcmp(token,"Bone")==0){token=nextToken(ini);((StringBase<char>&)event.bone).set(token);}
  token=nextToken(ini);
 }
 if(*((const char*)event.fx+8)){
  Rva00B9AC2 shared;
  shared.start=event.start;shared.bone=event.bone;shared.period=event.period;shared.end=event.end;shared.loop=event.loop;
  *((Rva000B3F15*)&shared.events)=((Rva001E2BB0*)TheFXListStore)->rva001E2BB0(fxName);
  _STL::list<Rva000BC0DBElement> list(*(const _STL::list<Rva000BC0DBElement>*)((char*)shared.events+4));
  for(ListNode*it=(*(ListNode**)&list)->next;it!=(*(ListNode**)&list);it=it->next){
   EventNugget*nugget=(EventNugget*)it->value;
   if(nugget->type==9){ParticleEvent32 record;Rva000B9887Init(nugget,(BfmePod32*)&record);((_STL::list<BfmePod32>*)four)->push_back(*(const BfmePod32*)&record);}
  }
  ((_STL::vector<Rva000BB4AC>*)three)->push_back((const Rva000BB4AC&)shared);
 }else{((_STL::vector<Rva000BB491>*)two)->push_back(event);}
}
