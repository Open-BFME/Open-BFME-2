// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C1F0A@ScriptActions@@QAEXABVAsciiString@@ABV?$StringBase@D@@M@Z @0x003C1F0A 98B: Script team to AIGroup anim via getTeamNamed createGroup getTeamAsAIGroup and AIGroup slot10; neighbours ScriptActions_rva003C1E69 ScriptActions_rva003C1FAD; caller 0x003CD5F7.
#include "ascii_string.h"

class Team;
class AIGroup;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class AI
{
public:
	AIGroup *createGroup();
};
extern class AI *TheAI;

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *grp);
};

class Drawable;
class Rva002D752DNode;
class Rva002D752D;

class AIGroup
{
public:
	void groupSetEmoticon(const StringBase<char> &name, int val);
};

extern int BfmeLogicFramesPerSecond;

// ?getTeamNamed@ScriptEngine@@QAEPAVTeam@@VAsciiString@@_N@Z present-unmatched
// ?createGroup@AI@@QAEPAVAIGroup@@XZ present-unmatched
// ?getTeamAsAIGroup@Team@@QAEXPAVAIGroup@@@Z present-unmatched
// AIGroup::groupSetEmoticon is rowed at 0x0036E1C3 (AIGroupRva0036E1C3.cpp).
void ScriptActions::Rva003C1F0A(const AsciiString &teamName, const StringBase<char> &animName, float f)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team == 0)
		return;
	AIGroup *grp = TheAI->createGroup();
	if (grp == 0)
		return;
	team->getTeamAsAIGroup(grp);
	int v = (int)((float)BfmeLogicFramesPerSecond * f);
	grp->groupSetEmoticon(animName, v);
}
