// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
// Rva002A8928_BrutalDifficultyCheats default ctor (retail 0x002A8928, 22
// bytes). Builds the {0.0, default} float pair the BrutalDifficultyCheats
// parser (rowed 0x002A898A) fills through initFromINI: buildCostReduction
// is 0.0, buildTimeReduction comes from the float global at 0xBC2424 (same
// default the rowed parser TU names kBrutalDifficultySecondDefault). The
// struct name mirrors the sibling parser TU; the owning struct is BFME2-new
// (no BFME1 donor).

struct BrutalDifficultyCheats
{
	BrutalDifficultyCheats();
	float buildCostReduction;
	float buildTimeReduction;
};

extern const float kBrutalDifficultySecondDefault;

// ??0BrutalDifficultyCheats@@QAE@XZ
BrutalDifficultyCheats::BrutalDifficultyCheats()
{
	buildCostReduction = 0.0f;
	buildTimeReduction = kBrutalDifficultySecondDefault;
}
