// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?doTeamPartialUseCommandButton@ScriptActions@@IAEXMABVAsciiString@@0@Z,
// retail 0x003C7276 (295 bytes, EH, RET 12): for the named team, collect the
// members the named command button is valid to use on (from a script) and
// order that many percent of them, rounded up, to use it.
// Donor: Open-BFME-1 ScriptActions_doTeamPartialUseCommandButton.cpp (same
// shape) and Zero Hour ScriptActions::doTeamPartialUseCommandButton; the BFME 2
// layouts are the rowed callees: getTeamNamed 0x003584E9 (name by value),
// ControlBar::findCommandButton 0x0031BE3C, Team::iterate_TeamMemberList
// 0x00263864 and DLINK_ITERATOR::advance 0x00263526 (both out of line, the
// 24-byte iterator copied with rep movsd), the button's validity test
// 0x0035B2C3 (Object, other, position, source), the Object* vector's
// push_back 0x001F211B and Object::doCommandButton 0x00296749.
// The method name is carried from the donor (same arguments and algorithm);
// BFME 2 evidence for it is the unnamed dispatcher slot calling this body.
#include <vector>
#include "ascii_string.h"
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

class Object;
// The storage base destructor only inlines here; retail's out-of-line copy is the /EHs one at 0x001F1609.
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<Object *, allocator<Object *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}

extern "C" __declspec(dllimport) double __cdecl ceil(double);

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Object
{
public:
	void doCommandButton(const class CommandButton *button, int source, bool extra);
};

template <class OBJCLASS>
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

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class CommandButton;
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;

struct Coord3D;
// The button's validity test keeps its address-derived row name and pointer ABI.
class Rva0035B2C3
{
public:
	bool rva0035B2C3(void *object, int other, const Coord3D *position, int source);
};

class ScriptActions
{
protected:
	void doTeamPartialUseCommandButton(float percentage, const AsciiString &teamName, const AsciiString &commandAbility);
};

void ScriptActions::doTeamPartialUseCommandButton(float percentage, const AsciiString &teamName, const AsciiString &commandAbility)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;

	_STL::vector<Object *> objList;
	DLINK_ITERATOR<Object> iter;
	for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (((Rva0035B2C3 *)commandButton)->rva0035B2C3(obj, 0, 0, 1))
			objList.push_back(obj);
	}

	int numObjs = fast_float2long_round((float)ceil(percentage * objList.size() * 0.01f));
	int count = 0;
	for (_STL::vector<Object *>::const_iterator it = objList.begin(); it != objList.end(); ++it) {
		Object *obj = *it;
		if (count >= numObjs)
			return;
		obj->doCommandButton(commandButton, 1, false);
		++count;
	}
}
