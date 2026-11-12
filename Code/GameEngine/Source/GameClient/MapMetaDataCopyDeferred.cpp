// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Ownership split only: copy/assignment retain the known waypoint-tree link
// blockers; native destruction and parsing remain in MapMetaDataCopy.cpp.
// Reference: BFME1 GameClient/MapMetaData_ctor.cpp, MapMetaData_assign.cpp,
// MapMetaData_dtor.cpp and ZH GeneralsMD MapUtil.h; BFME2 has a new word at F4.
// Named BFME2 GUI methods independently prove fields0/4/20/50/F8/FC.
// Retail copy3039E8 is257B and copies this entire256B record member by member.
// Waypoint copy303359 copies the typed tree plus count at C; its tree-copy
// chain3025A5->301F9B->301BBF->3012CE preserves the verified coordinate payload.
// List copy2820DD allocates20B nodes:8B links plus Coord3D; members48/4C
// are the reference supply/tech-position lists. Player copy303374 uses eight
// records of20B, with real copy302CE2 and dtor22D920 callbacks. Their three
// flags/team/map layout also agrees with the matched MPPositionInfo writer.
// Unknown BFME2 wordF4 remains opaque; no extra meaning is inferred.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <map>
#include <set>
#include "unicode_string.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
// bfme link decl-only begin
namespace _STL { template <> _List_node<Coord3D> * list<Coord3D, allocator<Coord3D> >::_M_create_node(Coord3D const &); }
namespace _STL { template <> _Rb_tree_base<pair<AsciiString const, Coord3D>, allocator<pair<AsciiString const, Coord3D> > >::_Rb_tree_base(allocator<pair<AsciiString const, Coord3D> > const &); }
namespace _STL { template <> _Rb_tree_node<AsciiString> * _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_M_copy(_Rb_tree_node<AsciiString> *, _Rb_tree_node<AsciiString> *); }
namespace _STL { template <> _Rb_tree_node<pair<AsciiString const, Coord3D> > * _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::_M_create_node(pair<AsciiString const, Coord3D> const &); }
namespace _STL { template <> _Rb_tree_node<AsciiString> * _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_M_create_node(AsciiString const &); }
namespace _STL { template <> _Rb_tree_node<pair<AsciiString const, Coord3D> > * allocator<_Rb_tree_node<pair<AsciiString const, Coord3D> > >::allocate(unsigned int, void const *) const; }
// Retail's waypoint-tree _M_copy (0x00301F9B, 115B) has no unwind frame: it is
// STLport's structural copy without _STLP_TRY/_STLP_UNWIND. Spell that body so
// this /EHs unit stops emitting a try-wrapped copy the link would keep.
namespace _STL {
typedef _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > > WaypointTree;
// Retail 0x00301F9B is rowed under the TreeHintPayload003012F0 name.
// ?_STL::WaypointTree::_M_copy present-unmatched
template <> inline _Rb_tree_node<pair<AsciiString const, Coord3D> > *
WaypointTree::_M_copy(_Rb_tree_node<pair<AsciiString const, Coord3D> > *__x, _Rb_tree_node<pair<AsciiString const, Coord3D> > *__p)
{
	_Link_type __top = _M_clone_node(__x);
	__top->_M_parent = __p;
	if (__x->_M_right)
		__top->_M_right = _M_copy(_S_right(__x), __top);
	__p = __top;
	__x = _S_left(__x);
	while (__x != 0) {
		_Link_type __y = _M_clone_node(__x);
		__p->_M_left = __y;
		__y->_M_parent = __p;
		if (__x->_M_right)
			__y->_M_right = _M_copy(_S_right(__x), __y);
		__p = __y;
		__x = _S_left(__x);
	}
	return __top;
}
}
// bfme link decl-only end
#include "../../../Libraries/Include/Lib/Region3D.h"
typedef _STL::list<Coord3D> Coord3DList;
// Instantiate the reference coordinate-list copy and its typed helpers.
class WaypointMap : public _STL::map<AsciiString,Coord3D> { int numStartSpots; public: WaypointMap(const WaypointMap &); };
// The copy chain301EF6->301A3E->3012B0->2C552 proves a string-only20B node:
// these faction names form a set, not a map with an unobserved mapped value.
#include "../../Include/Common/PlayerPosition.h"
// Implicit copy emits the real EH array-copy helper: eight20B records.
// Callback302CE2 copies three flags/team/map; callback22D920 destroys map+8.
struct MapPlayers { PlayerPosition items[8]; };
class MapMetaData {
    UnicodeString displayName,description; Region3D extent; int numPlayers;
    unsigned char isMultiplayer,isScenarioMP,isOfficial;
    unsigned int filesize,crc,timestampLo,timestampHi;
    WaypointMap waypoints; Coord3DList supplyPositions,techPositions;
    AsciiString fileName; MapPlayers players; unsigned int wordF4;
    UnicodeString cachedDisplayName,cachedDescription;
public: MapMetaData(const MapMetaData &); ~MapMetaData(); MapMetaData &operator=(const MapMetaData &);
};
inline MapMetaData::MapMetaData(const MapMetaData &source)
    : displayName(source.displayName), description(source.description), extent(source.extent), numPlayers(source.numPlayers),
      isMultiplayer(source.isMultiplayer), isScenarioMP(source.isScenarioMP), isOfficial(source.isOfficial),
      filesize(source.filesize), crc(source.crc), timestampLo(source.timestampLo), timestampHi(source.timestampHi),
      waypoints(source.waypoints), supplyPositions(source.supplyPositions), techPositions(source.techPositions),
      fileName(source.fileName), players(source.players), wordF4(source.wordF4),
      cachedDisplayName(source.cachedDisplayName), cachedDescription(source.cachedDescription) {}
typedef char SizeCheck[sizeof(MapMetaData)==0x100?1:-1];

// The tree at3025A5 is already byte-verified under its earlier opaque-payload
// model; the metadata reference and its coordinate copy chain prove this alias.
inline WaypointMap::WaypointMap(const WaypointMap &source)
    : _STL::map<AsciiString,Coord3D>(source), numStartSpots(source.numStartSpots) {}

// Retail faction-tree destruction uses the BFME null-checked header free.
typedef _STL::_Rb_tree<AsciiString,AsciiString,_STL::_Identity<AsciiString>,_STL::less<AsciiString>,_STL::allocator<AsciiString> > FactionSetTree;
template FactionSetTree::~_Rb_tree();

// Reference assignment preserves the same256B member layout. Waypoint
// assignment302C9C copies tree then count; player assignment302CB7 loops
// eight20B records; list assignment301B54 copies three dwords per node.
inline MapMetaData &MapMetaData::operator=(const MapMetaData &o)
{
    displayName.set(o.displayName);
    description.set(o.description);
    extent = o.extent;
    numPlayers = o.numPlayers;
    isMultiplayer = o.isMultiplayer;
    isScenarioMP = o.isScenarioMP;
    isOfficial = o.isOfficial;
    filesize = o.filesize;
    crc = o.crc;
    timestampLo = o.timestampLo;
    timestampHi = o.timestampHi;
    waypoints = o.waypoints;
    supplyPositions = o.supplyPositions;
    techPositions = o.techPositions;
    ((StringBase<char> *)&fileName)->set(*(const StringBase<char> *)&o.fileName);
    players = o.players;
    wordF4 = o.wordF4;
    cachedDisplayName.set(o.cachedDisplayName);
    cachedDescription.set(o.cachedDescription);
    return *this;
}
// The map<AsciiString, MapMetaData> node copy in stlport_rb_tree_hint_00304bef.cpp calls this copy constructor through an opaque spelling pinned to the same 0x003039E8 (thiscall, one const reference); bind that spelling here.
#pragma comment(linker, "/alternatename:??0TreeHintOpaque00304573@@QAE@ABU0@@Z=??0MapMetaData@@QAE@ABV0@@Z")

// The copy operations above are header inlines elsewhere: other units emit
// select-any copies, so strong definitions here were duplicates in the linked
// build. This anchor only makes this unit emit its copies for the ledger
// rows; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitMapMetaDataDeferredCopy@@YAXPAVMapMetaData@@ABV1@PAVWaypointMap@@ABV2@@Z present-unmatched
void bfmeEmitMapMetaDataDeferredCopy(MapMetaData *destination, const MapMetaData &that, WaypointMap *destWaypoints, const WaypointMap &thatW)
{
	destination->MapMetaData::MapMetaData(that);
	*destination = that;
	destWaypoints->WaypointMap::WaypointMap(thatW);
}
#pragma inline_depth()
