// ??0Rva002A8823Tuning@@QAE@XZ
// partial score=0.95 date=2026-09-26
// cl: /O1 /Oy- /DNDEBUG /MD /GX-
// ATTEMPT for ??0Rva002A8823Tuning@@QAE@XZ (retail 0x002A8823, 34 bytes).
// Near miss: 34/34 bytes, 12/12 insns, sole diff is scheduler order of the
// final `or [eax+0x1c],-1` (ours hoists it above the xor/inc 1-chain, retail
// keeps it last). Refuted: body-init order, mem-init list, |= spelling, ~0
// spelling, /O2 (/Ot: mov ecx,1 + mov -1, 39B), /Os /G5 /G6 /G7 /GB /G3 /GD
// /Ob1 /Oi- (all or-first). The or needs a source-level dependency on the
// ecx 1-chain to pin it late; a barrier-free constant always floats first.
// Next idea: a TU where the -1 store is data-dependent on an earlier store
// (e.g. chained assignment through the same lvalue) or a different
// optimization setting for this TU than the parser TU.

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

// ??0Rva002A8823Tuning@@QAE@XZ
Rva002A8823Tuning::Rva002A8823Tuning()
{
	difficulty = 2;
	economyUpgradeProbability = 1;
	field8 = 1;
	specialPowerActivationProbability = 1;
	field10 = 1;
	offensiveTacticActivationProbability = 1;
	field18 = 1;
	economyMaxFarms = -1;
}
