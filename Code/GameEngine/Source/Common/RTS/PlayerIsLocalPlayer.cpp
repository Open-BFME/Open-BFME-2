// cl: /DNDEBUG /MD /EHsc

// ?isLocalPlayer@Player@@QBE_NXZ, retail 0x002A9D89 (15 bytes).
// Player::isLocalPlayer is `return this == ThePlayerList->getLocalPlayer()`.
// Retail-measured BFME2 layout: PlayerList::m_localPlayer is at +0x10 here
// (BFME1 donor has +0x0C); ThePlayerList is 0x00DFEEE8 and bakes to its
// absolute (no ledger pin for the global). /O1 keeps the xor-then-cmp-sete
// shape (xor eax,eax; cmp ecx,[edx+0x10]; sete al).

class Player;

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }

private:
	unsigned char m_pad00[ 0x10 ];
	Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;

class Player
{
public:
	bool isLocalPlayer() const;
};

bool Player::isLocalPlayer() const
{
	return this == ThePlayerList->getLocalPlayer();
}
