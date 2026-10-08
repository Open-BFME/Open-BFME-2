// cl: /ICode/Libraries/Include/Lib /O1 /MD /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "Coord3D.h"
// Existing bfmealloc shim and no-exception STL configuration reproduce the
// native record-vector helpers. Each body and recursive relocation was checked.
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
	unsigned char m_pad00[0x30];
    TeamPrototype *m_prototype;
    unsigned int m_teamID;
    unsigned int getID() const { return m_teamID; }
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

// Same 20-byte record constructed at 0x004ECDA7 and transferred at 0x004ECDC8.
class Rva004ECDC8 {
public:
    Rva004ECDC8(unsigned int);
    Rva004ECDC8(const Rva004ECDC8 &that) { *this = that; }
    Rva004ECDC8 &operator=(const Rva004ECDC8 &that);
    unsigned int m_teamID;
    Coord3D m_lastPosition;
    int m_staleFrames;
};
typedef Rva004ECDC8 AITacticTeamRecord;

// Existing 20-byte-record erase provider at 0x004ED3A2.
class Rva004ED3A2
{
public:
    void *rva004ED3A2(void *position);
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
    void NotifyTeamCreated(Team *team);
	void updateTeamInfos();
	void calcLastTeamPos();
	void cohereTeams();
	void sendTeamToAssistAnotherHorde(Team *team);		// 0x004ED52E

private:
	std::vector<TeamPrototype *> m_protos;
	bool m_10;						// +0x10
	std::vector<Rva004ECDC8> m_teams;
	Rva002C589B *m_20;					// +0x20
	void *m_24;						// +0x24
	bool m_ended;						// +0x28
	unsigned char m_pad29[0x38 - 0x29];
	Coord3D m_38;
	Coord3D m_44; // +0x44
	bool m_50;
    bool m_51; // +0x51
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
		TeamPrototype **protoEnd = m_protos.end();
		for (TeamPrototype **it = m_protos.begin(); it != protoEnd; ++it)
			record->rva004EC07D(*it);
	}

	AITacticTeamRecord *teamsEnd = m_teams.end();
	for (AITacticTeamRecord *rec = m_teams.begin(); rec != teamsEnd; ++rec)
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
    AITacticTeamRecord *it = m_teams.begin();
    while (it != m_teams.end()) {
        Team *team = TheTeamFactory->findTeamByID(it->m_teamID);
        if (team && team->hasAnyObjects(false))
            ++it;
        else
            it = (AITacticTeamRecord *)((Rva004ED3A2 *)&m_teams)->rva004ED3A2(it);
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
    AITacticTeamRecord *end = m_teams.end();
    for (AITacticTeamRecord *rec = m_teams.begin(); rec != end; ++rec) {
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


// FACT: WB AITactic::NotifyTeamCreated; native 0x004ED6D2..0x004ED748.
// A created team's id (+0x34) becomes a record; its prototype (+0x30) is
// removed from pending prototypes. +0x51 becomes true when all needed teams
// have arrived before the tactic has started (+0x10 false).
void AITactic::NotifyTeamCreated(Team *team)
{
    if (m_ended) return;
    m_teams.push_back(Rva004ECDC8(team->getID()));
    TeamPrototype **end = m_protos.end();
    for (TeamPrototype **it = m_protos.begin(); it != end; ++it) {
        if (team->m_prototype == *it) {
            m_protos.erase(it);
            break;
        }
    }
    if (!m_10 && (int)m_teams.size() == getNumberOfTeamsNeeded())
        m_51 = true;
}

// ?Rva004ECDC8::operator= present-unmatched
// Native 0x004ECEA8 copies these five words; this unrowed instantiation is
// retained for the complete record-vector fold proof, not counted as new bytes.
Rva004ECDC8 &Rva004ECDC8::operator=(const Rva004ECDC8 &that)
{
    m_teamID = that.m_teamID;
    m_lastPosition.x = that.m_lastPosition.x;
    m_lastPosition.y = that.m_lastPosition.y;
    m_lastPosition.z = that.m_lastPosition.z;
    m_staleFrames = that.m_staleFrames;
    return *this;
}

