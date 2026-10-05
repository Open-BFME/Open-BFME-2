// ?rva0039DC05@Team@@QBEHH_N0@Z
// partial score=0.96 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?rva0039DC05@Team@@QBEHH_N0@Z @0x0039DC05 (94B): counts the members whose
// template passes the rowed kind test 0x000456AC for the given kind,
// skipping effectively dead members (Object +0x438 bit 0) when asked and
// members with object status 2 (Zero Hour's OBJECT_STATUS_UNDER_CONSTRUCTION
// slot, via the rowed Object::testStatus) when asked - Zero Hour's
// countObjectsByThingTemplate filters applied to a kind instead of a
// template list. Same member walk as TeamRva0039DDC2.cpp. Retail tests the
// kind test's AL, so it is declared bool here (alias pin beside the row's
// int-returning name). Caller 0x003E5E6A.

class Object;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

class ThingTemplate
{
public:
	bool rva000456AC(int kind) const;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	unsigned char m_pad0[4];
	ThingTemplate *m_template; // +0x04
	unsigned char m_pad8[0x438 - 8];
	unsigned char m_privateStatus; // +0x438
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	int rva0039DC05(int kind, bool ignoreDead, bool ignoreUnderConstruction) const;
};

int Team::rva0039DC05(int kind, bool ignoreDead, bool ignoreUnderConstruction) const
{
	int count = 0;
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	for (Object *obj; (obj = iter.cur()) != 0; iter.advance())
	{
		if (ignoreDead && obj->isEffectivelyDead())
			continue;
		if (ignoreUnderConstruction && obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
			continue;
		if (!obj->getTemplate()->rva000456AC(kind))
			continue;
		++count;
	}
	return count;
}
