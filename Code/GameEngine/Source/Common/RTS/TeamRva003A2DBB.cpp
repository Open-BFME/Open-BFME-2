// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003A2DBB@Team@@QAEXM@Z @0x003A2DBB 258B.
// Target facts: the one REL32 caller is the rowed Team::rva003A3736
// (0x003A3736), which reads the +0x120 total this body caches and its
// +0x124 deadline. The body takes the team centre (0x0039E5B9), uses
// the first member as the reference object, queries the partition within
// the range through the linked filter chain (relationship 1, alive, the
// 0x002611BF filter on the reference object), sums each hit's ThingTemplate
// +0x51C float into +0x120 and re-arms the 5000 ms deadline through the
// rowed leaf 0x0039D8D3 (declared nothrow: no unwind state spans it). The
// name is address-derived. Shape: the member iterator lives in an inner
// scope so its slot is reused by the later filter temporaries, as retail.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../PartitionRangeQueryCallView.h"

class Object;

#include "../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

extern PartitionManager *ThePartitionManager;

#include "../../../Include/Common/ThingTemplate.h"

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x68 - 0x08];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = ((*m_cur).*(m_getNextFunc))(); }
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

#include "../../../Include/Common/TeamBFME2.h"

inline DLINK_ITERATOR<Object> Team::iterate_TeamMemberList() const
{
	return DLINK_ITERATOR<Object>(m_dlinkhead_TeamMemberList, &Object::dlink_next_TeamMemberList);
}

void Team::rva003A2DBB(float range)
{
	Coord3D center;
	rva0039E5B9(&center);
	Object *leader;
	{
		DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
		leader = iter.cur();
	}
	if (!leader)
		return;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&center, range, 0,
		Rva00260EB1Filter(leader, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(leader))), 0);
	float total = 0.0f;
	Object *obj;
	while ((obj = hits.next()) != 0)
		total += (obj->getTemplate()->m_threatLevel);
	m_120 = total;
	rva0039D8D3(5000);
}
