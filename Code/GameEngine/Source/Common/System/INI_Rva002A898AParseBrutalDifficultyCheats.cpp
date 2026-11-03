// cl: /Oy- /DNDEBUG /MD /GX-
// Rva002A898A_ParseBrutalDifficultyCheats (retail 0x002A898A, 72 bytes).
// Builds a float pair {0.0, default from the float global at 0xBC2424},
// fills it through the rowed INI::initFromINI at 0x002DE78 with the two
// entry table at 0xBFD85C (BuildCostReduction at +0, BuildTimeReduction at
// +4, both through 0x42F1BA), then stores the pair at instance+0x840.
// Serves the BrutalDifficultyCheats entry of the table at 0x7FDA50
// (siblings: CombatChainDefinition, DifficultyTuning,
// AnyTypeTemplateDisabledSlots). The struct name is a readable local model;
// the owning struct is BFME2-new (no BFME1 donor).

class INI;
#include "../../../Include/Common/INI/FieldParse.h"

struct BrutalDifficultyCheats
{
	float buildCostReduction;
	float buildTimeReduction;
};


#include "../../../Include/Common/INI/INI.h"

// Retail's BrutalDifficultyCheats field table at VA 0x00BFD85C (.rdata, 32
// bytes), transcribed from retail's own bytes. Retail has no zero sentinel
// after the second record: the token strings follow directly.
extern const FieldParse BrutalDifficultyCheatsFieldParse[] =
{
	{ "BuildCostReduction", &INI::parsePercentToReal, 0, 0x0 },
	{ "BuildTimeReduction", &INI::parsePercentToReal, 0, 0x4 }
};

// ?Rva002A898A_ParseBrutalDifficultyCheats@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva002A898A_ParseBrutalDifficultyCheats(INI *ini, void *instance, void *store, const void *userData)
{
	BrutalDifficultyCheats cheats;
	cheats.buildCostReduction = 0.0f;
	cheats.buildTimeReduction = 0.1f;
	ini->initFromINI(&cheats, BrutalDifficultyCheatsFieldParse);
	float *slot = (float *)((char *)instance + 0x840);
	slot[0] = cheats.buildCostReduction;
	slot[1] = cheats.buildTimeReduction;
}
