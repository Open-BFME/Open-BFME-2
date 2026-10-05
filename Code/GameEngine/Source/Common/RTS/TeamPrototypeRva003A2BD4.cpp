// cl: /O1 /MD
// ?rva003A2BD4@TeamPrototype@@QAEXXZ @0x003A2BD4 57B: registers with the
// factory when present, then resolves the +8 holder through rowed
// TeamFactory::addTeamPrototypeToList 0x003A2B78 and pinned PlayerList
// 0x002A8AB1 into pinned Player 0x004EC072. Evidence: m04 feeds the rowed
// factory call, m08 feeds pinned 0x002AE228 and 0x002A8AB1 (ThePlayerList),
// result feeds pinned 0x004EC072; straightline null-guarded chain.
class TeamPrototype;
class Player;
class PlayerList;

class Rva003A2BD4M08
{
public:
	void rva002AE228(TeamPrototype *tp);
};

class TeamFactory
{
public:
	void addTeamPrototypeToList(TeamPrototype *tp);
};

class PlayerList
{
public:
	Player *rva002A8AB1(Rva003A2BD4M08 *m);
};

class Player
{
public:
	void rva004EC072(TeamPrototype *tp);
};

extern PlayerList *ThePlayerList;

class TeamPrototype
{
public:
	void rva003A2BD4(void);

private:
	char m_pad00[4];
	TeamFactory *m_factory04;
	Rva003A2BD4M08 *m_08;
};

void TeamPrototype::rva003A2BD4(void)
{
	if (m_factory04 != 0)
		m_factory04->addTeamPrototypeToList(this);
	if (m_08 != 0) {
		m_08->rva002AE228(this);
		Player *player = ThePlayerList->rva002A8AB1(m_08);
		if (player != 0)
			player->rva004EC072(this);
	}
}
