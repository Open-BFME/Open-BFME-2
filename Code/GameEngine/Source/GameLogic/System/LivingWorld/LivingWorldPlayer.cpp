// cl: /O1 /G7 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
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
#include "FixedStorage128.h"

namespace _STL
{
	// Keep the already verified pointer-vector erase provider out of line.
	template <> void **vector<void *>::erase(void **position);
}

// Native2E12F3..2E134C and WBDE4FC0 prove the216-byte stride and
// the key atAC. Native2E1451..2E14DD and the verified UnitRevivalEntry
// copies establish the consumed experience/rank/upgrade fields. The remaining
// fields and the key-search method name remain unknown.
struct LivingWorldPlayerRecordView
{
	char unknown00[8];
    float experience;
    int rank, level;
    BfmeFixedStorage128 upgrades;
    char unknown94[0xAC - 0x94];
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

// The existing61B provider consumes a24-byte subrecord. These are
// pointer views into that record; no objects of the declaration-only class
// are constructed here.
class Rva001EAFC1 { public: Rva001EAFC1 &operator=(const Rva001EAFC1 &); };
struct LivingWorldRevivalUnitDataView {
    char unknown00[8]; float experience; int rank; BfmeFixedStorage128 upgrades;
    char unknown90[4]; char record94[0x18];
};
class Rva002E0D93;
class Rva002E204D { public: Rva002E0D93 *rva002E204D(Rva002E0D93 *); };
// Existing opaque native predicate at 0x00318F42. Native and WB identify
// the receiver as an element of m_armyVec; its original method is unknown.
class Mbr002E0B30 { public: unsigned char pred(); };
class LivingWorldPlayer
{
public:
	typedef _STL::vector<void *> ArmyVec;

	void OnUnitDequeued(Rva00319CED *unit);
	void **RemoveArmy(void **&iter);
	bool rva002E12F3(int key);
	bool rva002E0B30();
    void RemoveRevivalUnit(int key);
    void GetRevivalUnitData(int key, LivingWorldRevivalUnitDataView *out);

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

// WBDE5040 names RemoveRevivalUnit; native2E2225..2E2285 RET4.
// Reuse the full61B216-byte vector erase at2E204D under its owner spelling.
void LivingWorldPlayer::RemoveRevivalUnit(int key)
{
    if (key == 0) return;
    for (unsigned int i = 0; i < m_records.size(); ++i) {
        if (m_records[i].key == key) {
            reinterpret_cast<Rva002E204D *>(&m_records)->rva002E204D(
                reinterpret_cast<Rva002E0D93 *>(&m_records[i]));
            break;
        }
    }
}
// WBDE64F0 names GetRevivalUnitData; native2E1451..2E14DD RET8.
// Output field offsets are target facts; its original type name is unknown.
void LivingWorldPlayer::GetRevivalUnitData(int key, LivingWorldRevivalUnitDataView *out)
{
    if (key == 0) return;
    for (unsigned int i = 0; i < m_records.size(); ++i) {
        const LivingWorldPlayerRecordView &entry = m_records[i];
        if (entry.key == key) {
            out->rank = entry.rank;
            out->experience = entry.experience;
            out->upgrades = entry.upgrades;
            *reinterpret_cast<Rva001EAFC1 *>(out->record94) =
                *reinterpret_cast<const Rva001EAFC1 *>(entry.unknownB0);
            break;
        }
    }
}
// Native2E0B30..2E0B76, 70B; WBDE45B0 independently scans the army vector
// at1B8 and calls318F42 until true. Signed span arithmetic retains retail's
// recomputed vector count. Player/m_armyVec identity is established by the
// existing RemoveArmy body; the predicate and member names remain unknown.
bool LivingWorldPlayer::rva002E0B30()
{
 int *span=(int *)&m_armyVec;
 for(unsigned int i=0; i<(unsigned)((span[1]-span[0])>>2); ++i)
  if (((Mbr002E0B30 *)m_armyVec[i])->pred()) return true;
 return false;
}
