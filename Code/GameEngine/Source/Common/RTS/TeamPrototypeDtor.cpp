// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /GX
//
// Zero Hour Team.cpp TeamPrototype teardown:
//   ?deleteTeamCallback@@YAXPAVTeam@@@Z   retail 0x003A33A7, 38 bytes
//   ??1TeamPrototype@@MAE@XZ              retail 0x003A33CD, 223 bytes
//
// Identity: the rowed ??_GTeamPrototype 0x003A38B1 (slot 0 of vtable
// 0x00C1AE94, unique TeamPrototype name getter) calls 0x003A33CD, which
// re-stores that vtable and hands 0x003A33A7 (pushed as a function
// pointer) to the rowed instance-list drain 0x0039D4FB, as Zero Hour's
// destructor hands deleteTeamCallback to removeAll_TeamInstanceList. The
// callback calls TheTeamFactory (0x00E028BC) member 0x003A3048, whose body
// is Zero Hour's teamAboutToBeDeleted (prototype-map walk, then
// ThePlayerList), and frees the team in BFME 2's deleteInstance shape
// (virtual slot 0 with 0, then operator delete).
//
// BFME 2 deltas read from the target: the owning-player and factory
// removals live in an out-of-line member 0x003A0CD1 (pinned under an
// address name); the generic-script table has 32 entries (+0x2C) followed
// by 32 AsciiStrings (+0xAC, torn down through the eh vector destructor
// with the rowed AsciiString dtor 0x0048BA39); member teardown order
// (+0x318 string, +0x12C TeamTemplateInfo, the string array, +0x20,
// +0x14, +0x10 strings) gives the retail EH states 5..0, and the inlined
// Snapshot base restores 0x00BBB554.

template <typename T> struct BfmeStringData;

#include "ascii_string.h"
// Slot 2 is the class-name getter, as in TeamPrototypeCtor.cpp.
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

class Team
{
public:
	virtual void *deleteInstance(int flags);
};

class Script
{
public:
	Script *duplicate() const;
	void *getAction() const { return m_action; }
	bool isEasy() const { return m_easy; }
	bool isNormal() const { return m_normal; }
	bool isHard() const { return m_hard; }
	int getDelayEvalSeconds() const { return m_delayEvaluationSeconds; }
	unsigned int getFrameToEvaluate() const { return m_frameToEvaluate; }
	void setFrameToEvaluate(unsigned int frame) { m_frameToEvaluate = frame; }
	bool isSequential() const { return m_sequential; }
	int getLoopCount() const { return m_loopCount; }
	int getDelayEvaluationSeconds() const { return m_delayEvaluationSeconds; }
	bool isOneShot() const { return m_oneShot; }
	bool isActiveRV() const { return m_isActive; }
	virtual void *deleteInstance(int flags);
	char m_pad04[0xC];
private:
	bool m_sequential; // +0x10 +0x10
	char m_pad11[0x3];
	int m_loopCount; // +0x14 +0x14
	char m_pad18[0x8];
	int m_delayEvaluationSeconds; // +0x20 +0x20
	char m_pad24[0x5];
	bool m_oneShot; // +0x29 +0x29
	char m_pad2A[0x1];
	bool m_easy; // +0x2B +0x2B
	bool m_normal; // +0x2C +0x2C
	bool m_hard; // +0x2D +0x2D
	char m_pad2E[0x6];
	void *m_action; // +0x34 +0x34
	char m_pad38[0x4];
	unsigned int m_frameToEvaluate; // +0x3C +0x3C
	bool m_isActive; // +0x40 +0x40
	char m_pad41[0x3];
};

class TeamFactory
{
public:
	void teamAboutToBeDeleted(Team *team);
};

extern TeamFactory *TheTeamFactory;

class TeamTemplateInfo
{
public:
	virtual ~TeamTemplateInfo();

private:
	unsigned char m_data[0x318 - 0x12C - 4];
};

enum { MAX_GENERIC_SCRIPTS = 32 };

class TeamPrototype : public Snapshot
{
public:
	void removeAll_TeamInstanceList(void (*deleteFunc)(Team *));
	void rva003A0CD1();

protected:
	virtual ~TeamPrototype();
	// The rest of vtable 0x00C1AE94 (TeamPrototypeCtor.cpp's rows), declared so
	// this TU's ??_7TeamPrototype is the same four-slot table.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);

private:
	TeamFactory *m_factory; // +0x04
	void *m_owningPlayer; // +0x08
	unsigned int m_id; // +0x0C
	AsciiString m_name; // +0x10
	AsciiString m_14; // +0x14
	int m_flags; // +0x18
	int m_1C; // +0x1C
	AsciiString m_20; // +0x20
	Script *m_productionConditionScript; // +0x24
	bool m_retrievedGenericScripts; // +0x28
	Script *m_genericScriptsToRun[MAX_GENERIC_SCRIPTS]; // +0x2C
	AsciiString m_genericScriptNames[MAX_GENERIC_SCRIPTS]; // +0xAC
	TeamTemplateInfo m_teamTemplate; // +0x12C
	AsciiString m_attackPriorityName; // +0x318
};

static void deleteTeamCallback(Team *team)
{
	if (team)
	{
		TheTeamFactory->teamAboutToBeDeleted(team);
		::operator delete(team->deleteInstance(0));
	}
}

TeamPrototype::~TeamPrototype()
{
	removeAll_TeamInstanceList(deleteTeamCallback);

	rva003A0CD1();

	if (m_productionConditionScript)
	{
		::operator delete(m_productionConditionScript->deleteInstance(0));
	}
	m_productionConditionScript = 0;

	for (int i = 0; i < MAX_GENERIC_SCRIPTS; ++i)
	{
		if (m_genericScriptsToRun[i])
		{
			::operator delete(m_genericScriptsToRun[i]->deleteInstance(0));
			m_genericScriptsToRun[i] = 0;
		}
	}
}

