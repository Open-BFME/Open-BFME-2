// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??1?$_Rb_tree@W4ObjectID@@U?$pair@$$CBW4ObjectID@@H@_STL@@U?$_Select1st@U?$pair@$$CBW4ObjectID@@H@_STL@@@3@U?$less@W4ObjectID@@@3@V?$allocator@U?$pair@$$CBW4ObjectID@@H@_STL@@@3@@_STL@@QAE@XZ,
// retail 0x00286852, 56 bytes. STLport 4.5.3 _Rb_tree dtor of map<ObjectID, int>
// (callers: OpenContain/HordeContain/SiegeEngineContain/HordeSiegeEngineContain
// dtors, their unwind funclets and findBestTarget's via the ~map thunk 0x00286921,
// AITargetHeuristicEnemyStructure::findBestTarget 0x005735C6). ConnectionManager's
// +0x12138 map is not this tree: it unwinds through 0x004D233F.
// Target facts: it calls clear 0x00286656, which calls the self-recursive erase
// 0x00286183. Retail keeps several byte-identical free-based erase/clear/dtor
// chains (0x00286183, 0x004ABAD6, 0x000692F5, 0x00219880), so /OPT:ICF did not
// fold the self-recursive erase and the chain is ONE tree instantiation. Its one
// key-reading caller, findBestTarget, keys it by Object::getID() with a signed
// 32-bit compare (folded _M_find 0x00388F63) and counts int votes (operator[]
// 0x0028932C): map<ObjectID, int>. The int/void* names belong to the twin chain
// 0x004ABCFE -> 0x004ABC5C -> 0x004ABAD6.
#include <map>

#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/ObjectID.h"

typedef _STL::pair<const ObjectID, int> ObjectIDIntPair;
typedef _STL::_Rb_tree<ObjectID, ObjectIDIntPair, _STL::_Select1st<ObjectIDIntPair>, _STL::less<ObjectID>, _STL::allocator<ObjectIDIntPair> > ObjectIDIntTree;
template <> void ObjectIDIntTree::clear();  // rowed at 0x00286656 (StlSweepW5Rva00286656.cpp)
template ObjectIDIntTree::~_Rb_tree();

// The family's empty-map construction chain folds into the shared STLport
// bodies (map 0x0033C432 -> tree 0x001F068F -> tree base 0x001F0534).
typedef _STL::map<ObjectID, int> ObjectIDIntMap;
template ObjectIDIntMap::map();

// AITargetHeuristicEnemyStructure::findBestTarget 0x005735C6 counts its votes
// through operator[], which /OPT:ICF folded onto the int-keyed map body
// 0x0028932C; its lower_bound/insert/insert_unique/_M_insert/_M_create_node
// chain folds onto the map<int,int> bodies too (0x00382A92, 0x00289147,
// 0x00422EC0, 0x001E6F5F, 0x0038341E). The fold-proof pin in reverse/symbols.csv
// names this unit; /D_BFME_RETAIL_TREE_INSERT_LAYOUT gives insert_unique retail's
// branch layout (vendor/stlport/stl/_tree.c).
template int &ObjectIDIntMap::operator[](const ObjectID &);
