// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002E02F0@Rva002E02F0@@QAEXHPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z, retail 0x002E02F0 107B.
// Clear Science vector then refill from hashtable at +0x10 gated by Entry::Check.
// Evidence: erase 0x00532803 reserve 0x002A1410 begin 0x00427195 Check pin 0x002DFA43
// push_back 0x002E01C6 inc 0x0041E832; callers 0x002E3548 0x0050302C 0x005E9028; ret 8.
#include <vector>
#include <hash_map>

enum ScienceType
{
	SCIENCE_NONE = 0
};

class GameWindow;
class WindowVideo;

class WindowVideoManager
{
public:
	typedef const GameWindow *ConstGameWindowPtr;
	struct hashConstGameWindowPtr
	{
		size_t operator()(ConstGameWindowPtr const &) const;
	};
};

typedef _STL::hash_map<const GameWindow *, WindowVideo *, WindowVideoManager::hashConstGameWindowPtr, _STL::equal_to<const GameWindow *> > WindowVideoMap;

class Rva0059E647Entry
{
public:
	bool Check(int);
};

struct Rva002E02F0IterHelper
{
	void *m_current;
	void *m_owner;
};

class Rva002E02F0
{
public:
	void rva002E02F0(int arg1, _STL::vector<ScienceType> *vec);
	void rva002E0298(_STL::vector<ScienceType> *vec);
private:
	char m_pad[0x10];
	WindowVideoMap m_map;
};

void Rva002E02F0::rva002E02F0(int arg1, _STL::vector<ScienceType> *vec)
{
	vec->erase(vec->begin(), vec->end());
	if (arg1 == 0)
		return;
	vec->reserve(m_map.size());
	for (WindowVideoMap::iterator it = m_map.begin(); ((Rva002E02F0IterHelper *)&it)->m_current != 0; ++it)
	{
		if (((Rva0059E647Entry *)&it->second)->Check(arg1))
			vec->push_back((ScienceType)(int)it->first);
	}
}

// Retail 0x002E0298..0x002E02F0. The adjacent matched method establishes
// the table at +0x10 and the existing vector ABI. This body exports every
// node key, without the sibling's predicate; original application types unknown.
void Rva002E02F0::rva002E0298(_STL::vector<ScienceType> *vec)
{
    vec->erase(vec->begin(), vec->end());
    vec->reserve(m_map.size());
    for (WindowVideoMap::iterator it = m_map.begin(); ((Rva002E02F0IterHelper *)&it)->m_current != 0; ++it)
    {
        ScienceType key = (ScienceType)(int)it->first;
        vec->push_back(key);
    }
}
