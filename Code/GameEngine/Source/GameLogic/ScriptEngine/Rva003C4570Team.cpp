// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva003C4570Do@@YGXABVAsciiString@@0@Z @0x003C4570 100B.
// Team-plus-ExperienceLevel script helper: getTeamNamed kir teamizmi level find
// via NameKey plus rowed rva0028951F then two Team::rva0039DD12 iterates.
// Retail pushes level ptr plus 0x6886A7 then 0 plus 0x688726 callbacks.
// Evidence: chain lane via 0x28951F just landed; prev doTeamAttackNamed same
// two-AsciiString void shape plus same ScriptEngine global 0xDFE16C.
typedef int Int;
typedef bool Bool;

class Object;
class Team;

#include "ascii_string.h"


class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
};
extern ScriptEngine *TheScriptEngine;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Overridable
{
public:
	void *m_v0;
};

class Rva0028951F
{
public:
	const Overridable *rva0028951F(int key);
};

class DLINK_ITERATOR_Object;
typedef int (__cdecl *TeamPredicate)(Object *obj, void *userData);

class Team
{
public:
	int rva0039DD12(TeamPredicate pred, void *userData) const;
};

// The object's member at +0x264 receives both per-object calls.
struct Rva003C4570Object
{
	char m_pad[0x264];
	void *m_264;
};

struct Rva0039B24FInput;

class Rva0039B24F
{
public:
	void rva0039B24F(Rva0039B24FInput *input, int a, bool b);
};

class Rva0039B20C
{
public:
	void rva0039B246();
};

// Team iterate callback 0x002886A7 (27B): hand the experience level found
// above to each member's +0x264 object, then continue.
int __cdecl Rva002886A7(Object *obj, void *userData)
{
	((Rva0039B24F *)((Rva003C4570Object *)obj)->m_264)->rva0039B24F((Rva0039B24FInput *)userData, 1, false);
	return 1;
}

// Team iterate callback 0x00288726 (19B): the follow-up call on the same
// +0x264 object, then continue.
int __cdecl Rva00288726(Object *obj, void *userData)
{
	((Rva0039B20C *)((Rva003C4570Object *)obj)->m_264)->rva0039B246();
	return 1;
}

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

void __stdcall Rva003C4570Do(const AsciiString &teamName, const AsciiString &levelName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	int key = TheNameKeyGenerator->nameToKey(levelName);
	const Overridable *lvl = reinterpret_cast<Rva0028951F *>(TheExperienceLevelSystem)->rva0028951F(key);
	if (!lvl)
		return;
	team->rva0039DD12(Rva002886A7, (void *)lvl);
	team->rva0039DD12(Rva00288726, 0);
}
