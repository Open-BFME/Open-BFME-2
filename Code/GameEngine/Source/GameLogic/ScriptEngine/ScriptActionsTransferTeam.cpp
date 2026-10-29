// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /I.
// stlport
// ZH ScriptActions.cpp at BFME1 cee35b7d8 supplies transfer identity;
// unnamed WB10087D0 independently preserves the native branch structure.
// Native003C90DD..003C91D1: transfer ownership; refresh and idle both the
// member and its containing horde; notify the script engine afterwards.
// Object virtual-base/member-pointer layout follows verified Team iterator49
// and advance32. Both visible emitted helpers independently match retail.
// Callback3BA83F is the existing91-byte provider; its second argument is
// unused. The cast preserves the two native pointer-width cdecl arguments.
#include "ascii_string.h"
#include <vector>
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
class Object;
class Player;
enum CommandSourceType { CMD_FROM_AI=2 };
class AICommandInterface { public: void aiIdle(CommandSourceType); };
class AIUpdateInterface { public: unsigned char m_pad[0x20]; AICommandInterface m_command; };
class ThingTemplate {
public: __forceinline bool isKindOf(int t) const { return (m_kind[t>>3]&(1<<(t&7)))!=0; }
private: unsigned char m_pad[0x108]; unsigned char m_kind[0x20];
};
class Thing { public: virtual ~Thing(); };
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail { public: unsigned char m_carrier[4]; };
class BfmeObjectDlinkBase {
public: Object *dlink_next_TeamMemberList() const; const ThingTemplate *m_template; unsigned char m_pad[0x60];
};
class Object : public Thing, public BfmeObjectDlinkBase, public BfmeObjectVbptrCarrier {
public:
 __forceinline bool isKindOf(int t) const { return m_template->isKindOf(t); }
 Object *getContainedBy() const { return m_containedBy; }
 AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
 void rva0028BAC0(); void rva0028DCC4();
private:
 unsigned char m_pad70[0x258-0x70]; AIUpdateInterface *m_ai;
 unsigned char m_pad25C[0x274-0x25C]; Object *m_containedBy;
};
template<class OBJCLASS> class DLINK_ITERATOR {
public:
 typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
 DLINK_ITERATOR(OBJCLASS *cur,GetNextFunc next):m_cur(cur),m_next(next) {}
 __declspec(noinline) void advance() { if(m_cur) m_cur=(m_cur->*m_next)(); }
 bool done() const { return m_cur==0; }
 OBJCLASS *cur() const { return m_cur; }
private: OBJCLASS *m_cur; GetNextFunc m_next;
};
class Team {
public:
 DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
 void setControllingPlayer(Player *);
 int rva0039DD12(int (*func)(Object *,void *),void *) const;
private: unsigned char m_pad[0x38]; Object *m_head;
};
inline __declspec(noinline) DLINK_ITERATOR<Object> Team::iterate_TeamMemberList() const {
 return DLINK_ITERATOR<Object>(m_head,&Object::dlink_next_TeamMemberList);
}
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;
class PlayerList { public: Player *getEachPlayerFromMask(int &); };
extern PlayerList *ThePlayerList;
class Rva002039B6Host { public: void rva002039B6(); };
int __cdecl rva003BA83F(void *,int);
void ScriptActions::doTransferTeamToPlayer(const AsciiString &teamName,const AsciiString &playerName) {
 Team *theTeam=TheScriptEngine->getTeamNamed(teamName,false);
 int mask=TheScriptEngine->rva00357475(playerName,0);
 Player *playerDest=ThePlayerList->getEachPlayerFromMask(mask);
 if (!(theTeam && playerDest)) return;
 theTeam->setControllingPlayer(playerDest);
 theTeam->rva0039DD12(reinterpret_cast<int (*)(Object *,void *)>(rva003BA83F),0);
 for(DLINK_ITERATOR<Object> iter=theTeam->iterate_TeamMemberList();!iter.done();iter.advance()) {
  Object *obj=iter.cur();
  AIUpdateInterface *ai;
  Object *horde=obj->getContainedBy();
  if(horde && horde->isKindOf(0x6D)) {
   horde->rva0028BAC0(); horde->rva0028DCC4(); ai=horde->getAIUpdateInterface();
   if(ai) ai->m_command.aiIdle(CMD_FROM_AI);
  }
  obj->rva0028BAC0(); obj->rva0028DCC4(); ai=obj->getAIUpdateInterface();
  if(ai) ai->m_command.aiIdle(CMD_FROM_AI);
 }
 ((Rva002039B6Host *)TheScriptEngine)->rva002039B6();
}
