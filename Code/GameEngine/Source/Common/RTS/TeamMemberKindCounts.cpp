extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?rva0039DC05@Team@@QBEHH_N0@Z
// ?rva0039DC05@Team@@QBEHH_N0@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0039DC05@Team@@QBEHH_N0@Z @0x0039DC05 (94B): counts the members whose
// template passes the rowed kind test 0x000456AC for the given kind,
// skipping effectively dead members (Object +0x438 bit 0) when asked and
// members with object status 2 (Zero Hour's OBJECT_STATUS_UNDER_CONSTRUCTION
// slot, via the rowed Object::testStatus) when asked - Zero Hour's
// countObjectsByThingTemplate filters applied to a kind instead of a
// template list. Same member walk as TeamRva0039DDC2.cpp. Retail tests the
// kind test's AL through the bool-returning template query. Caller 0x003E5E6A.

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

typedef char TeamMemberIteratorABI24[(sizeof(DLINK_ITERATOR<Object>)==24)?1:-1];

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

enum KindOfType { KINDOF_INVALID = -1 };

class ThingTemplate
{
public:
	bool isKindOf(KindOfType kind) const;
	bool isEquivalentTo(const ThingTemplate *tt) const;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	bool isEffectivelyDead() const { return (m_dead & 1) != 0; }
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	unsigned char m_pad0[4];
	ThingTemplate *m_template; // +0x04
	unsigned char m_pad8[0x438 - 8];
	unsigned char m_dead; // +0x438
};

#include "../../../Include/Common/TeamBFME2.h"

int Team::rva0039DC05(int kind, bool ignoreDead, bool ignoreUnderConstruction) const
{
	int count = 0;
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	for (Object *obj; (obj = iter.cur()) != 0; iter.advance())
	{
 _ReadWriteBarrier();
		if (ignoreDead && obj->isEffectivelyDead())
			continue;
		if (ignoreUnderConstruction && obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
			continue;
		if (!(unsigned char)obj->getTemplate()->isKindOf((KindOfType)kind))
			continue;
		++count;
	}
	return count;
}
// Target/native facts: whole94B ends at39DC63; direct caller3E5E6A,
// iterator ABI24 and template4/dead438 accesses. The barrier in the loop
// preserves native owner/template/flag load scheduling under O1G7SSE.
// ZH countObjectsByThingTemplate supplies the filter semantics only; the
// original kind-counter method name remains unknown and keeps its RVA.

// ?countObjectsByThingTemplate@Team@@QBEXHPBQBVThingTemplate@@_NPAH1@Z
// Retail 0x0039DB89..0x0039DC05 (124 bytes, RET 0x14), directly before the
// kind counter above; caller 0x0039EC03. Zero Hour's
// Team::countObjectsByThingTemplate: for each member, the first template in
// the list its template is equivalent to (rowed ThingTemplate::isEquivalentTo
// 0x0033BB04) counts it, unless dead or under construction when asked. The
// member walk and barrier are the kind counter's; with them retail keeps the
// member in EDI and its template in EBX.
void Team::countObjectsByThingTemplate(int numTmplates, const ThingTemplate *const *things, bool ignoreDead, int *counts, bool ignoreUnderConstruction) const
{
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	for (Object *obj; (obj = iter.cur()) != 0; iter.advance())
	{
		_ReadWriteBarrier();
		const ThingTemplate *objtmpl = obj->getTemplate();
		for (int i = 0; i < numTmplates; ++i)
		{
			if (!objtmpl->isEquivalentTo(things[i]))
				continue;
			if (ignoreDead && obj->isEffectivelyDead())
				continue;
			if (ignoreUnderConstruction && obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
				continue;
			counts[i] += 1;
			break;
		}
	}
}
