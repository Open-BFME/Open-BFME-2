// cl: /DNDEBUG /MD
// ?rva003A2D53@Team@@QAEXHPAVObject@@@Z 104B @0x003A2D53: team map register plus filtered member notify.
// Evidence: this plus0x11c map plus findSlot row 0x0041F4E5 plus iterate row 0x00263864 plus advance pin 0x00263526 plus rva00298C0B row plus Object plus0x438 plus0x94 plus0x250 filters. Caller at 0x003C443F.
class Object;
class Team;

class Object
{
public:
	unsigned char m_pad00[0x94];
	unsigned char m_flag94;
	unsigned char m_pad95[0x250 - 0x95];
	void *m_inner250;
	unsigned char m_pad254[0x438 - 0x254];
	unsigned char m_flag438;
};

class ObjectLookupMap
{
public:
	Object **findSlot(int *key);
};

struct MapWrapper
{
	char m_pad[4];
	ObjectLookupMap m_map;
};

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

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva003A2D53(int key, Object *val);
private:
	char m_pad00[0x11c];
	MapWrapper *m_11c;
};

class Rva00298C0B
{
public:
	void rva00298C0B(Team *t);
};

void Team::rva003A2D53(int key, Object *val)
{
	if (key == -1)
		return;
	Object **slot = m_11c->m_map.findSlot(&key);
	*slot = val;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		if ((cur->m_flag438 & 1) != 0)
			continue;
		if ((cur->m_flag94 & 1) != 0)
			continue;
		if (cur->m_inner250 == 0)
			continue;
		((Rva00298C0B *)cur)->rva00298C0B(this);
	}
}
