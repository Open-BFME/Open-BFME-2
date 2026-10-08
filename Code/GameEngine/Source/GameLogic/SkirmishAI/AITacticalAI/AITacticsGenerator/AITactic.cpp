// cl: /ICode/Libraries/Include/Lib /O1 /MD
#include "Coord3D.h"
// AITactic::initializeTeamTemplate @ 0x004ECE61, 50 bytes: slot 3 of the AITactic
// vtable, which WorldBuilder names initializeTeamTemplate in every tactic that
// overrides it (the AIRingHero/AIRoamingDefense/AITacticDefensive overrides
// call this base); its literal is AITactic.cpp line 386.
// Reads [this+0x20]->+4, random 3..5 into [arg1+0x2d4], always returns true.
// Evidence: 4 callers forwarding (this, arg1, arg2) e.g. 0x005AC924; rowed callee
// ?GetGameLogicRandomValue@@YAHHHPADH@Z with file/line 0x182; vtable slot 3 refs.
int __cdecl GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Team;
class TeamPrototype;
class Object;
enum KindOfType;
template<class T> class DLINK_ITERATOR {
    T *m_cur;
    unsigned char m_targetAbiState[20];
public:
    void advance();
    bool done() const { return m_cur == 0; }
    T *cur() const { return m_cur; }
};
class Object { public: bool isKindOf(KindOfType) const; };

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);			// 0x0039F761
};

extern TeamFactory *TheTeamFactory;

// Team::disband per WorldBuilder (rowed at 0x0039E9E0).
class Team
{
public:
	void disband(); // 0x0039E9E0
	bool hasAnyObjects(bool flag);
    void rva0039E5B9(Coord3D *position);
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
    bool rva0039DAF4() const; // 0x0039DAF4
};

struct Rva002A8AB1Record
{
	void rva004EC07D(TeamPrototype *proto);			// 0x004EC07D
};

class Rva002A8F24
{
public:
	unsigned char m_pad00[0x870];
    float m_movementThreshold;
    Rva002A8AB1Record *rva002A8AB1(void *owner);		// 0x002A8AB1
};

extern Rva002A8F24 *g_00DFEEF8;

// The tactic's target (WorldBuilder AITarget); rowed under a placeholder owner.
class Rva002C589B
{
public:
	void rva002C5843(bool flag);				// 0x002C5843
	void markApproachHazard(void *area);			// 0x002C590F
	void removeTactic() { --m_numTactics; }

	unsigned char m_pad00[4];
	int m_04;						// +0x04
	unsigned char m_pad08[0x19 - 8];
	bool m_19;
	unsigned char m_pad1A[2];
	int m_numTactics;					// +0x1C
};

struct AITacticTeamRecord
{
	unsigned int m_teamID;					// +0x00
	Coord3D m_lastPosition;
	int m_staleFrames;
};

// Existing 20-byte-record erase provider at 0x004ED3A2.
class Rva004ED3A2
{
public:
    void *rva004ED3A2(void *position);
};

// Retail uses the same begin/end/capacity aggregate for the team records.
struct AITacticTeams
{
    AITacticTeamRecord *m_begin;
    AITacticTeamRecord *m_end;
    AITacticTeamRecord *m_cap;
    bool empty() const { return m_begin == m_end; }
};

class AITactic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual bool initializeTeamTemplate(void *p, int dummy);
	virtual unsigned int getNumberOfTeamsNeeded();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();

	void end(bool a, bool b);
	void preUpdate();
	void updateTeamInfos();
	void calcLastTeamPos();
	void cohereTeams();
	void sendTeamToAssistAnotherHorde(Team *team);		// 0x004ED52E

private:
	TeamPrototype **m_protoBegin;				// +0x04
	TeamPrototype **m_protoEnd;				// +0x08
	TeamPrototype **m_protoCap;				// +0x0C
	bool m_10;						// +0x10
	AITacticTeams m_teams;
	Rva002C589B *m_20;					// +0x20
	void *m_24;						// +0x24
	bool m_ended;						// +0x28
	unsigned char m_pad29[0x38 - 0x29];
	Coord3D m_38;
	Coord3D m_44;			// +0x38
	bool m_50;						// +0x50
};

bool AITactic::initializeTeamTemplate(void *p, int /*dummy*/)
{
	void *mid = m_20;
	if (mid == 0)
		return true;
	if (*(int *)((char *)mid + 4) != 0)
		return true;
	*(int *)((char *)p + 0x2D4) = GetGameLogicRandomValue(3, 5, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\AITactic.cpp", 0x182);
	return true;
}

// ?end@AITactic@@QAEX_N0@Z retail 0x004ED748, 213 bytes. WorldBuilder names it
// AITactic::end (AITactic.cpp); retail drops its asserts and the "END: %s ON:
// %s" log. Once only (+0x28): unless told otherwise calls virtual slot 2,
// releases each team prototype from the owner record 0x002A8AB1 gives for
// +0x24, disbands every team (first offering it to another horde unless
// +0x50 is set), then detaches from the target, marking an approach hazard
// when the tactic still needs teams. Both arguments are tested as bytes.
void AITactic::end(bool a, bool b)
{
	if (m_ended)
		return;
	m_ended = true;
	if (!b)
		slot02();

	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_24);
	if (record)
	{
		TeamPrototype **protoEnd = m_protoEnd;
		for (TeamPrototype **it = m_protoBegin; it != protoEnd; ++it)
			record->rva004EC07D(*it);
	}

	AITacticTeamRecord *teamsEnd = m_teams.m_end;
	for (AITacticTeamRecord *rec = m_teams.m_begin; rec != teamsEnd; ++rec)
	{
		Team *team = TheTeamFactory->findTeamByID(rec->m_teamID);
		if (team)
		{
			if (!m_50)
				sendTeamToAssistAnotherHorde(team);
			team->disband();
		}
	}

	if (m_20)
	{
		if (a)
			m_20->rva002C5843(true);
		else if (!b && getNumberOfTeamsNeeded() > 0)
			m_20->markApproachHazard(&m_38);
		m_20->removeTactic();
		m_20 = 0;
	}
	m_10 = false;
}

// ?preUpdate@AITactic@@QAEXXZ retail 0x004EDF03, 211 bytes.
// FACT: native range ends at 0x004EDFD6; WB identifies AITactic::preUpdate
// with the same findTeamByID, hasAnyObjects, record erase and end callees.
// FACT: record stride 0x14, target flag +0x19, current/previous points +0x38/+0x44.
// The vector aggregate retains retail's [edi+4] empty test after vslot 4.
// The final indirect call is vslot 8; its method name remains unresolved.
void AITactic::preUpdate()
{
    AITacticTeamRecord *it = m_teams.m_begin;
    while (it != m_teams.m_end) {
        Team *team = TheTeamFactory->findTeamByID(it->m_teamID);
        if (team && team->hasAnyObjects(false))
            ++it;
        else
            it = (AITacticTeamRecord *)((Rva004ED3A2 *)&m_teams.m_begin)->rva004ED3A2(it);
    }
    if ((!m_10 && m_20 && m_20->m_19) ||
        (m_10 && getNumberOfTeamsNeeded() > 0 && m_teams.empty()))
        end(false, false);
    else if (m_10) {
        updateTeamInfos();
        calcLastTeamPos();
        if (m_44.x == 0.0f && m_44.y == 0.0f && m_44.z == 0.0f)
            m_44 = m_38;
        cohereTeams();
        slot08();
    }
}

// FACT: native 0x004ECF9C..0x004ED08A, void member ABI; WB names updateTeamInfos.
// FACT: each 20-byte record stores id +0, last position +4, stale frames +0x10.
// Native reads the AI configuration float at +0x870 and compares squared XY
// movement. KindOf value 0x70 and the final Team predicate retain their proven
// call signatures without guessing the unresolved predicate's semantics.
void AITactic::updateTeamInfos()
{
    AITacticTeamRecord *end = m_teams.m_end;
    for (AITacticTeamRecord *rec = m_teams.m_begin; rec != end; ++rec) {
        Team *team = TheTeamFactory->findTeamByID(rec->m_teamID);
        Coord3D position;
        team->rva0039E5B9(&position);
        float dx = position.x - rec->m_lastPosition.x;
        float dy = position.y - rec->m_lastPosition.y;
        float threshold = g_00DFEEF8->m_movementThreshold;
        bool moved = false;
        if (dx * dx + dy * dy > threshold * threshold) {
            rec->m_lastPosition = position;
            moved = true;
        }
        bool hasKind = false;
        DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
        while (!iter.done() && !hasKind) {
            if (iter.cur()->isKindOf((KindOfType)0x70)) hasKind = true;
            iter.advance();
        }
        if (!moved && !hasKind && !team->rva0039DAF4()) ++rec->m_staleFrames;
        else rec->m_staleFrames = 0;
    }
}

