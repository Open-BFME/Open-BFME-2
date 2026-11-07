// cl: /Oy- /DNDEBUG /MD /GX-
// ?Rva004FD77CParse@@YAXPAVINI@@PAVScenario@LivingWorldScenario@@@Z @0x004FD77C 98B.
// TeamDefeatCondition ParseINI helper: new Rva004FCD49 0x14, initFromINI via
// table TeamDefeatConditionFieldParse, then holder->addTeamDefeatCondition. Throws INIException code 3 with
// retail literal when either pointer is null.
// Evidence: chain lane calls landed 0x004FD3E2; caller 0x004FD7B5 pattern;
// table VA 0x00C63640 defined below; string "Invalid data in
// TeamDefeatCondition::ParseINI"; throwinfo anchor 0x00CFE2FC; neighbours
// Rva004135CDParse/Rva00413DCCParse same filler plus CxxThrow recipe.
class INI;
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

void Rva004FCB23Parse(INI *ini, void *instance, void *store, const void *userData);

class ModuleData;

class Rva004FCD49
{
public:
	Rva004FCD49();
	virtual ~Rva004FCD49();
private:
	char m_pad[0x10];
};

#include "../../Include/Common/LivingWorldScenario.h"

class LivingWorldScenario::Scenario
{
public:
	void addTeamDefeatCondition(const ModuleData *p);
};

// Retail's TeamDefeatCondition field table at VA 0x00C63640 (.rdata, 48
// bytes), transcribed from retail's own bytes: two records plus the null
// terminator.
extern const FieldParse TeamDefeatConditionFieldParse[] =
{
	{ "Teams",                             &Rva004FCB23Parse, 0, 0x04 },
	{ "NumControlledRegionsLessOrEqualTo", &INI::parseInt,    0, 0x10 },
	{ 0, 0, 0, 0 }
};

void Rva004FD77CParse(INI *ini, LivingWorldScenario::Scenario *holder)
{
	if (!ini || !holder)
	{
		throw INIException(3, "Invalid data in TeamDefeatCondition::ParseINI");
	}
	Rva004FCD49 *p = new Rva004FCD49;
	ini->initFromINI(p, TeamDefeatConditionFieldParse);
	holder->addTeamDefeatCondition((const ModuleData *)p);
}
