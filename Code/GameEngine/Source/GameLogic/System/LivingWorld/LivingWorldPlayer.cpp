// cl: /O1 /EHsc /MD /arch:SSE
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

namespace _STL
{
	template <class T> class allocator {};

	template <class T, class A = allocator<T> > class vector
	{
	public:
		T *erase(T *position);		// 0x001FF51F

	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

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

private:
	unsigned char m_pad000[0x1b8];
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
