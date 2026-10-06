// cl: /O1 /EHsc /MD /arch:SSE
// LivingWorldBattle.cpp -- battle-player members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. Swapping two armies exchanges their pointers in
// the array at +0x04 and swaps the matching 0x68-byte army records at +0x10
// through 0x003F40EF (unnamed).

typedef int Int;

class LivingWorldArmy;

struct BattleArmyRecord
{
	unsigned char m_data[0x68];
};

void rva003F40EF(BattleArmyRecord *a, BattleArmyRecord *b);	// 0x003F40EF

template <class T> inline void swapValues(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

class LivingWorldBattle
{
public:
	class BattlePlayer
	{
	public:
		void SwapArmies(Int first, Int second);

	private:
		unsigned char m_pad00[4];
		LivingWorldArmy **m_armies;		// +0x04
		unsigned char m_pad08[8];
		BattleArmyRecord *m_records;		// +0x10
	};
};

// LivingWorldBattle::BattlePlayer::SwapArmies, retail 0x003F427D.
void LivingWorldBattle::BattlePlayer::SwapArmies(Int first, Int second)
{
	swapValues(m_armies[first], m_armies[second]);
	rva003F40EF(&m_records[first], &m_records[second]);
}
