// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva00212728@Rva00212728@@QAEPAXPAX@Z, retail 0x00212728, 57 bytes.
// Reverse lookup over WindowVideoMap at this+0x218: begin via rowed
// hashtable 0x00427195 then prefix ++ via rowed 0x0041E832, return entry
// whose second equals the query else -1. Callers 0x005769A7 0x00576A54
// in 0x00576946 and 0x005777EC in 0x005777A0. Flags from Rva002BFDAEFind.
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

class GameWindow;
class WindowVideo;

#include "../../../Include/GameClient/WindowVideoManagerClass.h"

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
// bfme link decl-only begin
namespace _STL { template <> unsigned int hashtable<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::_M_bkt_num_key(GameWindow const * const &) const; }
namespace _STL { template <> unsigned int hashtable<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::_M_bkt_num_key(GameWindow const * const &,unsigned int) const; }
namespace _STL { template <> _STL::_Hashtable_node<_STL::pair<GameWindow const * const,WindowVideo *> > * _Hashtable_iterator<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::_M_skip_to_next(); }
namespace _STL { template <> _STL::_Ht_iterator<_STL::pair<GameWindow const * const,WindowVideo *>,_STL::_Nonconst_traits<_STL::pair<GameWindow const * const,WindowVideo *> >,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > > hashtable<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::begin(); }
// bfme link decl-only end
