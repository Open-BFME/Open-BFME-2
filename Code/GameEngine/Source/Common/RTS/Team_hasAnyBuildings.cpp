// cl: /DNDEBUG /MD
// ?hasAnyBuildings@Team@@QAE_NVBfmeFixedStorage0004543D@@0@Z 0x0039DF1C 107 Team member kind filter
// Retail walks via rowed iterate 0x263864 and advance 0x263526, skips dead
// Object+0x438 bit0 and status Object+0x94 bit0, template +0x108 sign and
// 0x2000000 plus +0x11A bit 0x10, then rowed isKindOfMulti 0x0030AD7D on the
// two 28-byte value args. Caller at 0x0039EF22. Same flags as neighbours.
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

// The by-value kind filter is the 28-byte storage the ledger names after
// its copy constructor 0x0004543D, which every caller copies it through.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
	unsigned int w[7]; // +0x00
};
typedef BfmeFixedStorage0004543D Rva0039DF1CFilter;

template<int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
};

struct ThingTemplate
{
	unsigned char m_pad108[0x108];
	int m_kind0;
	unsigned char m_pad10C[0x11A - 0x10C];
	unsigned char m_kindByte11a;
};

class Thing
{
public:
	bool isKindOfMulti(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear) const;
};

class Object
{
public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
	unsigned char m_pad8[0x94 - 0x08];
	unsigned char m_status94;
	unsigned char m_pad95[0x438 - 0x95];
	unsigned char m_dead;
};

#include "../../../Include/Common/TeamBFME2.h"

bool Team::hasAnyBuildings(Rva0039DF1CFilter f1, Rva0039DF1CFilter f2)
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		if ((cur->m_dead & 1) != 0)
			continue;
		if ((cur->m_status94 & 1) != 0)
			continue;
		ThingTemplate *thingTemplate = cur->m_template;
		if ((thingTemplate->m_kind0 & 0x80) != 0)
			continue;
		if ((thingTemplate->m_kind0 & 0x2000000) != 0)
			continue;
		if ((thingTemplate->m_kindByte11a & 0x10) != 0)
			continue;
		const BitFlags<116> &mustBeSet = *(const BitFlags<116> *)(const void *)&f1;
		const BitFlags<116> &mustBeClear = *(const BitFlags<116> *)(const void *)&f2;
		if (((const Thing *)cur)->isKindOfMulti(mustBeSet, mustBeClear))
			return true;
	}
	return false;
}
