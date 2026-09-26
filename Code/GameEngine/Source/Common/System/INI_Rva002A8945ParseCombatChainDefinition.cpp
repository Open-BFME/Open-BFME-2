// cl: /O1 /DNDEBUG /MD /GX-
// Rva002A88C7_CombatChainEntry default ctor (retail 0x002A88C7, 39 bytes),
// Rva002A88EE_CombatChainEntry copy-assign (retail 0x002A88EE, 52 bytes) and
// Rva002A8945_ParseCombatChainDefinition (retail 0x002A8945, 69 bytes).
// Serves the CombatChainDefinition entry of the table at 0x7FDA50
// (siblings: BrutalDifficultyCheats, DifficultyTuning,
// AnyTypeTemplateDisabledSlots). The entry layout is retail-owned: the unit
// id at +0x00 (default -1, parsed through 0x004E8E57), 16 target-type ids
// at +0x04 (default -1, parsed through the rowed parseAIKindOfList at
// 0x004E8EA6) and 16 target-priority modifiers at +0x44 (default 0.0,
// parsed as reals through 0x004E8D8C). The parser fills a stack temp
// through the rowed INI::initFromINI at 0x002DE78 with the three-entry
// table at 0xBFD804, then assigns the temp into instance indexed by the
// parsed unit id (imul 0x84 stride). The struct name is a readable local
// model; the owning struct is BFME2-new (no BFME1 donor).

struct FieldParse;

extern "C" void *memset(void *dst, int val, unsigned int n);
extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

struct CombatChainEntry
{
	CombatChainEntry();
	CombatChainEntry &operator=(const CombatChainEntry &that);
	int unit;
	int targetTypes[16];
	float targetPriorityModifiers[16];
};

class INI
{
public:
	void initFromINI(void *instance, const FieldParse *table);
	static void Rva002A8945_ParseCombatChainDefinition(INI *ini, void *instance, void *store, const void *userData);
};

// ??0CombatChainEntry@@QAE@XZ
CombatChainEntry::CombatChainEntry()
{
	unit = -1;
	memset(targetTypes, -1, 0x40);
	memset(targetPriorityModifiers, 0, 0x40);
}

// ??4CombatChainEntry@@QAEAAU0@ABU0@@Z
CombatChainEntry &CombatChainEntry::operator=(const CombatChainEntry &that)
{
	unit = that.unit;
	memcpy(targetTypes, that.targetTypes, 0x40);
	memcpy(targetPriorityModifiers, that.targetPriorityModifiers, 0x40);
	return *this;
}

// ?Rva002A8945_ParseCombatChainDefinition@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva002A8945_ParseCombatChainDefinition(INI *ini, void *instance, void *store, const void *userData)
{
	CombatChainEntry entry;
	ini->initFromINI(&entry, reinterpret_cast<const FieldParse *>(0x00BFD804));
	((CombatChainEntry *)instance)[entry.unit] = entry;
}
