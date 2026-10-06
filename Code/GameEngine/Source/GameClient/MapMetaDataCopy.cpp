// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
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
class AsciiString : private StringBase<char> { public: __forceinline AsciiString(const AsciiString &o) : StringBase<char>(o) {} void set(const AsciiString &o) { StringBase<char>::set(o); } __forceinline ~AsciiString(); };
#include "../../../Libraries/Include/Lib/Coord3D.h"
struct Region3D { Coord3D lo,hi; Region3D(const Region3D &); };
typedef _STL::list<Coord3D> Coord3DList;
// Instantiate the reference coordinate-list copy and its typed helpers.
class WaypointMap : public _STL::map<AsciiString,Coord3D> { int numStartSpots; public: WaypointMap(const WaypointMap &); };
// The copy chain301EF6->301A3E->3012B0->2C552 proves a string-only20B node:
// these faction names form a set, not a map with an unobserved mapped value.
struct PlayerPosition { unsigned char human,computer,loadAIScripts; int forceTeam; _STL::set<AsciiString> factions; PlayerPosition(); ~PlayerPosition(); };
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
inline MapMetaData::MapMetaData(const MapMetaData &o)
    : displayName(o.displayName), description(o.description), extent(o.extent), numPlayers(o.numPlayers),
      isMultiplayer(o.isMultiplayer), isScenarioMP(o.isScenarioMP), isOfficial(o.isOfficial),
      filesize(o.filesize), crc(o.crc), timestampLo(o.timestampLo), timestampHi(o.timestampHi),
      waypoints(o.waypoints), supplyPositions(o.supplyPositions), techPositions(o.techPositions),
      fileName(o.fileName), players(o.players), wordF4(o.wordF4),
      cachedDisplayName(o.cachedDisplayName), cachedDescription(o.cachedDescription) {}
typedef char SizeCheck[sizeof(MapMetaData)==0x100?1:-1];

// The tree at3025A5 is already byte-verified under its earlier opaque-payload
// model; the metadata reference and its coordinate copy chain prove this alias.
inline WaypointMap::WaypointMap(const WaypointMap &o)
    : _STL::map<AsciiString,Coord3D>(o), numStartSpots(o.numStartSpots) {}

// Retail faction-tree destruction uses the BFME null-checked header free.
typedef _STL::_Rb_tree<AsciiString,AsciiString,_STL::_Identity<AsciiString>,_STL::less<AsciiString>,_STL::allocator<AsciiString> > FactionSetTree;
template FactionSetTree::~_Rb_tree();

PlayerPosition::PlayerPosition()
    : human(1), computer(1), loadAIScripts(1), forceTeam(-1) {}

PlayerPosition::~PlayerPosition() {}

// Reference member destruction; retail22DBC6 is the complete156B body.
// POD coordinate-list cleanup is shared with the already-held integer list.
inline MapMetaData::~MapMetaData() {}

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
// Retail 0x002819AD 28B is list<Coord3D>::push_front: insert(begin(), x).
// Begin is the sentinel's _M_next (double deref); callers at 0x00534BD5 and
// 0x00534BDC push parsed supply/tech positions, and 0x005352DD/0x00535302
// copy waypoint lists. Same shape as rowed list<int> push_front 0x00392076.
template void _STL::list<Coord3D, _STL::allocator<Coord3D> >::push_front(const Coord3D &);
// Retail 0x00534BAF/0x00534BDC 45B are INI Coord3D-list parse callbacks:
// parse a local Coord3D via rowed INI::parseCoord3D 0x0002F507 then push_front
// it into the instance list at +0xA8/+0xAC. Same /O1 /Oy- shape as the rowed
// SideFlags callbacks; honest Rva names, no donor class claimed.
class INI
{
public:
	static void parseCoord3D(INI *, void *, void *, const void *);
};
struct Rva00534BAFHolder
{
	char m_pad[0xA8];
	Coord3DList m_listA8;
};
struct Rva00534BDCHolder
{
	char m_pad[0xAC];
	Coord3DList m_listAC;
};
void Rva00534BAFParse(INI *ini, void *instance, void *, const void *)
{
	Coord3D pos;
	INI::parseCoord3D(ini, 0, &pos, 0);
	((Rva00534BAFHolder *)instance)->m_listA8.push_front(pos);
}
void Rva00534BDCParse(INI *ini, void *instance, void *, const void *)
{
	Coord3D pos;
	INI::parseCoord3D(ini, 0, &pos, 0);
	((Rva00534BDCHolder *)instance)->m_listAC.push_front(pos);
}

// The map<AsciiString, MapMetaData> node copy in stlport_rb_tree_hint_00304bef.cpp calls this copy constructor through an opaque spelling pinned to the same 0x003039E8 (thiscall, one const reference); bind that spelling here.
#pragma comment(linker, "/alternatename:??0TreeHintOpaque00304573@@QAE@ABU0@@Z=??0MapMetaData@@QAE@ABV0@@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:_bfmeCbEOEa=??0PlayerPosition@@QAE@XZ")
#pragma comment(linker, "/alternatename:_bfmeCbEOEb=??1PlayerPosition@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva00078460Elem@@QAE@XZ=??1PlayerPosition@@QAE@XZ")

// The four members above are header inlines elsewhere: other units emit
// select-any copies, so strong definitions here were duplicates in the linked
// build. This anchor only makes this unit emit its copies for the ledger
// rows; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitMapMetaDataCopy@@YAXPAVMapMetaData@@ABV1@PAVWaypointMap@@ABV2@@Z present-unmatched
void bfmeEmitMapMetaDataCopy(MapMetaData *p, const MapMetaData &that, WaypointMap *w, const WaypointMap &thatW)
{
	p->MapMetaData::MapMetaData(that);
	p->MapMetaData::~MapMetaData();
	*p = that;
	w->WaypointMap::WaypointMap(thatW);
}
#pragma inline_depth()
