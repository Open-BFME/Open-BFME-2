// cl: /GX- /MD
// ?doesTeamMeetThreat@AITeamBuilder@@QAEHPAVTeam@@@Z @0x0059A1C1 151B.
// Chain of 0x002A8B73: lookup max via global Rva002A8F24 then float-gate the
// Team sum of +0x51c over members whose template kind has 8 at +0x108 or 4 at
// +0x113. Evidence: caller 0x0059AD0D; callees rowed 0x002A8B73 0x002C5AE6
// 0x00263864 0x00263526; prev Rva00599FD7Count Team/iterator pattern.
class ThingTemplate
{
public:
	char m_pad00[0x108];
	unsigned char m_kind0; // +0x108
	char m_pad109[0xA];
	unsigned char m_kind1; // +0x113
	char m_pad114[0x408];
	float m_threatLevel; // +0x51C
};

#include "../../../Libraries/Include/Lib/Coord3D.h"
enum ObjectStatusTypes { STATUS_90=90 };
class Team;
struct RecruitThingTemplate;
class AIUpdateInterface;
class Object
{
public:
	void setTeam(Team*);
	bool testStatus(ObjectStatusTypes) const;
	Team *getTeam() const { return team; }
	const RecruitThingTemplate *getTemplate() const { return objectTemplate; }
	char m_pad00[0x4];
	RecruitThingTemplate * objectTemplate; // +0x04
	char m_pad08[0x30];
	Coord3D position; // +0x38
	char m_pad44[0x30];
	int objectID; // +0x74
	char m_pad78[0x1E0];
	AIUpdateInterface * ai; // +0x258
	char m_pad25C[0xA8];
	Team * team; // +0x304
	char m_pad308[0x130];
	unsigned char flag438; // +0x438
	char m_pad439[0x87];
	unsigned int frame4c0; // +0x4C0
};

template<class T> class DLINK_ITERATOR;
template<> class DLINK_ITERATOR<Object>
{
private:
    Object *m_cur;
    unsigned char m_targetAbiState[20];
public:
    void advance();
    bool done() const { return m_cur == 0; }
    Object *cur() const { return m_cur; }
};

struct TeamProto
{
	char m_pad[0x2C4];
	int m_2C4;
};

class TeamPrototype;
template<class T> class DLINK_ITERATOR;
class Team
{
public:
	Team *dlink_next_TeamInstanceList() const;
	void disband();
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	char m_pad00[0x30];
	TeamPrototype *prototype30; // +0x30
	char m_pad34[0x29];
	bool active; // +0x5D
	bool dirty; // +0x5E
	char m_pad5F[0xB1];
	bool flag110; // +0x110
	bool flag111; // +0x111
	char m_pad112[0x2];
};

struct Rva002A8AB1Record;
class Player;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *);
	void *rva002A8F24(Player *);
	void *rva002A8B73(void *,int);
};
extern Rva002A8F24 *TheSkirmishAIManager;

class Rva002C589B
{
public:
	float getEnemyThreat();
};

class AITeamBuilder
{
public:
	int doesTeamMeetThreat(Team *team);
private:
	char m_pad00[0x14];
	Player *owner14;
};

int AITeamBuilder::doesTeamMeetThreat(Team *team)
{
	void *found = TheSkirmishAIManager->rva002A8B73((void *)owner14, ((TeamProto *)team->prototype30)->m_2C4);
	float vmax = 0.0f;
	if (found != 0)
		vmax = ((Rva002C589B *)found)->getEnemyThreat();
	float sum = 0.0f;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); ((DLINK_ITERATOR<Object> &)iter).advance())
	{
		Object *cur = iter.cur();
		ThingTemplate *thingTemplate = (ThingTemplate *)cur->objectTemplate;
		if ((thingTemplate->m_kind0 & 8) != 0 || (thingTemplate->m_kind1 & 4) != 0)
			sum += thingTemplate->m_threatLevel;
	}
	return sum >= vmax;
}
