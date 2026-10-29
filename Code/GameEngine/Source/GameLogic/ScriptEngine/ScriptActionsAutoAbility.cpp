// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /I.
// stlport
// Native 003C32CC..003C33C9; WB1018A80 supplies the nested null checks
// and per-slot candidate local. ZH supplies the AutoAbilityBehavior identity;
// target module key, 32 slots and command-button flag +10C are retail evidence.
// Team iterator constructor/advance use the verified native member-pointer ABI.
#include "ascii_string.h"
#include <vector>
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
class Object;
class Module;
enum NameKeyType { NAMEKEY_INVALID=0 };
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
 const AsciiString *rva00290E67() const;
protected: friend class ScriptActions;
 Module *findModule(NameKeyType) const;
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

class NameKeyGenerator { public: NameKeyType nameToKey(const char *); }; extern NameKeyGenerator *TheNameKeyGenerator;
class CommandButton { public: unsigned char m_pad[0x10C]; bool m_10C; };
class CommandSet { public: const CommandButton *getCommandButton(int) const; };
class ControlBar { public: const CommandButton *findCommandButton(const AsciiString &); }; extern ControlBar *TheControlBar;
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
class AutoAbilityBehavior { public: void rva0045A748(void *,bool); };

void ScriptActions::rva003C32CC(const AsciiString &teamName, const AsciiString &buttonName, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	static NameKeyType key = TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
	const CommandButton *button = TheControlBar->findCommandButton(buttonName);
	if (!button || !button->m_10C)
		return;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done();
		((DLINK_ITERATOR<Object> *)&iter)->advance()) {
		Object *obj=iter.cur();
		if (obj) {
		AutoAbilityBehavior *ability = (AutoAbilityBehavior *)obj->findModule(key);
		if (!ability) continue;
		{
			const CommandSet *set = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(obj->rva00290E67());
			if (set) {
				for (int i = 0; i < 32; ++i) {
					const CommandButton *candidate=set->getCommandButton(i);
					if (button == candidate)
						ability->rva0045A748((void *)button, flag);
				}
			}
		}
	}
}
}
