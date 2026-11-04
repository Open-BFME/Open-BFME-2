// ?clearUnseenMaps@MapCache@@AAE_NVAsciiString@@@Z, retail 0x0030469E, 166
// bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/MapCacheClearUnseenMaps.cpp
// (reference/open-bfme-1). The donor body does not place at BFME 1's flags;
// compiled /Os it is byte-identical to retail once relocations are masked
// (unique hit on unclaimed .text). Only the placed body is defined here.
//
// MapCache::loadUserMaps calls this standalone entry after rebuilding its
// per-directory seen set. The by-value directory parameter, m_seen at +0x0c,
// and the map erase traversal reproduce the original MapUtil.cpp algorithm.
//
// AsciiString comes from the shared compatibility shim, not a TU-local class,
// per the class gate. Its members are exactly the workers retail calls here:
// the copy constructor at 0x000365F0, startsWithNoCase at 0x00036000 and the
// release worker at 0x00036410. str() is inline in both, returning m_data + 8
// or "" for a null buffer. The donor's own operator< is dropped: the shared
// string_base.h already defines it, and redefining collides.
//
// 1 callee pin read off retail's REL32 displacement: the map's key erase at
// 0x00304384. It is the two-level std::map erase (a lookup helper at
// 0x005C9F41, then the tree _M_erase at 0x000D20DB), not the raw tree _M_erase
// the other AsciiString-tree rows in the ledger name.
// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <string.h>

#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@U?$_Sele:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; class MapMetaData;
namespace _STL { template <> void _Rb_tree<AsciiString,pair<AsciiString const ,MapMetaData>,_Select1st<pair<AsciiString const ,MapMetaData> >,less<AsciiString>,allocator<pair<AsciiString const ,MapMetaData> > >::_M_erase(_Rb_tree_node<pair<AsciiString const ,MapMetaData> > *); }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

typedef bool Bool;
typedef int Int;

#include "unicode_string.h"
#include "../../Include/GameClient/MapMetaData.h"

extern "C" void _free(void *);

// Retail releases metadata nodes through the game allocator's free wrapper.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_Rb_tree_node<pair<const AsciiString, MapMetaData> > >::deallocate(
    _Rb_tree_node<pair<const AsciiString, MapMetaData> > *node, unsigned int) const
{
    if (node) _free(node);
}

template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_Rb_tree_node<pair<const AsciiString, MapMetaData> > *,
    _Rb_tree_node<pair<const AsciiString, MapMetaData> >,
    allocator<_Rb_tree_node<pair<const AsciiString, MapMetaData> > > >::deallocate(
    _Rb_tree_node<pair<const AsciiString, MapMetaData> > *node, unsigned int count)
{
    allocator<_Rb_tree_node<pair<const AsciiString, MapMetaData> > >::deallocate(node, count);
}
}

#include "../../Include/GameClient/MapCache.h"

// ?clearUnseenMaps@MapCache@@AAE_NVAsciiString@@@Z
Bool MapCache::clearUnseenMaps(AsciiString dirName)
{
	((StringBase<char> &)(dirName)).toLower();
	Bool erasedSomething = false;
	std::map<AsciiString, Bool>::iterator it = m_seen.begin();
	while (it != m_seen.end())
	{
		AsciiString mapName = it->first;
		if (!it->second && mapName.startsWithNoCase(dirName.str()))
		{
			erase(mapName);
			erasedSomething = true;
		}
		++it;
	}
	return erasedSomething;
}
