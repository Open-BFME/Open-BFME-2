// cl: /O1 /Oy- /DNDEBUG /MD /GX- /arch:SSE
// Rva002A898A_ParseBrutalDifficultyCheats (retail 0x002A898A, 72 bytes).
// Builds a float pair {0.0, default from the float global at 0xBC2424},
// fills it through the rowed INI::initFromINI at 0x002DE78 with the two
// entry table at 0xBFD85C (BuildCostReduction at +0, BuildTimeReduction at
// +4, both through 0x42F1BA), then stores the pair at instance+0x840.
// Serves the BrutalDifficultyCheats entry of the table at 0x7FDA50
// (siblings: CombatChainDefinition, DifficultyTuning,
// AnyTypeTemplateDisabledSlots). The struct name is a readable local model;
// the owning struct is BFME2-new (no BFME1 donor).

struct FieldParse;

struct BrutalDifficultyCheats
{
	float buildCostReduction;
	float buildTimeReduction;
};

extern const float kBrutalDifficultySecondDefault;

class INI
{
public:
	void initFromINI(void *instance, const FieldParse *table);
	static void Rva002A898A_ParseBrutalDifficultyCheats(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva002A898A_ParseBrutalDifficultyCheats@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva002A898A_ParseBrutalDifficultyCheats(INI *ini, void *instance, void *store, const void *userData)
{
	BrutalDifficultyCheats cheats;
	cheats.buildCostReduction = 0.0f;
	cheats.buildTimeReduction = kBrutalDifficultySecondDefault;
	ini->initFromINI(&cheats, reinterpret_cast<const FieldParse *>(0x00BFD85C));
	float *slot = (float *)((char *)instance + 0x840);
	slot[0] = cheats.buildCostReduction;
	slot[1] = cheats.buildTimeReduction;
}
