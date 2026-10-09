// ?setObjectsEnabled@Player@@QAEXABVAsciiString@@_N@Z
// partial score=0.74989 date=2026-10-09
// stlport
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Reference ZH Player.cpp::setObjectsEnabled at2116, BF1 9cbfb551fe20.
// WB C18F30 and native2ABD93..2ABE24 prove Player list32C / prototype
// teamhead334 / template4+name64 / script status flag1 and inverse enable.
// DLINK_ITERATOR<Object> return view is24 bytes (existing49B Team provider);
// its traversal state is opaque here and advanced by the existing32B helper.
#include "ascii_string.h"
#include <list>
class ThingTemplate{public:char prefix[0x64];AsciiString name;};
enum ObjectScriptStatusBit{OBJECT_STATUS_SCRIPT_DISABLED=1};
class Object;

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
	unsigned char m_tail[0x40];void setScriptStatus(ObjectScriptStatusBit,bool);
};

template<class T>class DLINK_ITERATOR{public:typedef T*(T::*Next)()const;T*current;Next next;DLINK_ITERATOR(T*obj,Next f):current(obj),next(f){} void advance(){current=(current->*next)();}};
struct ObjectTemplateView{char prefix[4];const ThingTemplate*tmplate;};
class MemoryPoolObject{public:virtual ~MemoryPoolObject();};class Snapshot{public:virtual ~Snapshot();};
class Team:public MemoryPoolObject,public Snapshot{public:Team*dlink_next_TeamInstanceList()const;DLINK_ITERATOR<Object>iterate_TeamMemberList()const;};
template<>void DLINK_ITERATOR<Object>::advance();
class TeamPrototype{public:char prefix[0x334];Team*head;};
struct PlayerTeamNode{PlayerTeamNode*next,*previous;TeamPrototype*value;};
class Player{public:void setObjectsEnabled(const AsciiString&,bool);private:char prefix[0x32C];PlayerTeamNode*teams;};
void Player::setObjectsEnabled(const AsciiString&name,bool enable){
 for(PlayerTeamNode*i=teams->next;i!=teams;i=i->next){
  for(DLINK_ITERATOR<Team>teamList(i->value->head,&Team::dlink_next_TeamInstanceList);teamList.current;teamList.advance()){
 Team*team=teamList.current;
   DLINK_ITERATOR<Object>objects=team->iterate_TeamMemberList();
   Object*obj;while((obj=objects.current)!=0){if(((ObjectTemplateView*)obj)->tmplate->name.compare(name)==0)obj->setScriptStatus(OBJECT_STATUS_SCRIPT_DISABLED,!enable);objects.advance();}
  }
 }
}
