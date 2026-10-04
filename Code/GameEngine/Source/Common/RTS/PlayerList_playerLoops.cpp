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
//
// Slot 1, 0x002A7EF1, is Zero Hour's PlayerList::init verbatim (one player
// counted, every player re-initialised with no template, the neutral player
// made local), over the same twenty slots; its two callees take Zero Hour's
// names, Player::init and PlayerList::setLocalPlayer (the latter swaps the
// local player at +0x10, ret 4).

typedef int Int;

#define MAX_PLAYER_COUNT 20

class PlayerTemplate;

class Player
{
public:
	void init(const PlayerTemplate *pt);	///< pinned 0x002AF729 (ZH name)
	void update();							///< pinned 0x002AE770 (ZH name, inferred)
	void rva002A99FA();
	void rva002B0D00();
};

class PlayerList
{
public:
	virtual void init();
	virtual void update();
	virtual void rva002A7ACE();
	virtual void rva002A7AE6();

	void setLocalPlayer(Player *player);	///< pinned 0x002A7B34 (ZH name)

private:
	char m_unmodelled_04[0x10 - 0x04];
	Player *m_local;						// +0x10

	Int m_playerCount;						// +0x14
	Player *m_players[MAX_PLAYER_COUNT];	// +0x18
};

void PlayerList::init()
{
	m_playerCount = 1;
	m_players[0]->init(0);

	for (Int i = 1; i < MAX_PLAYER_COUNT; i++)
		m_players[i]->init(0);

	// call setLocalPlayer so that becomingLocalPlayer() gets called appropriately
	setLocalPlayer(m_players[0]);
}

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
