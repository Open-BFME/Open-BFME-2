// ?xfer@AITactic@@UAEXPAVXfer@@@Z
// partial score=0.9 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?xfer@AITactic@@UAEXPAVXfer@@@Z retail 0x004EDA8C, 605 B: WorldBuilder AITactic::DoXfer.
// Bank: logic, calls and offsets match; stack slots differ (retail reuses the
// xfer argument slot for the loop counters, cl gives it to the target id), and
// the record push_back is called through its HLod-spelled placeholder row.
// The prototype vector push_back (0x004DFCB0) needs a fold-proof pin.
// stlport
#include <vector>
#include "ascii_string.h"

struct Coord3D
{
	float x, y, z;
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

class TeamPrototype
{
public:
	unsigned int getID() const { return m_id; }
private:
	unsigned char m_pad[0xC];
	unsigned int m_id;					// +0x0C
};

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototypeByID(unsigned int id);	// 0x0039F72C
};
extern TeamFactory *TheTeamFactory;

class Player
{
public:
	int getPlayerIndex() const { return m_index; }
private:
	unsigned char m_pad[0x54];
	int m_index;						// +0x54
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);			// 0x002A7A29
};
extern PlayerList *ThePlayerList;

class Rva002A8F24
{
public:
	void *rva002A8B73(void *player, int id);		// 0x002A8B73
};
extern Rva002A8F24 *g_00DFEEF8;

extern int g_00E044AC;

// The tactic's 0x14-byte team record (rowed ctor and xfer under this name).
class Rva004ECDC8
{
public:
	Rva004ECDC8(unsigned int v);				// 0x004ECDA7
	void rva004ECDC8(Xfer *xfer);				// 0x004ECDC8
private:
	unsigned char m_bytes[0x14];
};

// The record vector's push_back is rowed under this placeholder spelling.
class HLodClass
{
public:
	class ModelNodeClass;
};
class Rva004ED471
{
public:
	void rva004ED69B(const HLodClass::ModelNodeClass *value);	// 0x004ED69B
};

struct Rva004EDA8CTeams
{
	unsigned int size() const { return m_end - m_begin; }
	Rva004ECDC8 *m_begin;
	Rva004ECDC8 *m_end;
	Rva004ECDC8 *m_cap;
};

struct Rva004EDA8CTarget
{
	unsigned char m_pad[0x38];
	unsigned int m_id;					// +0x38
};

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, void *unused);
	virtual void v4();
	virtual void xfer(Xfer *xfer);

private:
	std::vector<TeamPrototype *> m_protos;			// +0x04
	bool m_10;						// +0x10
	Rva004EDA8CTeams m_teams;				// +0x14
	Rva004EDA8CTarget *m_target;				// +0x20
	Player *m_player;					// +0x24
	bool m_ended;						// +0x28
	AsciiString m_name;					// +0x2C
	unsigned int m_30;					// +0x30
	bool m_34;						// +0x34
	Coord3D m_38;						// +0x38
	Coord3D m_44;						// +0x44
	bool m_50;						// +0x50
	bool m_51;						// +0x51
	unsigned int m_54;					// +0x54
};

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
			unsigned int id = (*it)->getID();
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
		Rva004ECDC8 *end = m_teams.m_end;
		for (Rva004ECDC8 *rec = m_teams.m_begin; rec != end; ++rec)
			rec->rva004ECDC8(xfer);
	}
	else if (xfer->isLoading())
	{
		for (unsigned int i = 0; i < teamCount; ++i)
		{
			Rva004ECDC8 rec(0);
			rec.rva004ECDC8(xfer);
			((Rva004ED471 *)&m_teams)->rva004ED69B((const HLodClass::ModelNodeClass *)&rec);
		}
	}

	int playerIndex = (xfer->isSaving() && m_player) ? m_player->getPlayerIndex() : -1;
	xfer->xferInt(&playerIndex);
	if (xfer->isLoading() && playerIndex != -1)
		m_player = ThePlayerList->getNthPlayer(playerIndex);

	unsigned int targetID = m_target ? m_target->m_id : (unsigned int)-1;
	xfer->xferUnsignedInt(&targetID);
	if (xfer->isLoading() && targetID != (unsigned int)-1)
		m_target = (Rva004EDA8CTarget *)g_00DFEEF8->rva002A8B73(m_player, targetID);

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
