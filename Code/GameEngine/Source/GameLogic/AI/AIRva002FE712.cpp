// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?destroyGroup@AI@@QAEXPAVAIGroup@@@Z @ 0x002FE712 89B
// AI group destroy: find in +0x14 list, erase, deleteInstance(0)+delete.
// Evidence: TheAI at 0x00DFF0F8 callers 0x0036CF62 and 0x0023C99D pass AIGroup*,
// list at +0x14 matches createGroup push_back<int> at 0x002FEC4B, donor
// BFME1 ai.cpp destroyGroup find+erase+deleteInstance shape.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <algorithm>

enum ObjectID
{
	INVALID_ID = 0
};

class AIGroup
{
public:
	virtual void *deleteInstance(int flags);
};

class AI
{
public:
	void destroyGroup(AIGroup *group);

private:
	char m_pad[0x14];
	_STL::list<ObjectID> m_groupList;
};

void AI::destroyGroup(AIGroup *group)
{
	_STL::list<ObjectID>::iterator it = _STL::find(m_groupList.begin(), m_groupList.end(), *(ObjectID *)&group);
	if (it == m_groupList.end())
		return;
	((_STL::list<int> *)&m_groupList)->erase(*(_STL::list<int>::iterator *)&it);
	void *mem = 0;
	if (group)
		mem = group->deleteInstance(0);
	::operator delete(mem);
}
