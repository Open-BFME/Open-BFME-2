// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Team@@QAE@PAVTeamPrototype@@H@Z @0x003A39A7 471B.
// Identity: WorldBuilder Team.cpp Team::Team (assert "proto should not be null"
// at line 1928) and the existing pin; TeamFactory::createInactiveTeam calls it
// on a 0x13C-byte block. Target facts: Snapshot vtable 0x00BBB554 at +0, the
// rowed 0x2C-byte base ctor 0x0055B048 at +4, final vtables 0x00C1AEFC /
// 0x00C1AEB8, the hash table member at +0x48 (rowed ctor 0x003A393A, cleared
// through rowed 0x003A2A41), list<int> at +0x12C and set<AsciiString> at
// +0x130 (rowed out-of-line ctors), two 0x18-byte relation maps at +0x11C
// (PlayerRelationMap 0x002AF6F7) and +0x118 (TeamRelationMap 0x003A3959),
// the "/" and " - creating team instance." concats and the 32-entry bool/int
// arrays at +0x70/+0x90. Donor: ZH Team.cpp Team::Team supplies the field
// names, the enemy-sighted script test (prototype +0x200 then +0x1FC) and the
// debug message; offsets without a donor counterpart keep address names.
#include <list>
#include <set>
#include "ascii_string.h"
#include "Common/Snapshot.h"

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
private:
	char m_04[0x2C - 4];
};

class Rva003A393A
{
public:
	Rva003A393A();
	~Rva003A393A();
private:
	char m_table[0x14];
};

class Rva000427195
{
public:
	void rva003A2A41();
};

class Rva003A3959
{
public:
	Rva003A3959();
private:
	char m_data[0x18];
};
typedef Rva003A3959 TeamRelationMap;

class PlayerRelationMap
{
public:
	PlayerRelationMap();
private:
	char m_data[0x18];
};

class Rva0039D40F;

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }
	void prependTo_TeamInstanceList(Rva0039D40F *team);
private:
	char m_00[0x10];
	AsciiString m_name;				// +0x10
	AsciiString m_14;				// +0x14
	char m_18[0x1FC - 0x18];
	AsciiString m_scriptOnEnemySighted;	// +0x1FC
	AsciiString m_scriptOnAllClear;		// +0x200
	friend class Team;
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &msg, bool clear);
};
extern ScriptEngine *TheScriptEngine;

class Object;
class Waypoint;

enum { MAX_GENERIC_SCRIPTS = 32 };

class Team : public Snapshot, public Rva0055B0CC
{
public:
	Team(TeamPrototype *proto, int id);
protected:
	virtual ~Team();
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
private:
	TeamPrototype *m_proto;			// +0x30
	int m_id;						// +0x34
	Object *m_dlinkhead_TeamMemberList;	// +0x38
	Team *m_dlink_TeamInstanceList_prev;	// +0x3C
	Team *m_dlink_TeamInstanceList_next;	// +0x40
	AsciiString m_state;			// +0x44
	Rva003A393A m_48;				// +0x48
	bool m_enteredOrExited;			// +0x5C
	bool m_active;					// +0x5D
	bool m_created;					// +0x5E
	bool m_5F;						// +0x5F
	bool m_checkEnemySighted;		// +0x60
	bool m_seeEnemy;				// +0x61
	bool m_prevSeeEnemy;			// +0x62
	bool m_wasIdle;					// +0x63
	int m_destroyThreshold;			// +0x64
	int m_curUnits;					// +0x68
	Waypoint *m_currentWaypoint;	// +0x6C
	bool m_shouldAttemptGenericScript[MAX_GENERIC_SCRIPTS];	// +0x70
	int m_90[MAX_GENERIC_SCRIPTS];	// +0x90
	bool m_isRecruitablitySet;		// +0x110
	bool m_isRecruitable;			// +0x111
	bool m_112;						// +0x112
	bool m_113;						// +0x113
	int m_commonAttackTarget;		// +0x114
	TeamRelationMap *m_teamRelations;	// +0x118
	PlayerRelationMap *m_playerRelations;	// +0x11C
	float m_120;					// +0x120
	int m_124;						// +0x124
	bool m_128;						// +0x128
	_STL::list<int> m_12C;			// +0x12C
	_STL::set<AsciiString> m_130;	// +0x130
};

Team::Team(TeamPrototype *proto, int id) :
	m_proto(proto),
	m_id(id),
	m_dlinkhead_TeamMemberList(0),
	m_dlink_TeamInstanceList_prev(0),
	m_dlink_TeamInstanceList_next(0),
	m_enteredOrExited(false),
	m_active(false),
	m_created(false),
	m_5F(false),
	m_checkEnemySighted(false),
	m_seeEnemy(false),
	m_prevSeeEnemy(false),
	m_wasIdle(false),
	m_destroyThreshold(0),
	m_curUnits(0),
	m_currentWaypoint(0),
	m_isRecruitablitySet(false),
	m_isRecruitable(false),
	m_112(false),
	m_113(false),
	m_120(0.0f),
	m_124(0),
	m_128(false)
{
	m_commonAttackTarget = 0;

	m_playerRelations = new PlayerRelationMap;
	m_teamRelations = new TeamRelationMap;
	((Rva000427195 *)&m_48)->rva003A2A41();

	if (proto)
	{
		proto->prependTo_TeamInstanceList((Rva0039D40F *)this);
		if (!proto->m_scriptOnAllClear.isEmpty() ||
				!proto->m_scriptOnEnemySighted.isEmpty())
		{
			m_checkEnemySighted = true;
		}

		AsciiString teamName = proto->getName();
		teamName.concat("/");
		teamName.concat(proto->m_14);
		teamName.concat(" - creating team instance.");
		TheScriptEngine->AppendDebugMessage(teamName, false);
	}

	for (int i = 0; i < MAX_GENERIC_SCRIPTS; ++i)
	{
		m_shouldAttemptGenericScript[i] = true;
		m_90[i] = 0;
	}
}
