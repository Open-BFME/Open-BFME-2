// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// Landed from the banked attempt once Zero Hour's null-member skip
// (Object *obj = iter.cur(); if (!obj) continue;) was added to the member
// loop: it keeps the member in ecx from the loop test into the call, the
// mov-test wall the bank recorded.
// ?Rva003C30D9Do@ScriptActions@@QAEXABVAsciiString@@_N@Z @0x003C30D9 156B: team DualWeaponBehavior module flag via getTeamNamed cached NameKey iterate findModule. Evidence: single Rva003C3175Do same DualWeapon static findModule set byte; rowed getTeamNamed 0x3584E9 iterate 0x263864 advance 0x263526 findModule 0x28B6D6 nameToKey PBD 0x148E1A StringBase copy 0x365F0 DualWeaponBehavior literal; caller 0x003CE542; ret 0x8 stdcall.
#include "ascii_string.h"

enum NameKeyType { NK_NONE = 0 };

#include "../../../Include/Common/Module.h"

// DualWeaponBehavior's flag byte at +0x20; only the store is recovered.
class DualWeaponBehaviorView : public Module
{
public:
	char m_pad08[0x18];
	unsigned char m_20;
};

class Object;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend void ScriptActions::Rva003C30D9Do(const AsciiString &, bool);
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

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

void ScriptActions::Rva003C30D9Do(const AsciiString &teamName, bool flag)
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
		((DualWeaponBehaviorView *)module)->m_20 = flag;
	}
}
