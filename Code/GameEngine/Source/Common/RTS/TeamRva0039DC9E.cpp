// cl: /DNDEBUG /MD
// ?rva0039DC9E@Team@@QBEHV?$BitFlags@$0HE@@@0@Z @0x0039DC9E 75B.
// Team::rva0039DC9E(): counts members whose template flags pass testSetAndClear.
// Evidence: callees rowed 0x00263864 0x0030A146 0x00263526; callers at 0x0039ED4B 0x003BEA80 0x003BEB6F 0x003BEC42 0x004ED617; same 24-byte iterator as siblings.
template <int N>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const;
private:
	unsigned m_words[7];
};

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

struct ThingTemplate
{
	unsigned char m_pad[0x108];
	BitFlags<116> m_flags;
};

class Object
{
public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	int rva0039DC9E(BitFlags<116> mustBeSet, BitFlags<116> mustBeClear) const;
};

int Team::rva0039DC9E(BitFlags<116> mustBeSet, BitFlags<116> mustBeClear) const
{
	int count = 0;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		ThingTemplate *tmpl = cur->m_template;
		if (tmpl == 0)
			continue;
		if (!tmpl->m_flags.testSetAndClear(mustBeSet, mustBeClear))
			continue;
		++count;
	}
	return count;
}
