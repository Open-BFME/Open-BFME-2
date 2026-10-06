// cl: /Oy- /DNDEBUG /MD /GX-
// ??0Rva002A8823Tuning@@QAE@XZ @ 0x002A8823 (34B). DifficultyTuning default ctor with 2 plus six 1s plus -1.
// Evidence: sole caller ParseDifficultyTuning at 0x002A89DD; six probability fields plus max farms.
// Two _ReadWriteBarriers pin mov-2-first and or-minus-1-last; barrier-free floats or first.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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

Rva002A8823Tuning::Rva002A8823Tuning()
{
	difficulty = 2;
	_ReadWriteBarrier();
	economyUpgradeProbability = 1;
	field8 = 1;
	specialPowerActivationProbability = 1;
	field10 = 1;
	offensiveTacticActivationProbability = 1;
	field18 = 1;
	_ReadWriteBarrier();
	economyMaxFarms = -1;
}
