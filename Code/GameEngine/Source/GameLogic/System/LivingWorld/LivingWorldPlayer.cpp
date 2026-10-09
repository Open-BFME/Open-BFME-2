// cl: /O1 /G7 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// LivingWorldPlayer.cpp -- LivingWorldPlayer members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function; retail supplies the bytes. The player's queued command points at
// +0x298 drop by the dequeued unit's cost (rowed 0x004E1755) and clamp at 0.
//
// RemoveArmy takes an iterator into m_armyVec (+0x1B8, WB member name), hands
// the army's id (+0x78) to the game logic (0x0023D007, unrowed: forwards to
// the member at GameLogic+0x184) and erases it. The army vector erases
// through the folded pointer-vector erase (rowed as vector<void *>), so the
// view below holds void pointers.

typedef int Int;

#include <vector>

namespace _STL
{
	// Keep the already verified pointer-vector erase provider out of line.
	template <> void **vector<void *>::erase(void **position);
}

// Native2E12F3..2E134C and WBDE4FC0 prove the216-byte stride and
// the key atAC. The remaining fields and the original method name are unknown.
struct LivingWorldPlayerRecordView
{
	char unknown00[0xAC];
	int key;
	char unknownB0[0xD8 - 0xB0];
};

struct LivingWorldArmy
{
	unsigned char m_pad00[0x78];
	Int m_id;				// +0x78
};

class GameLogic
{
public:
	void rva0023D007(Int armyID);		// 0x0023D007
};

extern GameLogic *TheGameLogic;

class Rva00319CED
{
public:
	Int rva004E1755();			// 0x004E1755, command-point cost
};

class LivingWorldPlayer
{
public:
	typedef _STL::vector<void *> ArmyVec;

	void OnUnitDequeued(Rva00319CED *unit);
	void **RemoveArmy(void **&iter);
	bool rva002E12F3(int key);

private:
	unsigned char m_pad000[0x1a8];
	_STL::vector<LivingWorldPlayerRecordView> m_records;
	unsigned char m_pad1B4[4];
	ArmyVec m_armyVec;			// +0x1B8
	unsigned char m_pad1C4[0x298 - 0x1c4];
	Int m_queuedCommandPoints;		// +0x298
};

// LivingWorldPlayer::OnUnitDequeued, retail 0x002E0764.
void LivingWorldPlayer::OnUnitDequeued(Rva00319CED *unit)
{
	m_queuedCommandPoints -= unit->rva004E1755();
	if (m_queuedCommandPoints < 0)
		m_queuedCommandPoints = 0;
}

// LivingWorldPlayer::RemoveArmy, retail 0x002E10FE.
void **LivingWorldPlayer::RemoveArmy(void **&iter)
{
	TheGameLogic->rva0023D007(((LivingWorldArmy *)*iter)->m_id);
	return m_armyVec.erase(iter);
}

// Full89-byte RET4 body, with no relocations. The unsigned loop index and
// STLport size calculation retain retail's signed pointer-range division.
bool LivingWorldPlayer::rva002E12F3(int key)
{
	for (unsigned int i = 0; i < m_records.size(); ++i)
	{
		if (m_records[i].key == key)
			return true;
	}
	return false;
}
