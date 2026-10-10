// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Reference: GeneralsMD MapUtil.cpp WaypointMap::update. Native302B7D..302C81
// independently proves the 12-byte map plus count atC, string-key lookup,
// initial-camera entry, Player_%d_Start loop through eight positions, and
// three-word coordinate copies from node+14. Existing generic providers are
// used through their declared ABI views, without renaming the folded owners.
#include <map>
#include <algorithm>
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType;
class StaticNameKey { public: mutable int key; const char *name; };
class Rva00148F5ECache { public: NameKeyType get(); };
class NameKeyGenerator { public: const AsciiString &keyToName(NameKeyType); };
extern NameKeyGenerator *TheNameKeyGenerator;
extern const StaticNameKey TheKey_InitialCameraPosition;

// The erased find ABI is key-only and shared with MapCache; this view is
// restricted to the links/key and the 12 bytes copied by the waypoint caller.
struct MapCacheNode { int links[4]; AsciiString key; Coord3D coordinate; };
class MapCache { public: MapCacheNode *bfmeFind(const AsciiString &); };

struct TreeHintPayload003012F0 { unsigned int a,b,c; };
typedef _STL::pair<const AsciiString,TreeHintPayload003012F0> PayloadPair;
typedef _STL::map<AsciiString,TreeHintPayload003012F0,_STL::less<AsciiString>,_STL::allocator<PayloadPair> > PayloadMap;
namespace _STL {
template <> TreeHintPayload003012F0 &PayloadMap::operator[](const AsciiString &);
}
typedef _STL::pair<const AsciiString,Coord3D> CoordinatePair;
typedef _STL::_Rb_tree<AsciiString,CoordinatePair,_STL::_Select1st<CoordinatePair>,_STL::less<AsciiString>,_STL::allocator<CoordinatePair> > CoordinateTree;
namespace _STL {
template <> void CoordinateTree::clear();
// Branch-form int overloads: this TU's flags compile the generic max/min ?:
// to cmov, but retail's out-of-line copies use a branch (row 57 family-LK3).
inline const int &(max)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pa < *__pb) return __b; return __a; }
inline const int &(min)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pb < *__pa) return __b; return __a; }
}
class WaypointMap : public _STL::map<AsciiString,Coord3D>
{
public:
    void update();
    int numStartSpots;
};
extern "C" WaypointMap *m_waypoints;

static __forceinline void copyWaypoint(WaypointMap &destination,
 const AsciiString &key, const MapCacheNode &source)
{
    reinterpret_cast<PayloadMap &>(destination)[key] =
        *reinterpret_cast<const TreeHintPayload003012F0 *>(&source.coordinate);
}

void WaypointMap::update()
{
    if (!m_waypoints) { numStartSpots=1; return; }
    clear();
    AsciiString startingCamName = TheNameKeyGenerator->keyToName(
        reinterpret_cast<Rva00148F5ECache *>(const_cast<StaticNameKey *>(&TheKey_InitialCameraPosition))->get());
    MapCacheNode *node=reinterpret_cast<MapCache *>(m_waypoints)->bfmeFind(startingCamName);
    if (node!=*reinterpret_cast<MapCacheNode **>(m_waypoints))
        copyWaypoint(*this,startingCamName,*node);
    numStartSpots=0;
    for (int i=0;i<8;++i) {
        startingCamName.format("Player_%d_Start",i+1);
        node=reinterpret_cast<MapCache *>(m_waypoints)->bfmeFind(startingCamName);
        if (node==*reinterpret_cast<MapCacheNode **>(m_waypoints)) break;
        copyWaypoint(*this,startingCamName,*node);
        ++numStartSpots;
    }
    numStartSpots=_STL::max(numStartSpots,1);
}
