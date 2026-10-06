// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva002BFDAE@Rva002BFDAE@@QAEPAXPAX@Z @0x002BFDAE 56B
// Manual WindowVideoMap walk: begin on map at +0xac, return entry whose
// WindowVideo+0xc field equals the query, else NULL. Evidence: retail calls
// hashtable<GameWindow*,WindowVideo*>::begin at 0x427195 then Rva000411084::next
// at 0x411084, with the [node+8]->[+0xc] compare pattern of it->second->field.
#include <hash_map>

class GameWindow;
class WindowVideo
{
public:
	char m_pad[0x0c];
	void *m_match;
};

class WindowVideoManager
{
public:
	typedef const GameWindow *ConstGameWindowPtr;
	struct hashConstGameWindowPtr
	{
		size_t operator()(ConstGameWindowPtr p) const
		{
			return (size_t)p;
		}
	};
};

typedef std::hash_map<const GameWindow *, WindowVideo *, WindowVideoManager::hashConstGameWindowPtr, std::equal_to<const GameWindow *> > WindowVideoMap;

class Rva000411084
{
public:
	void *next();
	void *m_current;
	void *m_owner;
};

class Rva002BFDAE
{
public:
	void *rva002BFDAE(void *key);
private:
	char m_pad[0xac];
	WindowVideoMap m_map;
};

void *Rva002BFDAE::rva002BFDAE(void *key)
{
	WindowVideoMap::iterator it = m_map.begin();
	while (((Rva000411084 *)&it)->m_current != 0)
	{
		WindowVideo *winVid = it->second;
		if (winVid->m_match == key)
			return winVid;
		((Rva000411084 *)&it)->next();
	}
	return NULL;
}
