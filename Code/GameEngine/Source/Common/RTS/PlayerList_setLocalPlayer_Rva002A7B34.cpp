// cl: /O1 /MD /DNDEBUG
//
// ?setLocalPlayer@PlayerList@@QAEXPAVPlayer@@@Z
// retail 0x002A7B34, 93 bytes (Ghidra FUN_006a7b34).
//
// Donor: GeneralsMD PlayerList.cpp setLocalPlayer - a null player becomes the
// neutral player (+0x18), and on a change the old local player (+0x10) and
// the new one get becomingLocalPlayer(false/true) (0x002ADFF2, pinned).
// BFME 2 then re-registers two per-local-player callbacks: the shroud
// manager (VA 0x00DFE74C) gets the player's index (+0x54) with the
// callback at 0x002D7AE0, and the taint manager (VA 0x00DFE750) the
// callback at 0x002D7B18. Both calls go through the ledger's existing rows
// for those thunks (0x00739730, 0x006C0800); the callbacks' names are
// unknown and kept under their addresses.

class PartitionManager;
class PointGroupClass
{
public:
	enum PointModeEnum
	{
		TRIS = 0
	};
};

class Rva00739730
{
public:
	void rva00739730(int playerIndex, int callback);
};

class Rva006C0800
{
public:
	void rva006C0800(PointGroupClass::PointModeEnum callback);
};

extern PartitionManager *TheShroudManager;	// VA 0x00DFE74C
extern void *g_Va00DFE750;			// the taint manager, VA 0x00DFE750

void Rva002D7AE0LocalPlayerShroudCallback();
void Rva002D7B18LocalPlayerTaintCallback();

class Player
{
public:
	void becomingLocalPlayer(bool yes);
	int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad00[0x54];
	int m_playerIndex;
};

class PlayerList
{
public:
	Player *getNeutralPlayer() { return m_players[0]; }
	void setLocalPlayer(Player *player);
private:
	void *m_vtable;
	char m_pad04[0x10 - 0x04];
	Player *m_local;
	char m_pad14[0x18 - 0x14];
	Player *m_players[1];
};

void PlayerList::setLocalPlayer(Player *player)
{
	// can't set local player to null -- if you try, you get neutral.
	if (player == 0)
	{
		player = getNeutralPlayer();
	}

	if (player != m_local)
	{
		// m_local can be null the very first time we call this.
		if (m_local)
			m_local->becomingLocalPlayer(false);
		m_local = player;
		player->becomingLocalPlayer(true);
	}

	if (TheShroudManager)
		((Rva00739730 *)TheShroudManager)->rva00739730(player->getPlayerIndex(), (int)&Rva002D7AE0LocalPlayerShroudCallback);
	if (g_Va00DFE750)
		((Rva006C0800 *)g_Va00DFE750)->rva006C0800((PointGroupClass::PointModeEnum)(int)&Rva002D7B18LocalPlayerTaintCallback);
}
