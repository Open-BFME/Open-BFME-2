// cl: /MD
//
// ?xfer@AITacticSiege@@UAEXPAVXfer@@@Z, retail 0x005DC903, 56 bytes.
// Slot 5 (offset 0x14) of vtable 0x00876808 (class of ??1Rva005DC87B rowed
// at 0x005DC87B in Rva005DC73CDerived.cpp). Version(1,1) via Xfer slot 0x28
// then base ?xfer@AITactic@@UAEXPAVXfer@@@Z at 0x004EDA8C then
// XferObjectID at this+0x58. Evidence: ctor 0x005DC85F zeroes dword +0x58,
// callers 0x005A9C13 0x005A9D11 call this from tactic xfers, base pin and
// XferObjectID row 0x003060B2. Layout from Rva005A9ACDTactic.cpp
// (AITacticSiege over AITacticOffensive over AITactic, int at +0x58).

class Xfer
{
public:
	class Version;
	virtual ~Xfer();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual Xfer &operator==(Version &value);
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	OBJECTID_INVALID = -1
};

void XferObjectID(Xfer *xfer, enum ObjectID *objectID);

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, void *unused);
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	char m_pad04[0x10 - 4];
	bool m_running; // +0x10
	char m_pad11[0x20 - 0x11];
	void *m_record; // +0x20
	void *m_owner; // +0x24
	char m_pad28[0x58 - 0x28];
};

class Object;

class GameLogic
{
public:
	class Object *findObjectByID(enum ObjectID id);
};

extern GameLogic *TheGameLogic;

class AITacticSiege : public AITacticOffensive
{
public:
	virtual ~AITacticSiege();
	virtual void xfer(Xfer *xfer);
	class Object *rva005DCAE5();
	enum ObjectID m_58; // +0x58
};

void AITacticSiege::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	AITactic::xfer(xfer);
	XferObjectID(xfer, &m_58);
}

// ?rva005DCAE5@AITacticSiege@@QAEPAVObject@@XZ, retail 0x005DCAE5, 15 bytes.
// Object at this+0x58 via TheGameLogic->findObjectByID; callers 0x005A9B2E
// 0x005A9DED 0x005DCAF4, callee row 0x00049DC5.
Object *AITacticSiege::rva005DCAE5()
{
	return TheGameLogic->findObjectByID(m_58);
}
