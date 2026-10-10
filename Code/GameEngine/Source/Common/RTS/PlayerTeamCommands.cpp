// stlport
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/open-bfme-1/inputs/reference/shims/objectdlink
// ZH Player.cpp ungarrisonAllUnits semantics. Native [2AF037,2AF0C5)
// fixes Player prototype-list32C, prototype Team head334, Object AI258,
// ThingTemplate structure bit108:80, and AI commands base20.
// Team member-pointer dispatch has a function and zero this-adjustment;
// the neutral empty bases express that observed eight-byte ABI only.
// Object iterator ABI is inherited from the verified263864/263526 providers.
// Donor revision 575ba2b04; target direct calls independently verify semantics.
#include <list>
#include <cstring>
#include "ObjectDlinkPmf.h"
enum CommandSourceType {CMD_FROM_PLAYER,CMD_FROM_SCRIPT,CMD_FROM_AI};
template<int N>class BitFlags {public:unsigned bits[7];BitFlags(){std::memset(bits,0,sizeof(bits));}};
class Thing {public:bool isAnyKindOf(const BitFlags<69>&) const;};
class AICommandInterface {public:void aiHunt(CommandSourceType);void aiIdle(CommandSourceType);void aiEvacuate(bool,CommandSourceType);};
struct Rva2AE9B8AI {char pad[32];AICommandInterface commands;};
struct Rva2AE9B8Template {char pad[0x108];unsigned kinds;};
struct Rva2AE9B8Object {void*vt;Rva2AE9B8Template*type;char pad[0x258-8];Rva2AE9B8AI*ai;};
template<class T>class DLINK_ITERATOR {public:typedef T*(T::*GetNextFunc)()const;DLINK_ITERATOR(T*cur,GetNextFunc next):m_cur(cur),m_getNext(next){};T*cur()const{return m_cur;}bool done()const{return m_cur==0;}void advance();private:T*m_cur;GetNextFunc m_getNext;};
class Rva2AE9B8TeamBase1 {}; class Rva2AE9B8TeamBase2 {};
class Team : public Rva2AE9B8TeamBase1,public Rva2AE9B8TeamBase2 {public:Team*dlink_next_TeamInstanceList()const;DLINK_ITERATOR<Object> iterate_TeamMemberList()const;};
template<>__forceinline void DLINK_ITERATOR<Team>::advance(){if(m_cur)m_cur=(m_cur->*m_getNext)();}
struct Rva2AE9B8Prototype {char pad[0x334];Team*head;};
class Player {public:void ungarrisonAllUnits(CommandSourceType);private:char pad[0x32c];_STL::list<Rva2AE9B8Prototype*>prototypes;char gap[0x33d-0x330];bool hunt;};
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
