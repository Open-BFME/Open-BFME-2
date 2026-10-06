// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva003C2121Grant@@YGXABVAsciiString@@0@Z @0x003C2121 69B
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

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern class ScriptEngine *TheScriptEngine;

class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern "C" UpgradeCenter *TheUpgradeCenter;

void __stdcall Rva003C2121Grant(const AsciiString &teamName, const AsciiString &upgradeName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeName);
	if (!team)
		return;
	if (!upgrade)
		return;
	team->rva0039DB31(upgrade);
}
