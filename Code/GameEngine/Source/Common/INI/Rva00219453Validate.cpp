// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?Rva00219453Validate@@YA_NHPBD@Z @0x00219453 90B CreateAHero stat validator throws INIException 3 callers 0x00220484
#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/GameLogic/Module/Rva0040BAD0.h"
// Data ledger 0x00A02F74 owns TheAwardSystemManager as Rva0040AAD5*; pin 0x0040AAF8 is a
// Rva0040BAD0 member on the same manager. View the ledger type as derived so
// the data ref keeps its ledger mangling while the call keeps its pin mangling.
class Rva0040AAD5 : public Rva0040BAD0
{
};
extern Rva0040AAD5 *TheAwardSystemManager;

bool __cdecl Rva00219453Validate(int stat, const char *name)
{
	if (stat == 0)
	{
		throw INIException(3, "%s has not been set in CreateAHeroSystem.ini.", name);
	}
	if (TheAwardSystemManager->rva0040AAF8(stat) == 0)
	{
		throw INIException(3, "%s is not a valid statInfo in CreateAHeroSystem.ini.");
	}
	return true;
}
