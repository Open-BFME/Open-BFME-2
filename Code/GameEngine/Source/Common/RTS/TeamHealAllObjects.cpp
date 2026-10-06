// cl: /DNDEBUG /MD
//
// ?healAllObjects@Team@@QAEXXZ @0x0039DCE9 (41B).
// Team::healAllObjects(): walks the member list through the pinned
// iterate_TeamMemberList at 0x263864 and the pinned DLINK advance at
// 0x263526, calling the rowed Object::healCompletely at 0x0028FF9E on each
// entry. Retail shape is iterator output at ebp-0x18 plus heal plus advance
// plus null test. BFME1 donor
// reference/open-bfme-1/Code/GameEngine/Source/Common/RTS/Team.cpp:2363
// proves the name and loop; BFME2 deltas are the 24-byte iterator output
// and the pinned/rowed callees above. Caller at 0x0039ED84 heals each team
// in a list.

typedef int Bool;

class Object
{
public:
	void healCompletely();
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void healAllObjects();
};

void Team::healAllObjects()
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		iter.cur()->healCompletely();
	}
}
