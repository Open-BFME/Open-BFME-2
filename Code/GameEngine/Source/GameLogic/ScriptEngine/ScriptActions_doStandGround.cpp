// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
//
// ScriptActions::doTeamStandGround, retail 0x003C6191 (232B; ret 8)
// Target identity: executeAction case 501 (TEAM_STAND_GROUND) calls it on
// the ScriptActions instance (ecx = edi) with parameters 0 and 1 themselves,
// beside case 500 (UNIT_STAND_GROUND, 0x003C60E8); BFME 1's
// ScriptActions_doTeamStandGround.cpp is the donor for the name and flow.
// Target body: each member of the team named by parameter 0's string
// (getTeamNamed 0x003584E9, iterate_TeamMemberList 0x00263864, advance
// 0x00263526) gets status 0x44 set from parameter 1's int (setStatus
// 0x0023DB0E) and, for a template with KindOf bit 0x6D (byte +0x115, bit 5),
// the same status goes to every object the 0x0028C197 interface lists through
// its slot 67 (+0x10C) into a stack list (rowed _List_base<int> ctor
// 0x004EC36C, dtor 0x004EC395; the element type is int in the ledger and used
// as Object* here).
// Target differences from the donor: setStatus takes the status index, the
// horde test is the template's KindOf byte with no override lookup, and the
// member interface comes from 0x0028C197. Donor-carried: the stand-ground
// meaning of status 0x44 and the horde meaning of KindOf 0x6D and of the
// listed objects; the target establishes neither.
#include <list>
#include "ascii_string.h"

typedef int Int;

enum ObjectStatusTypes
{
	OBJECT_STATUS_STAND_GROUND = 0x44
};

class Parameter
{
public:
	Int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }
private:
	unsigned char m_pad00[8];
	Int m_int;		// +0x08
	unsigned char m_pad0C[4];
	AsciiString m_string;	// +0x10
};

class ThingTemplate
{
public:
	// KindOf bit 0x6D (byte +0x115, bit 5); BFME 1 tests KINDOF_HORDE here.
	bool isHorde() const { return (m_kindOf115 & 0x20) != 0; }
private:
	unsigned char m_pad000[0x115];
	unsigned char m_kindOf115;	// +0x115
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	void setStatus(ObjectStatusTypes st, bool set);	// 0x0023DB0E
	void *rva0028C197() const;
private:
	void *m_vtbl;
	const ThingTemplate *m_template;	// +0x04
};

// The 0x0028C197 interface: slot 67 (+0x10C) lists its objects.
class Rva0028C197Members
{
public:
#define MEMBERS_SLOT(n) virtual void slot##n();
	MEMBERS_SLOT(0) MEMBERS_SLOT(1) MEMBERS_SLOT(2) MEMBERS_SLOT(3) MEMBERS_SLOT(4)
	MEMBERS_SLOT(5) MEMBERS_SLOT(6) MEMBERS_SLOT(7) MEMBERS_SLOT(8) MEMBERS_SLOT(9)
	MEMBERS_SLOT(10) MEMBERS_SLOT(11) MEMBERS_SLOT(12) MEMBERS_SLOT(13) MEMBERS_SLOT(14)
	MEMBERS_SLOT(15) MEMBERS_SLOT(16) MEMBERS_SLOT(17) MEMBERS_SLOT(18) MEMBERS_SLOT(19)
	MEMBERS_SLOT(20) MEMBERS_SLOT(21) MEMBERS_SLOT(22) MEMBERS_SLOT(23) MEMBERS_SLOT(24)
	MEMBERS_SLOT(25) MEMBERS_SLOT(26) MEMBERS_SLOT(27) MEMBERS_SLOT(28) MEMBERS_SLOT(29)
	MEMBERS_SLOT(30) MEMBERS_SLOT(31) MEMBERS_SLOT(32) MEMBERS_SLOT(33) MEMBERS_SLOT(34)
	MEMBERS_SLOT(35) MEMBERS_SLOT(36) MEMBERS_SLOT(37) MEMBERS_SLOT(38) MEMBERS_SLOT(39)
	MEMBERS_SLOT(40) MEMBERS_SLOT(41) MEMBERS_SLOT(42) MEMBERS_SLOT(43) MEMBERS_SLOT(44)
	MEMBERS_SLOT(45) MEMBERS_SLOT(46) MEMBERS_SLOT(47) MEMBERS_SLOT(48) MEMBERS_SLOT(49)
	MEMBERS_SLOT(50) MEMBERS_SLOT(51) MEMBERS_SLOT(52) MEMBERS_SLOT(53) MEMBERS_SLOT(54)
	MEMBERS_SLOT(55) MEMBERS_SLOT(56) MEMBERS_SLOT(57) MEMBERS_SLOT(58) MEMBERS_SLOT(59)
	MEMBERS_SLOT(60) MEMBERS_SLOT(61) MEMBERS_SLOT(62) MEMBERS_SLOT(63) MEMBERS_SLOT(64)
	MEMBERS_SLOT(65) MEMBERS_SLOT(66)
#undef MEMBERS_SLOT
	virtual void getMembers(_STL::list<int> *members);	// slot 67 (+0x10C)
};

template<class OBJ> class DLINK_ITERATOR
{
public:
	void advance();		// 0x00263526
	bool done() const { return m_cur == 0; }
	OBJ *cur() const { return m_cur; }
private:
	OBJ *m_cur;
	unsigned char m_rest[20];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
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
	void doTeamStandGround(Parameter *teamParameter, Parameter *standGroundParameter);
};

void ScriptActions::doTeamStandGround(Parameter *teamParameter, Parameter *standGroundParameter)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParameter->getString(), false);
	if (!team)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		obj->setStatus(OBJECT_STATUS_STAND_GROUND, standGroundParameter->getInt() != 0);
		if (!obj->getTemplate()->isHorde())
			continue;
		Rva0028C197Members *horde = (Rva0028C197Members *)obj->rva0028C197();
		if (!horde)
			continue;
		_STL::list<int> members;
		horde->getMembers(&members);
		for (_STL::list<int>::iterator it = members.begin(); it._M_node != members.end()._M_node; ++it)
			((Object *)*it)->setStatus(OBJECT_STATUS_STAND_GROUND, standGroundParameter->getInt() != 0);
	}
}
