// cl: /DNDEBUG /MD
//
// ?rva0039DD12@Team@@QBEHP6AHPAVObject@@PAX@Z1@Z @0x0039DD12 (57B).
// Team predicate all-of: returns 1 only when the callback returns nonzero
// for every member, 0 on the first zero. Retail walks via the rowed
// iterate_TeamMemberList at 0x263864 and advance at 0x263526, calling the
// __cdecl predicate with (cur userdata) through the function pointer at
// +8. Callers at 0x0039EDBC and 0x003C1EB9 pass Team ECX with predicate and
// userdata args.

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

typedef int (__cdecl *TeamPredicate)(Object *obj, void *userData);

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	int rva0039DD12(TeamPredicate pred, void *userData) const;
};

int Team::rva0039DD12(TeamPredicate pred, void *userData) const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		if (!pred(iter.cur(), userData))
			return 0;
	}
	return 1;
}
