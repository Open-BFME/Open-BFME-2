// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004ED08A@Rva004ED08A@@QAEXXZ @0x004ED08A 77B.
// AI group materialization sweep: walk the +0x14/+0x18 entry range in 0x14
// steps; per entry create a group through TheAI, resolve the team id through
// TheTeamFactory, bind it via the rowed Team slot, run the rowed group step,
// and hand the group to the rowed AI sink. All five callees are rowed.
class AIGroup;
class Team;

class AI
{
public:
	AIGroup *createGroup();
	void destroyGroup(AIGroup *group);
};

extern AI *TheAI;

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};

extern TeamFactory *TheTeamFactory;

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class AIGroup
{
public:
	void rva00372C05();
};

struct Rva004ED08AEntry
{
	unsigned int m_id;
	char m_pad[0x14 - 4];
};

class Rva004ED08A
{
public:
	void rva004ED08A();
private:
	char m_pad[0x14];
	Rva004ED08AEntry *m_14;
	Rva004ED08AEntry *m_18;
};

void Rva004ED08A::rva004ED08A()
{
	Rva004ED08AEntry *end = m_18;
	Rva004ED08AEntry *p = m_14;
	if (p == end)
		return;
	do {
		AIGroup *g = TheAI->createGroup();
		Team *t = TheTeamFactory->findTeamByID(p->m_id);
		t->getTeamAsAIGroup(g);
		g->rva00372C05();
		TheAI->destroyGroup(g);
		++p;
	} while (p != end);
}
