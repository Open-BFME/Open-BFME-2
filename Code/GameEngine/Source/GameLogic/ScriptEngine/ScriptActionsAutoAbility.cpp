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
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../Include/Common/ThingTemplate.h"
class Thing { public: virtual ~Thing(); };
#include "../../../Include/Common/BfmeObjectVirtualTail.h"
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail { public: unsigned char m_carrier[4]; };
class BfmeObjectDlinkBase {
public: Object *dlink_next_TeamMemberList() const; const ThingTemplate *m_template; unsigned char m_pad[0x60];
};
class Object : public Thing, public BfmeObjectDlinkBase, public BfmeObjectVbptrCarrier {
public:
 __forceinline bool isKindOf(int t) const { return ((m_template->m_kindof[t >> 5] & (1U << (t & 31)))!=0); }
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
#include "../../../Include/Common/TeamBFME2.h"
inline __declspec(noinline) DLINK_ITERATOR<Object> Team::iterate_TeamMemberList() const {
 return DLINK_ITERATOR<Object>(m_dlinkhead_TeamMemberList,&Object::dlink_next_TeamMemberList);
}
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;
#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../Include/GameClient/CommandButton.h"
class CommandSet { public: const CommandButton *getCommandButton(int) const; };
#include "../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;
#include "../../../Include/Common/Rva0031D5F8.h"
#include "../../../Include/GameLogic/Module/AutoAbilityBehavior.h"

void ScriptActions::rva003C32CC(const AsciiString &teamName, const AsciiString &buttonName, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	static NameKeyType key = TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
	const CommandButton *button = TheControlBar->findCommandButton(buttonName);
	if (!button || !button->m_autoAbility)
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
