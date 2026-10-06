// ?rva003C0CEE@@YAXPAVObject@@H_N@Z
// partial score=0.6 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Three unnamed WorldBuilder ScriptActions members (WB 0x0100CF00,
// 0x0100CEC0, 0x0100D340) that set or clear one of four adjacent bits
// (0xB8..0xBB) of the 591-bit flag set at Object +0x10C (WorldBuilder's debug
// Object: +0x114), notifying the object (0x0028AE6D) only when the bit
// changes:
//
//   0x003C0CEE (124B) the per-object worker; a TU-local static, so cl passes
//              the object in EDX and the selector in EAX
//   0x003C0D6A (38B)  for a named unit
//   0x003C0D90 (79B)  for every member of a named team
//
// The selector maps 1..4 to the four bits, anything else to the first, as
// WorldBuilder's switch does. The bits carry no established names.

#include "ascii_string.h"
#include <bitset>

class Object
{
public:
	void rva0028AE6D();

	unsigned char m_pad00[0x10C];
	_STL::bitset<591> m_flags;
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
};

template<class OBJCLASS>
class Rva001705A0DlinkIterator
{
public:
	void advance();

private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool);
	Object *getUnitNamed(const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void rva003C0D6A(const AsciiString &unitName, int which, bool on);
	void rva003C0D90(const AsciiString &teamName, int which, bool on);
};

static void rva003C0CEE(Object *obj, int which, bool on)
{
	unsigned int bit;
	switch (which) {
	case 1:
		bit = 0xB8;
		break;
	case 2:
		bit = 0xB9;
		break;
	case 3:
		bit = 0xBA;
		break;
	case 4:
		bit = 0xBB;
		break;
	default:
		bit = 0xB8;
		break;
	}
	if (on) {
		if (!obj->m_flags.test(bit)) {
			obj->m_flags.set(bit);
			obj->rva0028AE6D();
		}
	} else {
		if (obj->m_flags.test(bit)) {
			obj->m_flags.reset(bit);
			obj->rva0028AE6D();
		}
	}
}

void ScriptActions::rva003C0D6A(const AsciiString &unitName, int which, bool on)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (obj)
		rva003C0CEE(obj, which, on);
}

void ScriptActions::rva003C0D90(const AsciiString &teamName, int which, bool on)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done();
		((Rva001705A0DlinkIterator<Object> *)&iter)->advance()) {
		Object *obj = iter.cur();
		if (obj)
			rva003C0CEE(obj, which, on);
	}
}
