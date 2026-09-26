// cl: /O1 /DNDEBUG /MD /GX-
// Rva002A88C7_CombatChainEntry default ctor (retail 0x002A88C7, 39 bytes).
// Serves the CombatChainDefinition entry of the table at 0x7FDA50
// (siblings: BrutalDifficultyCheats, DifficultyTuning,
// AnyTypeTemplateDisabledSlots). The entry layout is retail-owned: the unit
// id at +0x00 (default -1, parsed through 0x004E8E57), 16 target-type ids
// at +0x04 (default -1, parsed through the rowed parseAIKindOfList at
// 0x004E8EA6) and 16 target-priority modifiers at +0x44 (default 0.0,
// parsed as reals through 0x004E8D8C). The struct name is a readable local
// model; the owning struct is BFME2-new (no BFME1 donor).

extern "C" void *memset(void *dst, int val, unsigned int n);

struct CombatChainEntry
{
	CombatChainEntry();
	int unit;
	int targetTypes[16];
	float targetPriorityModifiers[16];
};

// ??0CombatChainEntry@@QAE@XZ
CombatChainEntry::CombatChainEntry()
{
	unit = -1;
	memset(targetTypes, -1, 0x40);
	memset(targetPriorityModifiers, 0, 0x40);
}
