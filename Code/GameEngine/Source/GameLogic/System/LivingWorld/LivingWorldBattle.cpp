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

class Rva003F41A4Elem
{
public:
	void Method(int a, int b, int c, int d, int e);
};

typedef void (Rva003F41A4Elem::*Rva003F41A4Fn)(int, int, int, int, int);

class Rva003F5224List
{
public:
	void forEach(Rva003F41A4Fn fn, int a, int b, int c, int d, int e);

private:
	Rva003F41A4Elem **m_begin;
	Rva003F41A4Elem **m_end;
	Rva003F41A4Elem **m_capacity;
	unsigned int m_index;
};

class Rva005CB260
{
public:
	void rva005CB260();
};

struct Rva003F5397Slot;

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
	void rva003F5397(Int a0, Int a1, Int a2, Int a3);

private:
	char m_pad00[8];
	Rva003F5224List m_list08;
	Rva003F5397Slot *m_table18;
};

struct Rva003F5397Slot
{
	char m_pad[4];
	LivingWorldBattle::BattlePlayer *m_players;
	char m_rest[0x1C - 8];
};

// ?rva003F5397@LivingWorldBattle@@QAEXHHHH@Z @0x003F5397 67B.
// Swap player armies then broadcast via rowed forEach 0x003F5224.
// Evidence: retail imul 0x1C 0x30 plus rowed SwapArmies 0x003F427D plus
// rowed forEach 0x003F5224 with func 0x005CB260 plus caller 0x002B41EB.
void LivingWorldBattle::rva003F5397(Int a0, Int a1, Int a2, Int a3)
{
	((BattlePlayer *)((char *)m_table18[a0].m_players + a1 * 0x30))->SwapArmies(a2, a3);
	m_list08.forEach((Rva003F41A4Fn)&Rva005CB260::rva005CB260, (int)this, a0, a1, a2, a3);
}

// LivingWorldBattle::BattlePlayer::SwapArmies, retail 0x003F427D.
void LivingWorldBattle::BattlePlayer::SwapArmies(Int first, Int second)
{
	swapValues(m_armies[first], m_armies[second]);
	rva003F40EF(&m_records[first], &m_records[second]);
}
