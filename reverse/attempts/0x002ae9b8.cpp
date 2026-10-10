// ?setUnitsShouldHunt@Player@@QAEX_NW4CommandSourceType@@@Z
// partial score=0.94 date=2026-10-10
// stlport
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/open-bfme-1/inputs/reference/shims/objectdlink
// ZH Player.cpp setUnitsShouldHunt/ungarrisonAllUnits semantics, BFME2
// native2AE9B8/2AF037 data and direct callees determine target-specific offsets.
#include <list>
#include <cstring>
// BFME Object DLINK pointer-to-member layout — cracks the {pfn, -100, 0} wall.
//
// A dozen bodies in d_002f6330.asm (ScriptActions team walks) materialize the
// literal constants 0x00401140 / 0xFFFFFF9C (-100) / 0 and then run MSVC 7.1's
// generic virtual-inheritance PMF dispatch:
//
//     mov  eax, [obj+0x68]        ; Object's vbptr
//     mov  ecx, [eax+vbindex]     ; vbtable[0] == 0
//     add  ecx, delta             ; -100
//     lea  ecx, [ecx+obj+0x68]    ; this = obj + 0x68 + 0 - 100 = obj + 4
//     call pfn                    ; ILT 0x1140 -> 0x000C8980: mov eax,[ecx+0x260]; ret
//
// The encoding law, measured against MSVC 7.1 (build/_pmf_v6.cpp probe):
//   * delta -100 with vbindex 0 requires the vbptr to be INHERITED from a base
//     class placed at +0x68 whose own vbptr sits at its +0 (it introduces the
//     virtual base), making vbtable[0] == 0. MSVC then encodes the DLINK
//     member's delta as (member-class offset) - (vbptr offset) = 4 - 0x68.
//   * A most-derived-introduced vbptr instead gives vbtable[0] == -vbptr and
//     delta == member-class offset — the +4/vbindex-4 shapes that do NOT match.
//
// So BFME's Object is, structurally:
//     vptr @ +0, DLINK base @ +4 (link field read at [this+0x260] from there),
//     ... fields ..., vbptr-carrying base @ +0x68, virtual base beyond.
//
// Use exactly this skeleton; sizes of VB/Carrier tails are free, offsets are not.

class Object;
enum ObjectStatusTypes {RvaStatus38=38};

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

// Introduces the vbptr at its own +0; lands at +0x68 inside Object.
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0( void ); };

// Sits at +4; the retail pfn body is: mov eax,[this+0x260]; ret
class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList( void ) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	bool testStatus(ObjectStatusTypes)const;void leaveGroup();unsigned char m_tail[0x40];
};


enum CommandSourceType {CMD_FROM_PLAYER,CMD_FROM_SCRIPT,CMD_FROM_AI};
template<int N>class BitFlags {public:unsigned bits[7];BitFlags(){std::memset(bits,0,sizeof(bits));}};
class Thing {public:bool isAnyKindOf(const BitFlags<69>&) const;};
class AICommandInterface {public:void aiHunt(CommandSourceType);void aiIdle(CommandSourceType);void aiEvacuate(bool,CommandSourceType);};
struct Rva2AE9B8AI {char pad[32];AICommandInterface commands;};
struct Rva2AE9B8Template {char pad[0x108];unsigned kinds;};
struct Rva2AE9B8Object {void*vt;Rva2AE9B8Template*type;char pad[0x258-8];Rva2AE9B8AI*ai;};
class ObjectCalls {public:bool testStatus(ObjectStatusTypes) const;void leaveGroup();};
template<class T>class DLINK_ITERATOR {public:typedef T*(T::*GetNextFunc)()const;DLINK_ITERATOR(T*cur,GetNextFunc next):m_cur(cur),m_getNext(next){};T*cur()const{return m_cur;}bool done()const{return m_cur==0;}void advance();private:T*m_cur;GetNextFunc m_getNext;};
class Rva2AE9B8TeamBase1 {}; class Rva2AE9B8TeamBase2 {};
class Team : public Rva2AE9B8TeamBase1,public Rva2AE9B8TeamBase2 {public:Team*dlink_next_TeamInstanceList()const;DLINK_ITERATOR<Object> iterate_TeamMemberList()const;};
template<>inline void DLINK_ITERATOR<Team>::advance(){if(m_cur)m_cur=(m_cur->*m_getNext)();}
struct Rva2AE9B8Prototype {char pad[0x334];Team*head;};
class Player {public:void setUnitsShouldHunt(bool,CommandSourceType);void ungarrisonAllUnits(CommandSourceType);private:char pad[0x32c];_STL::list<Rva2AE9B8Prototype*>prototypes;char gap[0x33d-0x330];bool hunt;};
void Player::setUnitsShouldHunt(bool enabled,CommandSourceType source){
 hunt=enabled;
 for(_STL::list<Rva2AE9B8Prototype*>::iterator it=prototypes.begin();it!=prototypes.end();++it){
  for(DLINK_ITERATOR<Team> iter=DLINK_ITERATOR<Team>((*it)->head,&Team::dlink_next_TeamInstanceList);!iter.done();iter.advance()){
   Team*team=iter.cur();if(!team)continue;
   for(DLINK_ITERATOR<Object> objects=team->iterate_TeamMemberList();!objects.done();objects.advance()){
    Object*obj=objects.cur();if(!obj)continue;
    BitFlags<69> mask;mask.bits[0]|=0x14000;reinterpret_cast<unsigned char*>(mask.bits)[11]|=8;
    if(reinterpret_cast<Thing*>(obj)->isAnyKindOf(mask)||obj->testStatus(RvaStatus38))continue;
    obj->leaveGroup();
    Rva2AE9B8AI*ai=reinterpret_cast<Rva2AE9B8Object*>(obj)->ai;
    if(ai){if(enabled)ai->commands.aiHunt(source);else ai->commands.aiIdle(source);}
   }
  }
 }
}
void Player::ungarrisonAllUnits(CommandSourceType source){
 for(_STL::list<Rva2AE9B8Prototype*>::iterator it=prototypes.begin();it!=prototypes.end();++it){
  for(DLINK_ITERATOR<Team> iter=DLINK_ITERATOR<Team>((*it)->head,&Team::dlink_next_TeamInstanceList);!iter.done();iter.advance()){
   Team*team=iter.cur();if(!team)continue;
   for(DLINK_ITERATOR<Object> objects=team->iterate_TeamMemberList();!objects.done();objects.advance()){
    Object*obj=objects.cur();if(!obj)continue;
    Rva2AE9B8Object*view=reinterpret_cast<Rva2AE9B8Object*>(obj);Rva2AE9B8AI*ai=view->ai;
    if(!ai)continue;if(view->type->kinds&0x80)ai->commands.aiEvacuate(false,source);
   }
  }
 }
}
