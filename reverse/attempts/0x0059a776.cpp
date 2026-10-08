// ?distanceSortUnits@AITeamBuilder@@QAEXPAXPBXPBUCoord3D@@@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB 0x0152B630 names distanceSortUnits (assert 492). Native
// [0x0059A776,0x0059A85C) sorts ObjectIDs by squared distance from a point.
// Native object position is +0x38, input IDs have stride four, and tree
// records contain a float key and one ID. All callees retain their existing
// ledger owners. The ScienceType vector and int-pointer map constructor
// below are ABI views of the measured storage, not application type claims.
#include <map>
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> DistanceValue;
typedef _STL::_Rb_tree<float, DistanceValue, _STL::_Select1st<DistanceValue>,
    _STL::less<float>, _STL::allocator<DistanceValue> > DistanceTree;
typedef _STL::map<int, void *> HeaderConstructor;

enum ScienceType { SCIENCE_0 = 0 };
typedef _STL::vector<ScienceType> IDVectorView;
namespace _STL {
template <> HeaderConstructor::map();
template <> DistanceTree::iterator DistanceTree::insert_equal(const DistanceValue &);
template <> void IDVectorView::reserve(unsigned int);
template <> void IDVectorView::push_back(const ScienceType &);
}

// The rowed destructor owns an eight-byte tree header/count pair. Native
// construction uses the existing map constructor with this same storage.
class Rva00599FAA
{
public:
    __forceinline Rva00599FAA() { new (this) HeaderConstructor; }
    ~Rva00599FAA();
    _STL::_Rb_tree_node_base *header;
    unsigned int count;
};

extern GameLogic *TheGameLogic;

class AITeamBuilder
{
public:
    void distanceSortUnits(void *sortedStorage, const void *unitsStorage,
        const Coord3D *center);
};

void AITeamBuilder::distanceSortUnits(void *sortedStorage,
    const void *unitsStorage, const Coord3D *center)
{
    Rva00599FAA distances;
    const IDVectorView *units = static_cast<const IDVectorView *>(unitsStorage);
    IDVectorView *sorted = static_cast<IDVectorView *>(sortedStorage);
    const ScienceType *id = units->begin();
    const ScienceType *end = units->end();
    for (; id != end; ++id) {
        unsigned int objectID = (unsigned int)*id;
        Object *object = TheGameLogic->findObjectByID((ObjectID)objectID);
        const Coord3D *position = (const Coord3D *)((const char *)object + 0x38);
        float x = center->x - position->x;
        float y = center->y - position->y;
        float z = center->z - position->z;
        TreeOpaqueMapped00372FF4 value;
        value.m_bits = objectID;
        ((DistanceTree *)&distances)->insert_equal(DistanceValue(x*x + y*y + z*z, value));
    }
    sorted->reserve(distances.count);
    DistanceTree *tree = (DistanceTree *)&distances;
    DistanceTree::iterator finish = tree->end();
    for (DistanceTree::iterator item = tree->begin();
         item._M_node != finish._M_node; ++item) {
        sorted->push_back(*(const ScienceType *)&item->second.m_bits);
    }
}
