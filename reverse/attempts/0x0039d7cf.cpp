// ?getControllingPlayer@Team@@QBEPAVPlayer@@XZ
// partial score=0.75 date=2026-09-09
// cl: /O2 /DNDEBUG /MD
//
// Team::getControllingPlayer, retail 0x0039D7CF, 12 bytes.
// Dedicated TU so Object::getControllingPlayer cannot inline this body.
// If Team+0x30 is live, return the Player* at that object's +8.

class Player;

struct TeamPlayerHolder
{
	char pad[8];
	Player *player;
};

class Team
{
	char pad[0x30];
	TeamPlayerHolder *m_playerHolder;

public:
	Player *getControllingPlayer() const;
};

Player *Team::getControllingPlayer() const
{
	TeamPlayerHolder *holder = m_playerHolder;
	if (holder)
		return holder->player;
	return 0;
}
