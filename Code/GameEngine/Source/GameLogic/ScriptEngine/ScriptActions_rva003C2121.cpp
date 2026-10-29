// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C2121Grant@ScriptActions@@QAEXABVAsciiString@@0@Z @0x003C2121 69B
// Grant upgrade to named team: ScriptEngine::getTeamNamed(team,false) via
// rowed 0x003584E9 with StringBase copy 0x000365F0, UpgradeCenter::findUpgrade
// via rowed 0x0026F26D, then Team::rva0039DB31 via rowed 0x0039DB31 when both
// are non-null. Both calls run before either null test (team saved across
// the second call). Evidence: caller 0x003CDE34; neighbours 0x003C207C and
// 0x003C2662; globals g_Va009FE16C TheUpgradeCenter.
#include "ascii_string.h"

class Team
{
public:
	void rva0039DB31(const void *arg);
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

void ScriptActions::Rva003C2121Grant(const AsciiString &teamName, const AsciiString &upgradeName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeName);
	if (!team)
		return;
	if (!upgrade)
		return;
	team->rva0039DB31(upgrade);
}
