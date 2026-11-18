// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/inputs/reference/shims/peerdefs -Ireference/open-bfme-1/inputs/reference/shims/stringinline -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork/GameSpy
// stlport

// The retail body at 0x006357D0 implements GroupRoomMap::operator[].
// GameSpyInfo::addGroupRoom calls this map through m_groupRooms[room.m_groupID].
// The existing insert_unique body at 0x00633BB0 and the 0x20-byte
// GameSpyGroupRoom layout identify this STLport instantiation.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include "StringInline.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

#include "../../../Include/Common/ScalarTypes.h"

struct AsciiUnicodePair
{
	AsciiString m_name;
	UnicodeString m_translatedName;
	Int m_groupID;
	Int m_numWaiting;
	Int m_maxWaiting;
	Int m_numGames;
	Int m_numPlaying;
	Int m_roomType;
	AsciiUnicodePair(const AsciiUnicodePair &other);
	__declspec(dllimport) __forceinline ~AsciiUnicodePair() {}
};

class GameSpyGroupRoom : public AsciiUnicodePair
{
public:
	GameSpyGroupRoom();		// 0x0038226B
	__declspec(dllimport) __forceinline GameSpyGroupRoom(const GameSpyGroupRoom &other) : AsciiUnicodePair(other) {}
	GameSpyGroupRoom &operator=(const GameSpyGroupRoom &other);	// 0x00381E56
};
typedef std::map<Int, GameSpyGroupRoom> GroupRoomMap;

// PeerDefs.cpp supplies these tree and value copies.
namespace _STL {
typedef pair<const int, GameSpyGroupRoom> GroupRoomValue;
typedef _Rb_tree<int, GroupRoomValue, _Select1st<GroupRoomValue>, less<int>, allocator<GroupRoomValue> > GroupRoomTree;
template <> GroupRoomValue::pair(const GroupRoomValue &);
template <> _Rb_tree_node<GroupRoomValue> *GroupRoomTree::_M_create_node(const GroupRoomValue &);
}

template GameSpyGroupRoom &GroupRoomMap::operator[]( const Int &key );
