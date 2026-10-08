// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// Landed from the banked attempt once Zero Hour's null-member skip
// (Object *obj = iter.cur(); if (!obj) continue;) was added to the member
// loop: it keeps the member in ecx from the loop test into the call, the
// mov-test wall the bank recorded.
// ?Rva003C30D9Do@@YGXABVAsciiString@@_N@Z @0x003C30D9 156B: team DualWeaponBehavior module flag via getTeamNamed cached NameKey iterate findModule. Evidence: single Rva003C3175Do same DualWeapon static findModule set byte; rowed getTeamNamed 0x3584E9 iterate 0x263864 advance 0x263526 findModule 0x28B6D6 nameToKey PBD 0x148E1A StringBase copy 0x365F0 DualWeaponBehavior literal; caller 0x003CE542; ret 0x8 stdcall.
#include "ascii_string.h"

enum NameKeyType { NK_NONE = 0 };

class Object;
class Module
{
public:
	char m_pad00[0x20];
	unsigned char m_20;
};

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend void __stdcall Rva003C30D9Do(const AsciiString &, bool);
};

class Team;

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

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

void __stdcall Rva003C30D9Do(const AsciiString &teamName, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	static NameKeyType dualKey = TheNameKeyGenerator->nameToKey("DualWeaponBehavior");
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Object *obj = it.cur();
		if (!obj)
			continue;
		Module *module = obj->findModule(dualKey);
		if (module == 0)
			continue;
		module->m_20 = flag;
	}
}
