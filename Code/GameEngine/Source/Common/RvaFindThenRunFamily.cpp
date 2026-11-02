// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Four find-then-run members (23B each): push [esp+4], call <find>,
// test eax, eax, je +7, mov ecx, eax, call <run>, ret 4. /O1 keeps the
// argument push on the stack slot.
// 0x0035519E (AiOrdersManager +0 member Rva0035516C rowed Armor find ->
//   opaque run; row keeps the peer pin),
// 0x003551D3 (same finder -> opaque run at 0x00548632),
// 0x0040D3E8 (ArmySummarySystem::GetArmyCurFramesToReinforceByID: the army
//   lookup 0x0040D008 on its own this -> rowed ArmySummary::rva0040C9F4;
//   WorldBuilder's twin 0x0108DDB0 bears the name and makes the same two
//   calls; GameLogic forwarder 0x0023D0AC adds 0x184 and tail-jumps here).
// Finder/callee identities otherwise unproven; new names address-derived.
// One ledger row per member.

enum NameKeyType
{
	NK_NONE = 0
};

class ArmorTemplate;

class Rva0035516C
{
public:
	const ArmorTemplate *rva0035516C(NameKeyType key) const;
};

#include "../../Include/GameLogic/ArmySummary.h"

class ArmySummarySystem
{
public:
	void *rva0040D008(int id);
	int GetArmyCurFramesToReinforceByID(int id);
};

// The order queue the finder returns for clearOrders (its clear,
// 0x005482E9, recovered in the existing 0x14-byte queue unit).
class Rva0054840A
{
public:
	void rva005482E9(int flags);
	void rva00548527();
	void rva00548632();
};

class AiOrdersManager
{
public:
	void rva0035519E(int value);
	void rva003551D3(int value);
	void clearOrders(int flags, int key);

private:
	Rva0035516C m_finder;
};

void AiOrdersManager::rva0035519E(int value)
{
	const ArmorTemplate *found = m_finder.rva0035516C((NameKeyType)value);
	if (found)
		((Rva0054840A *)found)->rva00548527();
}

void AiOrdersManager::rva003551D3(int value)
{
	const ArmorTemplate *found = m_finder.rva0035516C((NameKeyType)value);
	if (found)
		((Rva0054840A *)found)->rva00548632();
}

int ArmySummarySystem::GetArmyCurFramesToReinforceByID(int id)
{
	ArmySummary *found = (ArmySummary *)rva0040D008(id);
	int frames = (int)found;
	if (found)
		frames = found->rva0040C9F4();
	return frames;
}

// AiOrdersManager::clearOrders, retail 0x00355183 (27 B, ret 8; WorldBuilder
// AiOrdersManager.cpp:340 names it): finds the queue for the key with the
// same finder and clears it with the flags.
void AiOrdersManager::clearOrders(int flags, int key)
{
	const ArmorTemplate *found = m_finder.rva0035516C((NameKeyType)key);
	if (found)
		((Rva0054840A *)found)->rva005482E9(flags);
}
