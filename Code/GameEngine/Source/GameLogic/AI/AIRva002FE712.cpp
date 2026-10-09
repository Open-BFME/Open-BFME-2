// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?destroyGroup@AI@@QAEXPAVAIGroup@@@Z @ 0x002FE712 89B
// AI group destroy: find in +0x14 list, erase, deleteInstance(0)+delete.
// Evidence: TheAI at 0x00DFF0F8 callers 0x0036CF62 and 0x0023C99D pass AIGroup*,
// list at +0x14 matches createGroup push_back<int> at 0x002FEC4B, donor
// BFME1 ai.cpp destroyGroup find+erase+deleteInstance shape.
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}

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

// ?find@Rva002FE76BListPrefix@@QAEPAVRva001DB09DDwordField@@H@Z
// Retail 0x002FE76B..0x002FE799 (46 bytes): sentinel at receiver+0x14;
// nodes have next at +0 and a payload pointer at +8. The rowed 0x001DB09D
// getter reads the comparison key at payload+0x10. The success path jumps
// back to the shared pop/ret 4 within this proven boundary.
// Primary source lead: GeneralsMD AI.cpp AI::findGroup's list/key search;
// neighbouring AI::destroyGroup confirms the subsystem's +0x14 list.
// Original receiver/payload names and full layouts remain unproven.
class Rva001DB09DDwordField
{
public:
    int get() const;
};

struct Rva002FE76BNode
{
    Rva002FE76BNode *next;
    void *unmodelled04;
    Rva001DB09DDwordField *value;
};

class Rva002FE76BListPrefix
{
public:
    Rva001DB09DDwordField *find(int key);

private:
    char prefix00[0x14];
    Rva002FE76BNode *head;
};

Rva001DB09DDwordField *Rva002FE76BListPrefix::find(int key)
{
    for (Rva002FE76BNode *node = head->next; node != head; node = node->next)
        if (node->value->get() == key)
            return node->value;
    return 0;
}
