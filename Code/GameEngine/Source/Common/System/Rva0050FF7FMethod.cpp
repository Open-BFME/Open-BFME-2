// cl: /O1 /G7 /MD /Ireference/shims/bfme2_ascii /EHsc
// ?rva0050FF7F@Rva0050F5A6@@QAEHIPAVGameWindow@@I@Z retail 0x0050FF7F 65B
// Message router over Rva0050F5A6 array: forwards msg/window/val to each
// non-null Rva0050F0AB entry via rowed rva0050FED4, returns 1 on first handled,
// else 0. Evidence: rowed callee 0x0050FED4, count at +0x20 stride-8 array at
// +0x28 as in Rva0050F0AB.cpp Rva0050F5A6, caller 0x005101D3, ret 0xC.
class GameWindow;
struct Rva0050F4D0Money { unsigned int pad00; unsigned int balance; };
class Player {
public:
	bool isPlayerActive() const;
	Rva0050F4D0Money *getMoneyView() { return &money; }
private:
	char pad00[0x90];
	Rva0050F4D0Money money;
};
struct Rva0050F4D0PlayerList { char pad00[0x10]; Player *localPlayer; };
extern class PlayerList *ThePlayerList;
class Rva0050F041 { public: void rva0050FF1C(); };


class Rva0050F0AB
{
public:
	int rva0050FED4(unsigned int msg, GameWindow *window, unsigned int val);
	void rva0050F2AF(unsigned int val);
	char pad00[0x6c];
	unsigned int amount;
};

class Rva0050F5A6
{
public:
	int rva0050FF7F(unsigned int msg, GameWindow *window, unsigned int val);
	void rva0050F4D0();
	void rva0050FFC0();
private:
	char m_pad00[0x20];
	int m_20;
		struct Entry
	{
		Player *m_player;
		Rva0050F0AB *m_obj;
	};
	Entry m_entries[1];
};

int Rva0050F5A6::rva0050FF7F(unsigned int msg, GameWindow *window, unsigned int val)
{
	for (int i = 0; i < m_20; ++i)
	{
		Rva0050F0AB *entry = m_entries[i].m_obj;
		if (entry != 0 && entry->rva0050FED4(msg, window, val) == 1)
			return 1;
	}
	return 0;
}

static inline const unsigned int &Rva0050F4D0Min(const unsigned int &a, const unsigned int &b)
{
	return a < b ? a : b;
}
// Native 0x0050F4D0..0x0050F5A6, 214B: distribute the local player's
// available balance across the paired player/panel entries at +0x24.
// Target establishes ThePlayerList+0x10, balance at Player+0x94, unsigned
// minima, panel amount +0x6c, count +0x20 and the rowed active predicate/setter.
// The money view's +0x90 base comes from the target's explicit null test;
// its source type and the original method name remain unknown.
void Rva0050F5A6::rva0050F4D0()
{
	Player *local = ((Rva0050F4D0PlayerList *)ThePlayerList)->localPlayer;
	Rva0050F4D0Money *money = local->getMoneyView();
	unsigned int balance = 0;
	if (money)
		balance = money->balance;
	unsigned int remaining = balance;
	for (int i = 0; i < m_20; ++i)
	{
		Entry &entry = m_entries[i];
		if (entry.m_player != local && entry.m_obj && entry.m_player->isPlayerActive())
			{
			unsigned int requested = entry.m_obj->amount;
			remaining -= Rva0050F4D0Min(remaining, requested);
		}
	}
	unsigned int left = balance;
	for (int i = 0; i < m_20; ++i)
	{
		Entry &entry = m_entries[i];
		if (entry.m_player != local && entry.m_obj)
		{
			if (entry.m_player->isPlayerActive())
			{
				unsigned int available = entry.m_obj->amount + remaining;
				entry.m_obj->rva0050F2AF(Rva0050F4D0Min(left, available));
			}
			else
				entry.m_obj->rva0050F2AF(0);
			left -= entry.m_obj->amount;
		}
	}
}

// Native 0x0050FFC0..0x0050FFEC, 44B; no Ghidra entry. The caller at
// 0x005101E2 tail-jumps here with its +0x24 child. The complete body updates
// the same paired array through 0x0050F4D0 and each panel's rowed 0x0050FF1C.
void Rva0050F5A6::rva0050FFC0()
{
	rva0050F4D0();
	for (int i = 0; i < m_20; ++i)
		if (m_entries[i].m_obj)
			((Rva0050F041 *)m_entries[i].m_obj)->rva0050FF1C();
}
