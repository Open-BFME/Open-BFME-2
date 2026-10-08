// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Landed from the banked attempt once Zero Hour's null-member skip
// (Object *obj = iter.cur(); if (!obj) continue;) was added to the member
// loop: it keeps the member in ecx from the loop test into the call, the
// mov-test wall the bank recorded.
// ?Rva003C36FEDo@@YGXPAVParameter@@_N@Z @0x003C36FE 92B
// Team-member drawable flag via getTeamNamed iterate Rva-advance getDrawable.
// Evidence: rowed getTeamNamed 0x003584E9 iterate 0x00263864 advance 0x00263526
// Thing::getDrawable 0x005508E2 Drawable::rva00270FAC 0x00270FAC extern
// g_Va009FE16C caller 0x003CE8E7 ret 8. Donor Rva003C0DE1Do loop shape.
#include "ascii_string.h"

class Object;
class Team;
class Drawable;
class ScriptEngine;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
};

class Drawable
{
public:
	void rva00270FAC(bool flag);
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern class ScriptEngine *TheScriptEngine;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

void __stdcall Rva003C36FEDo(Parameter *parm, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)parm->getString(), false);
	if (team == 0)
		return;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Object *obj = it.cur();
		if (!obj)
			continue;
		Drawable *drawable = obj->getDrawable();
		if (drawable != 0)
			drawable->rva00270FAC(flag);
	}
}
