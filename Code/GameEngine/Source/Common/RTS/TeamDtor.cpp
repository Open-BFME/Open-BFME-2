// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /MD /EHs /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Team@@MAE@XZ @0x003A354F 388B.
// Identity: WorldBuilder Team.cpp Team::~Team (asserts at lines 1964..1989,
// "proto should not be null") matched by call graph; the Team vtables
// 0x00C1AEFC / 0x00C1AEB8 are the ones Team::Team (0x003A39A7) installs.
// Target facts: TheScriptEngine cleanup through rowed 0x002051B7, the
// drain of the ObjectID set at +0x130 through the pinned 0x003A23A5, the
// per-player relation cleanup (rowed 0x002A9CF0 on getNthPlayer), disband,
// TheTeamFactory->markTeamDoneForTacticalAI, the prototype instance-list
// unlink through rowed 0x0039D40F / 0x0039D4D8 on the +0x334 head, the two
// relation maps at +0x118 / +0x11C freed through virtual slot 0 with 0 and
// the global operator delete, the +0x48 table clear (0x003A2A41), the
// list<int> clear at +0x12C, SkirmishAI::UnRegister on the record of the
// prototype's +8 owner from the global at 0x00DFEEF8, then the member and
// base dtors (EH states 4..0). Donor: ZH Team.cpp Team::~Team supplies the
// order and field names; offsets without a donor counterpart keep address
// names. /EHs, not /EHsc: retail keeps the unwind state store before the
// list<int> dtor, whose body frees through the extern "C" free.
#include <list>
#include "ascii_string.h"
#include "Common/Snapshot.h"

class Object;
class Team;

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
private:
	char m_04[0x2C - 4];
};

struct Rva000427195
{
	void rva003A2A41();
};

// ??1Rva003A393A@@QAE@XZ @0x003A2EBD 57B: the dtor of Team's +0x48 table,
// whose ctor is 0x003A393A (Team::Team constructs the member through it and
// Team::~Team destroys it through this body). The clear it calls is the
// folded 0x003A2A41, ledger-named on its sibling class Rva000427195, and the
// bucket vector at +4 frees through the plain free 0x00030830; same body as
// ??1Rva000427195@@QAE@XZ (0x001FDEDB) apart from its own EH handler.
struct Rva003A393ABuckets
{
	~Rva003A393ABuckets()
	{
		if (m_begin)
			free(m_begin);
	}
	void **m_begin;
	void **m_end;
	void **m_storageEnd;
};

class Rva003A393A
{
public:
	~Rva003A393A();
	void clear() { ((Rva000427195 *)this)->rva003A2A41(); }
private:
	void *m_hash;
	Rva003A393ABuckets m_buckets;		// +0x04
	unsigned int m_numElements;		// +0x10
};

Rva003A393A::~Rva003A393A()
{
	clear();
}

struct Rva002EE9B7Node
{
	int m_color;
	Rva002EE9B7Node *m_parent;
	Rva002EE9B7Node *m_left;
	Rva002EE9B7Node *m_right;
	unsigned int m_value;
};

class Rva002EE9B7
{
public:
	~Rva002EE9B7();
	bool empty() const { return m_nodeCount == 0; }
	const unsigned int &front() const { return m_header->m_left->m_value; }
private:
	Rva002EE9B7Node *m_header;
	unsigned int m_nodeCount;
	int m_compare;
};

class Rva0039D40F
{
public:
	bool rva0039D40F(Rva0039D40F **head) const;
};

class Rva0039D4D8
{
public:
	void rva0039D4D8(Rva0039D40F *team);
};

class TeamPrototype
{
private:
	char m_00[8];
	void *m_owner;					// +0x08
	char m_0C[0x334 - 0x0C];
	Rva0039D40F *m_dlinkhead_TeamInstanceList;	// +0x334
	friend class Team;
};

class RelationMapBase
{
public:
	virtual void *deleteInstance(int flags);
};

class ScriptEngine
{
public:
	void rva002051B7(Object *obj);
};
extern ScriptEngine *TheScriptEngine;

class Player;

class Rva002A9CF0
{
public:
	void rva002A9CF0(int team);
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
	int getPlayerCount() const { return m_playerCount; }
private:
	char m_00[0x14];
	int m_playerCount;
};
extern PlayerList *ThePlayerList;

class TeamFactory
{
public:
	void markTeamDoneForTacticalAI(Team *team);
};
extern TeamFactory *TheTeamFactory;

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *key);
};
extern Rva002A8F24 *g_00DFEEF8;

class SkirmishAI
{
public:
	void UnRegister(Team *team);
};

class Team : public Snapshot, public Rva0055B0CC
{
public:
	void disband();
	void rva003A23A5(unsigned int id, int flag);
protected:
	virtual ~Team();
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
private:
	TeamPrototype *m_proto;			// +0x30
	int m_id;				// +0x34
	char m_38[0x44 - 0x38];
	AsciiString m_state;			// +0x44
	Rva003A393A m_48;			// +0x48
	char m_5C[0x118 - 0x5C];
	RelationMapBase *m_teamRelations;	// +0x118
	RelationMapBase *m_playerRelations;	// +0x11C
	char m_120[0x12C - 0x120];
	_STL::list<int> m_xferMemberIDList;	// +0x12C
	Rva002EE9B7 m_130;			// +0x130
};

Team::~Team()
{
	if (TheScriptEngine)
		TheScriptEngine->rva002051B7((Object *)this);

	while (!m_130.empty())
		rva003A23A5(m_130.front(), 0);

	if (ThePlayerList)
	{
		for (int i = 0; i < ThePlayerList->getPlayerCount(); ++i)
		{
			Player *p = ThePlayerList->getNthPlayer(i);
			if (p)
				((Rva002A9CF0 *)p)->rva002A9CF0((int)this);
		}
	}

	disband();
	TheTeamFactory->markTeamDoneForTacticalAI(this);

	TeamPrototype *proto = m_proto;
	if (proto)
	{
		if (((Rva0039D40F *)this)->rva0039D40F(&proto->m_dlinkhead_TeamInstanceList))
			((Rva0039D4D8 *)proto)->rva0039D4D8((Rva0039D40F *)this);
	}

	::operator delete(m_teamRelations ? m_teamRelations->deleteInstance(0) : 0);
	m_teamRelations = 0;
	::operator delete(m_playerRelations ? m_playerRelations->deleteInstance(0) : 0);
	m_playerRelations = 0;

	m_48.clear();
	m_xferMemberIDList.clear();

	if (g_00DFEEF8)
	{
		Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(m_proto->m_owner);
		if (rec)
			((SkirmishAI *)rec)->UnRegister(this);
	}
}
