// cl: /MD
// ?rva004D6C9C@Rva004D6C9C@@QAEXW4ScienceType@@@Z @0x004D6C9C (16B):
// Frameless vector<ScienceType>::push_back wrapper, member at +0x04.
// Retail lea eax,[esp+4]; push eax; add ecx,4; call push_back @0x002E01C6;
// ret 4. Single caller 0x002ACCA3 loops a ScienceType vector and pushes each
// element into the +0x730 object. Honest-address name: owner unproven.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
	T *erase(T *first, T *last);

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class Team;
class Object;
template<class OBJCLASS> class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_state[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Object
{
public:
	char m_pad00[0x74];
	ScienceType m_science74;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class Rva004D6C9C
{
public:
	void rva004D6C9C(ScienceType science);
	void rva004D6D95(Team *team, bool clearAll);

private:
	char m_pad04[4];
	_STL::vector<ScienceType> m_vec;
};

void Rva004D6C9C::rva004D6C9C(ScienceType science)
{
	m_vec.push_back(science);
}

// ?rva004D6D95@Rva004D6C9C@@QAEXPAVTeam@@_N@Z @0x004D6D95 94B
// Evidence: vector<ScienceType> at +4 same as rva004D6C9C; erase range plus team iteration plus push_back of Object+0x74.
// Caller at 0x00350459.
void Rva004D6C9C::rva004D6D95(Team *team, bool clearAll)
{
	if (!team)
		return;
	if (clearAll) {
		_STL::vector<ScienceType> *vec = &m_vec;
		vec->erase(vec->m_start, vec->m_finish);
	}
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	while (!iter.done()) {
		Object *object = iter.cur();
		ScienceType science = object->m_science74;
		m_vec.push_back(science);
		iter.advance();
	}
}
