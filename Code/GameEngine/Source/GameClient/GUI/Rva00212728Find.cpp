// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva00212728@Rva00212728@@QAEPAXPAX@Z, retail 0x00212728, 57 bytes.
// Reverse lookup over WindowVideoMap at this+0x218: begin via rowed
// hashtable 0x00427195 then prefix ++ via rowed 0x0041E832, return entry
// whose second equals the query else -1. Callers 0x005769A7 0x00576A54
// in 0x00576946 and 0x005777EC in 0x005777A0. Flags from Rva002BFDAEFind.
#include <hash_map>

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

typedef std::hash_map<const GameWindow *, WindowVideo *, WindowVideoManager::hashConstGameWindowPtr, std::equal_to<const GameWindow *> > WindowVideoMap;

struct Rva00212728IterHelper
{
	void *m_current;
	void *m_owner;
};

class Rva00212728
{
public:
	void *rva00212728(void *key);
private:
	char m_pad[0x218];
	WindowVideoMap m_map;
};

void *Rva00212728::rva00212728(void *key)
{
	WindowVideoMap::iterator it = m_map.begin();
	while (((Rva00212728IterHelper *)&it)->m_current != 0)
	{
		if (key == it->second)
			return (void *)it->first;
		++it;
	}
	return (void *)-1;
}
