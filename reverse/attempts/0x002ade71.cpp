// ?rva002ADE71@PlayerRelationMap@@QAEPAV1@PBV1@@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /DNDEBUG /MD
// stlport
// WB C0FEC0 clears member+4, iterates source+4 and copies key4/value8;
// native cloneFrom calls it on the vtable-identified PlayerRelationMap.
// All callees resolve through existing providers. Remaining native register
// allocation: node ESI/map EDI versus compiler node EDI/map ESI, prologue
// save ordering and typed-begin add/push ordering. Early iterator assignment
// adds a temporary/extent overflow. G5/G6/G7 and Ox/Os do not improve; Og-
// grows to124B. No new pin, extent change, matched row or gate edit.
#include <hash_map>
enum Relationship { RELATION_UNKNOWN=0 };
typedef _STL::hash_map<int,Relationship> RelationMapView;
typedef _STL::hashtable<_STL::pair<const int,Relationship>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<const int,Relationship> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,Relationship> > > RelationTableView;
namespace _STL {template<> RelationMapView::iterator &RelationMapView::iterator::operator++(); template<> RelationTableView::iterator RelationTableView::begin();}
class PlayerRelationHashMap { public: void clear(); char bytes[0x1C]; };
class Object;
struct RelationNodeView { void *next; int key; Object *value; };
class ObjectLookupMap { public: Object **findSlot(int *key); };
class PlayerRelationMap {
public: PlayerRelationMap *rva002ADE71(const PlayerRelationMap *source);
PlayerRelationHashMap m_map;
protected: virtual ~PlayerRelationMap();
};
PlayerRelationMap *PlayerRelationMap::rva002ADE71(const PlayerRelationMap *source) {
 m_map.clear();
 RelationMapView *sourceMap=reinterpret_cast<RelationMapView*>(const_cast<PlayerRelationHashMap*>(&source->m_map));
 RelationMapView::iterator it=sourceMap->begin();
 while(it != sourceMap->end()) {
  RelationNodeView *node=reinterpret_cast<RelationNodeView*>(it._M_cur);
  Object **slot=reinterpret_cast<ObjectLookupMap*>(&m_map)->findSlot(&node->key);
  *slot=node->value;
  ++it;
 }
 return this;
}
