// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0020F483@Rva0020EE29@@QAEXXZ retail 0x0020F483..0x0020F569 (230 bytes).
// Recomputes every living-world player's region bonus (WB twin 0x00B57FD0
// callgraph 2.0 with LivingWorldLogic::GetPlayerAtIndex and
// LivingWorldPlayer::CheckForRemovedMultiRegionBonuses). For each player of
// TheLivingWorldLogic (pointer vector at +0x8C; rowed lookup 0x002B52A8) it
// zeroes the six bonus words +0x25C..+0x270 then calls the rowed 0x002E1FA5
// and adds the +0x8C bonus of every region in this +0x8 manager's vector at
// +0x2C whose owner at +0x13C is the player's +0x14 id (rowed 0x0020E250).
// The manager's rule bonuses follow (rowed 0x0020F34E) then the rowed
// 0x002E0BEB with 0 and CheckForRemovedMultiRegionBonuses 0x002E1FC2.

template <class T> struct Rva0020F483PtrVector
{
	T **m_begin;
	T **m_end;
	unsigned int size() const { return m_end - m_begin; }
	T *operator[](unsigned int i) const { return m_begin[i]; }
};

class Rva0020E449
{
public:
	void rva0020E250(const Rva0020E449 &other);

	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

class Rva002E1FA5
{
public:
	void rva002E1FA5();
};

class Rva002E0BEB
{
public:
	void rva002E0BEB(void *arg);
};

class Rva002E2285;
class Rva002E2903Player;

class LivingWorldPlayer
{
public:
	void CheckForRemovedMultiRegionBonuses();

	char m_pad00[0x14];
	int m_id;
	char m_pad18[0x258 - 0x18];
	Rva0020E449 m_bonus;
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(int index);
};

class LivingWorldLogic
{
public:
	int getNumPlayers() const { return m_players.size(); }
	LivingWorldPlayer *getPlayerAtIndex(int index)
	{
		return reinterpret_cast<LivingWorldPlayer *>(reinterpret_cast<Rva002BA8F1Logic *>(this)->rva002B52A8(index));
	}

private:
	char m_pad00[0x8C];
	Rva0020F483PtrVector<LivingWorldPlayer> m_players;
};
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva0020F483Region
{
	char m_pad00[0x8C];
	Rva0020E449 m_bonus;
	char m_pad[0x13C - 0x8C - sizeof(Rva0020E449)];
	int m_owner;
};

class Rva0020F77C
{
public:
	void rva0020F34E(void *owner, Rva002E2285 *player);

	char m_pad00[0x2C];
	Rva0020F483PtrVector<Rva0020F483Region> m_regions;
};

class Rva0020EE29
{
public:
	void rva0020F483();

private:
	char m_pad00[8];
	Rva0020F77C *m_manager;
};

void Rva0020EE29::rva0020F483()
{
	for (int i = 0; i < TheLivingWorldLogic->getNumPlayers(); i++)
	{
		LivingWorldPlayer *player = TheLivingWorldLogic->getPlayerAtIndex(i);
		Rva0020E449 *bonus = &player->m_bonus;
		bonus->m_04 = 0;
		bonus->m_08 = 0;
		bonus->m_0C = 0;
		bonus->m_10 = 0;
		bonus->m_14 = 0;
		bonus->m_18 = 0;
		reinterpret_cast<Rva002E1FA5 *>(player)->rva002E1FA5();
		Rva0020F483PtrVector<Rva0020F483Region> &regions = m_manager->m_regions;
		for (unsigned int j = 0; j < regions.size(); j++)
		{
			Rva0020F483Region *region = regions[j];
			if (region->m_owner == player->m_id)
				bonus->rva0020E250(region->m_bonus);
		}
		m_manager->rva0020F34E(this, reinterpret_cast<Rva002E2285 *>(player));
		reinterpret_cast<Rva002E0BEB *>(player)->rva002E0BEB(0);
		player->CheckForRemovedMultiRegionBonuses();
	}
}
