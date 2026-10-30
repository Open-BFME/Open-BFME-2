// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C1E8CSet@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003C1E8C 54B: team experience
// grant. Resolves the team through rowed ScriptEngine 0x003584E9
// getTeamNamed and applies the all-of iterate 0x0039DD12 with the callback
// 0x002886C2, passing the int through the user data.
// ?Rva002886C2@@YAHPAVObject@@PAX@Z @0x002886C2 39B: the callback converts
// the user data to a float and grants it to the tracker at Object +0x264
// through the pinned 0x0039B315 (amount then true true true false), then
// continues the iteration. Evidence: callee REL32s and the call frame read
// from retail; the tracker class name comes from the pin.
#include "ascii_string.h"

typedef bool Bool;
class Object;
typedef int (__cdecl *TeamPredicate)(Object *obj, void *userData);

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class ExperienceTracker
{
public:
	void rva0039B315(float amount, bool a, bool b, bool c, bool d);
};

struct Rva002886C2Object
{
	char m_pad[0x264];
	ExperienceTracker *m_experienceTracker;
};

int __cdecl Rva002886C2(Object *obj, void *userData)
{
	((Rva002886C2Object *)obj)->m_experienceTracker->rva0039B315((float)(int)userData, true, true, true, false);
	return 1;
}

void ScriptActions::Rva003C1E8CSet(const AsciiString &team, int experience)
{
	Team *targetTeam = TheScriptEngine->getTeamNamed(team, false);
	if (targetTeam != 0)
		targetTeam->rva0039DD12(Rva002886C2, (void *)experience);
}
