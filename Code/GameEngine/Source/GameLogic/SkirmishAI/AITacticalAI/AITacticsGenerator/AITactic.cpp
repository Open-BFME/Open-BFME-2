// cl: /ICode/Libraries/Include/Lib /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "ascii_string.h"
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

struct Rva00506909Request;
struct Rva003A2FD4Proto;
extern const char *AITargetTypeNames[];
class Team;
class TeamPrototype
{
public:
	unsigned int snapshotID() const { return m_id; }
private:
	unsigned char m_pad[0xC];
	unsigned int m_id; // +0x0C
    unsigned char m_pad10[0x2CC - 0x10];
public:
    int m_tacticKind; // +0x2CC
    unsigned char m_pad2D0[0x2DC - 0x2D0];
    unsigned int m_tacticOrdinal; // +0x2DC
};

class Xfer
{
public:
	class Version;
	virtual ~Xfer();
	virtual bool isLoading();				// +0x04
	virtual bool isSaving();				// +0x08
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual Xfer &operator==(Version &value);		// +0x28
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void xferCoord3D(Coord3D *value);		// +0x60
	virtual void v25();
	virtual void v26();
	virtual void xferAsciiString(AsciiString *value);	// +0x6C
	virtual void v28();
	virtual void v29();
	virtual void xferUnsignedInt(unsigned int *value);	// +0x78
	virtual void xferInt(int *value);			// +0x7C
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void xferBool(bool *value);			// +0x90
};

class Xfer::Version
{
public:
	Version(unsigned char current) : m_loaded(0), m_current(current) {}
	unsigned char m_loaded;
	unsigned char m_current;
};

class Player
{
public:
	int getPlayerIndex() const { return m_index; }
    const AsciiString &nameForTeamCreation() const { return m_ownerName; }
private:
	unsigned char m_pad[0x4C];
    AsciiString m_ownerName;
    unsigned char m_pad50[4];
	int m_index;						// +0x54
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);			// 0x002A7A29
};
extern PlayerList *ThePlayerList;


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
	Rva003A2FD4Proto *initTeamForTacticalAI(const AsciiString &name, void *ownerName, int targetID, unsigned int tacticID);
    TeamPrototype *findTeamPrototypeByID(unsigned int id);
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
    void *rva002A8B73(void *owner, int id);
    Rva002A8AB1Record *rva002A8AB1(void *owner);		// 0x002A8AB1
};

extern Rva002A8F24 *g_00DFEEF8;
extern int g_00E044AC;

// The tactic's target (WorldBuilder AITarget); rowed under a placeholder owner.
class Rva002C589B
{
public:
	void rva002C5843(bool flag);				// 0x002C5843
	void markApproachHazard(void *area);			// 0x002C590F
	int rva0030F2C7() const;
    void removeTactic() { --m_numTactics; }

	unsigned char m_pad00[4];
	int m_04;						// +0x04
	unsigned char m_pad08[0x19 - 8];
	bool m_19;
	unsigned char m_pad1A[2];
	int m_numTactics; // +0x1C
    int m_tacticLimit; // +0x20
    unsigned char m_pad24[0x38 - 0x24];
    unsigned int m_id; // +0x38
    unsigned int getID() const { return m_id; }
};

// Same 20-byte record constructed at 0x004ECDA7 and transferred at 0x004ECDC8.
class Rva004ECDC8 {
public:
    Rva004ECDC8(unsigned int);
    void rva004ECDC8(Xfer *xfer);
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
	virtual void xfer(Xfer *xfer);
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();

	void end(bool a, bool b);
	void preUpdate();
    bool start(Rva00506909Request *request, void *owner);
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
	unsigned char m_pad29[3];
    AsciiString m_name;
    unsigned int m_30;
    bool m_34;
    unsigned char m_pad35[3];
	Coord3D m_38;
	Coord3D m_44; // +0x44
	bool m_50;
    bool m_51;
    unsigned int m_54; // +0x51
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


// FACT: native 0x004EDA8C..0x004EDCE9, WB AITactic::DoXfer.
// Versioned tactic state: prototype ids, 20-byte team records, owner/target ids,
// and fields +0x28..+0x54. The target id getter preserves retail local sharing.
void AITactic::xfer(Xfer *xfer)
{
	Xfer::Version version(2);
	*xfer == version;
	xfer->xferUnsignedInt((unsigned int *)&g_00E044AC);

	unsigned int protoCount = m_protos.size();
	xfer->xferUnsignedInt(&protoCount);
	if (xfer->isSaving())
	{
		std::vector<TeamPrototype *>::iterator end = m_protos.end();
		for (std::vector<TeamPrototype *>::iterator it = m_protos.begin(); it != end; ++it)
		{
			unsigned int id = (*it)->snapshotID();
			xfer->xferUnsignedInt(&id);
		}
	}
	else if (xfer->isLoading())
	{
		for (unsigned int i = 0; i < protoCount; ++i)
		{
			unsigned int id = 0;
			xfer->xferUnsignedInt(&id);
			TeamPrototype *proto = TheTeamFactory->findTeamPrototypeByID(id);
			m_protos.push_back(proto);
		}
	}

	xfer->xferBool(&m_10);

	unsigned int teamCount = m_teams.size();
	xfer->xferUnsignedInt(&teamCount);
	if (xfer->isSaving())
	{
		Rva004ECDC8 *end = m_teams.end();
		for (Rva004ECDC8 *rec = m_teams.begin(); rec != end; ++rec)
			rec->rva004ECDC8(xfer);
	}
	else if (xfer->isLoading())
	{
		for (unsigned int i = 0; i < teamCount; ++i)
		{
			Rva004ECDC8 rec(0);
			rec.rva004ECDC8(xfer);
			m_teams.push_back(rec);
		}
	}

	int playerIndex = (xfer->isSaving() && m_24) ? ((Player *)m_24)->getPlayerIndex() : -1;
	xfer->xferInt(&playerIndex);
	if (xfer->isLoading() && playerIndex != -1)
		m_24 = ThePlayerList->getNthPlayer(playerIndex);

	unsigned int targetID = m_20 ? m_20->getID() : (unsigned int)-1;
	xfer->xferUnsignedInt(&targetID);
	if (xfer->isLoading() && targetID != (unsigned int)-1)
		m_20 = (Rva002C589B *)g_00DFEEF8->rva002A8B73(m_24, targetID);

	xfer->xferBool(&m_ended);
	xfer->xferAsciiString(&m_name);
	xfer->xferUnsignedInt(&m_30);
	xfer->xferBool(&m_34);
	xfer->xferCoord3D(&m_38);
	xfer->xferCoord3D(&m_44);
	xfer->xferBool(&m_50);
	if (version.m_current >= 2)
	{
		xfer->xferBool(&m_51);
		xfer->xferUnsignedInt(&m_54);
	}
}


// FACT: WB request-based AITactic::start; native 004ED81D..004ED955.
// AL true/false and RET8 establish bool; target count/limit +1C/+20 and
// owner AsciiString +4C agree with the existing factory provider.
bool AITactic::start(Rva00506909Request *request, void *owner)
{
    // The generator retains an opaque legacy request handle; native stores
    // exactly this same target into +0x20 and accesses its established fields.
    Rva002C589B *target = (Rva002C589B *)request;
    int limit = target->m_tacticLimit;
    if (target->rva0030F2C7() < limit) {
        m_20 = target;
        m_24 = owner;
        unsigned int created = 0;
        for (unsigned int i = 0; i < getNumberOfTeamsNeeded(); ++i) {
            AsciiString name;
            const char *kind = target->m_04 != -1 ? AITargetTypeNames[target->m_04] : "INVALID";
            name.format("%s_%s_%u_%u", kind, m_name.str(), m_30, i);
            TeamPrototype *proto = (TeamPrototype *)TheTeamFactory->initTeamForTacticalAI(
                name, (void *)&((Player *)owner)->nameForTeamCreation(), (int)target->getID(), m_30);
            if (proto) {
                m_protos.push_back(proto);
                proto->m_tacticKind = target->m_04;
                proto->m_tacticOrdinal = i;
                if (initializeTeamTemplate(proto, i)) ++created;
            }
        }
        if (created == getNumberOfTeamsNeeded()) {
            ++target->m_numTactics;
            return true;
        }
    }
    m_20 = 0;
    end(false, false);
    return false;
}



