// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?rva003C9E4E@ScriptActions@@IAEXABVAsciiString@@0@Z, retail 0x003C9E4E
// (253B; ret 8). Target identity: an unnamed ScriptActions member aligned
// with WorldBuilder's 0x01018750 (same callees: getTeamNamed 0x003584E9 twice,
// iterate_TeamMemberList 0x00263864, advance 0x00263526 and
// AICommandInterface 0x0036F19B). Target body: among the second team's
// members of kind 7 (template +0x108 bitset) find the one whose body module
// (Object +0x254, slot 5) reports the lowest value below 1.0, then send every
// kind-14 member of the first team that has an AI (+0x258) at it, from
// script. As in WorldBuilder the guard tests the first team twice and never
// the second.
// Shape (from the WorldBuilder body): both loops re-test the current member
// for null; without those tests cl keeps 0 in ESI and pushes it where retail
// pushes immediates. DLINK_ITERATOR::advance and Team::iterate_TeamMemberList
// are defined inline over the virtual-inheritance Object layout of
// TeamIterateTeamMemberList.cpp (neither is inlined) so the member loads
// straight into EDI.
#include "ascii_string.h"

class Object;

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

class AICommandInterface
{
public:
	void rva0036F19B(Object *obj, CommandSourceType source);	// 0x0036F19B
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;	// +0x20
};

class BodyModuleInterface
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual float getHealthRatio() const = 0;	// slot 5 (+0x14)
};

struct ThingTemplate
{
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }
	char m_pad000[0x108];
	unsigned char m_kindOf[28];	// +0x108
};

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x68 - 8];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	__forceinline bool isKindOf(int bit) const { return m_template->isKindOf(bit); }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
private:
	unsigned char m_pad070[0x254 - 0x70];
	BodyModuleInterface *m_body;	// +0x254
	AIUpdateInterface *m_ai;	// +0x258
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = ((*m_cur).*(m_getNextFunc))(); }
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const { return DLINK_ITERATOR<Object>(m_head, &Object::dlink_next_TeamMemberList); }
private:
	unsigned char m_pad00[0x38];
	Object *m_head;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);	// 0x003584E9
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void rva003C9E4E(const AsciiString &teamName, const AsciiString &targetTeamName);
};

void ScriptActions::rva003C9E4E(const AsciiString &teamName, const AsciiString &targetTeamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	Team *targetTeam = TheScriptEngine->getTeamNamed(targetTeamName, false);
	if (theTeam && theTeam) {
		Object *weakest = 0;
		float lowest = 1.0f;
		for (DLINK_ITERATOR<Object> iter = targetTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *obj = iter.cur();
			if (obj && obj->isKindOf(7)) {
				BodyModuleInterface *body = obj->getBodyModule();
				if (body && body->getHealthRatio() < lowest) {
					weakest = obj;
					lowest = body->getHealthRatio();
				}
			}
		}
		if (weakest) {
			for (DLINK_ITERATOR<Object> iter2 = theTeam->iterate_TeamMemberList(); !iter2.done(); iter2.advance()) {
				Object *obj = iter2.cur();
				if (obj && obj->isKindOf(14)) {
					AIUpdateInterface *ai = obj->getAIUpdateInterface();
					if (ai)
						ai->m_commands.rva0036F19B(weakest, CMD_FROM_SCRIPT);
				}
			}
		}
	}
}
