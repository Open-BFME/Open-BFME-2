// cl: /O1 /DNDEBUG /MD /EHsc
//
// Three PlayerList virtuals that hand one Player call to each of the twenty
// player slots (the inline pointer array at +0x18; MAX_PLAYER_COUNT is 20 in
// BFME2, see PlayerList_getNthPlayer.cpp), in vtable 0x00BFD618:
//
//   slot 10  0x002A7AB6  PlayerList::update   -> Player::update 0x002AE770
//   slot 16  0x002A7ACE  rva002A7ACE          -> Player 0x002A99FA
//   slot 15  0x002A7AE6  rva002A7AE6          -> Player 0x002B0D00
//
// Slot 10 is SubsystemInterface::update's slot (GameEngine's update sits in
// slot 10 of its table too), and Zero Hour's PlayerList::update is this loop
// over Player::update; that pairing names the first body and its callee
// (inference). Zero Hour's other two such loops, newMap and updateTeamStates,
// are not virtual there, and the two Player callees do not show which is
// which, so slots 15 and 16 keep address names.

typedef int Int;

#define MAX_PLAYER_COUNT 20

class Player
{
public:
	void update();							///< pinned 0x002AE770 (ZH name, inferred)
	void rva002A99FA();
	void rva002B0D00();
};

class PlayerList
{
public:
	virtual void update();
	virtual void rva002A7ACE();
	virtual void rva002A7AE6();

private:
	char m_unmodelled_04[0x14 - 0x04];
	Int m_playerCount;						// +0x14
	Player *m_players[MAX_PLAYER_COUNT];	// +0x18
};

void PlayerList::update()
{
	for (Int i = 0; i < MAX_PLAYER_COUNT; i++)
		m_players[i]->update();
}

void PlayerList::rva002A7ACE()
{
	for (Int i = 0; i < MAX_PLAYER_COUNT; i++)
		m_players[i]->rva002A99FA();
}

void PlayerList::rva002A7AE6()
{
	for (Int i = 0; i < MAX_PLAYER_COUNT; i++)
		m_players[i]->rva002B0D00();
}
