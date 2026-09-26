// cl: /O1 /Oy- /DNDEBUG /MD /GX-
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

struct FieldParse;

class Rva002A8823Tuning
{
public:
	Rva002A8823Tuning();
	int difficulty;
	int economyUpgradeProbability;
	int field8;
	int specialPowerActivationProbability;
	int field10;
	int offensiveTacticActivationProbability;
	int field18;
	int economyMaxFarms;
};

class INI
{
public:
	void initFromINI(void *instance, const FieldParse *table);
	static void Rva002A89D2_ParseDifficultyTuning(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva002A89D2_ParseDifficultyTuning@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva002A89D2_ParseDifficultyTuning(INI *ini, void *instance, void *store, const void *userData)
{
	Rva002A8823Tuning tuning;
	ini->initFromINI(&tuning, reinterpret_cast<const FieldParse *>(0x00BFD768));
	((Rva002A8823Tuning *)((char *)instance + 0x878))[tuning.difficulty] = tuning;
}
