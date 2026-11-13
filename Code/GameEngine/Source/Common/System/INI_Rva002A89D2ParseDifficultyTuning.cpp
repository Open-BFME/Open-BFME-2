// cl: /Oy- /DNDEBUG /MD /GX-
// Rva002A89D2_ParseDifficultyTuning (retail 0x002A89D2, 61 bytes). The temp
// is 8 ints: the difficulty index (default 2) plus 7 tuning fields (all 1
// except EconomyMaxFarms at +0x1C, -1), default-built through the pinned
// Rva002A8823Tuning ctor at 0x002A8823. The parser fills the temp through
// the rowed INI::initFromINI at 0x002DE78 with the five-entry table at
// 0xBFD768 (Difficulty at +0 through 0x0023899F, the two probability fields
// through 0x002A8845, EconomyMaxFarms through parseInt), then copies the
// whole temp as one 32-byte struct assignment into instance+0x878 indexed
// by the parsed difficulty (rep movsd). Serves the DifficultyTuning entry
// of the table at 0x7FDA50 (siblings: CombatChainDefinition,
// BrutalDifficultyCheats). The class name stays address-derived; the owning
// struct is BFME2-new (no BFME1 donor).

class INI;
#include "../../../Include/Common/INI/FieldParse.h"
typedef void (*FieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

#include "../../../Include/Common/Rva002A8823Tuning.h"

#include "../../../Include/Common/INI/INI.h"

void Rva0023899FParse(INI *ini, int, int *);

// Retail's DifficultyTuning field table at VA 0x00BFD768 (.rdata, 80 bytes),
// transcribed from retail's own bytes. Retail has no zero sentinel after the
// fifth record: the token strings follow directly.
extern const FieldParse DifficultyTuningFieldParse[] =
{
	{ "Difficulty",                           (FieldParseProc)&Rva0023899FParse,  0, 0x00 },
	{ "EconomyUpgradeProbability",            &INI::Rva002A8845_ParseProbability, 0, 0x04 },
	{ "EconomyMaxFarms",                      &INI::parseInt,                     0, 0x1C },
	{ "SpecialPowerActivationProbability",    &INI::Rva002A8845_ParseProbability, 0, 0x0C },
	{ "OffensiveTacticActivationProbability", &INI::Rva002A8845_ParseProbability, 0, 0x14 }
};

// ?Rva002A89D2_ParseDifficultyTuning@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva002A89D2_ParseDifficultyTuning(INI *ini, void *instance, void *store, const void *userData)
{
	Rva002A8823Tuning tuning;
	ini->initFromINI(&tuning, DifficultyTuningFieldParse);
	((Rva002A8823Tuning *)((char *)instance + 0x878))[tuning.difficulty] = tuning;
}
