// cl: /O1 /arch:SSE /G7 /MD /Ireference/shims/bfme2_ascii
// Native39BDB8..39BE95 / WBFA27E0 select the greatest positive count
// and copy its template's UnicodeString display name at +30. The first map
// also applies the exact witnessed KindOf predicate; the receiver's map1E4
// is a second pass with the same mask, preserving the first winner on ties.
// ScoreKeeper ownership follows the native collector's Player+3BC receiver
// and the two wrappers selecting map1F0 / map1C8. Original member names and
// KindOf enum names are not asserted; storage follows native offsets.
// ZH ScoreKeeper.cpp at BF1 donor9cbfb551fe20 is a map-iteration lead only:
// its getTotalUnitsBuilt sums counts, while target evidence proves this max.
// Use the existing full35B seven-word BitFlags<69> intersection provider;
// this consuming view agrees with its physical28B storage.
// Native39BEAC begins after the preceding verified RET8 and its own RET8
// ends at the rowed helper39BEC3. Its map1C8 and full REL32 are witnessed.
#include "unicode_string.h"
template<int N>class BitFlags {public:bool test(const void*)const;private:unsigned words[7];};
namespace _STL {
struct _Rb_tree_node_base {bool color;_Rb_tree_node_base *parent,*left,*right;};
template<class T>struct _Rb_global {static _Rb_tree_node_base*__cdecl _M_increment(_Rb_tree_node_base*);};
}
struct MostProducedTemplateView {
 char beforeName[0x30];UnicodeString name;char beforeFlags[0x108-0x34];unsigned flags[7];
};
struct MostProducedNode:_STL::_Rb_tree_node_base {const MostProducedTemplateView *type;int count;};
struct ObjectCountMap {_STL::_Rb_tree_node_base *header;int words[2];};
class Rva0039BDB8 {
public:void rva0039BDB8(const BitFlags<69>*,UnicodeString*,const ObjectCountMap*);
 void rva0039BE95(const BitFlags<69>*,UnicodeString*);
 void rva0039BEAC(const BitFlags<69>*,UnicodeString*);
private:char beforeDestroyedMap[0x1C8];ObjectCountMap destroyedMap;ObjectCountMap map1D4;int word1E0;ObjectCountMap otherMap;ObjectCountMap builtMap;
};
void Rva0039BDB8::rva0039BDB8(const BitFlags<69>*mask,UnicodeString*out,const ObjectCountMap*map) {
 int bestCount=0;
 for(_STL::_Rb_tree_node_base *it=map->header->left;it!=map->header;it=_STL::_Rb_global<bool>::_M_increment(it)) {
  const MostProducedNode *entry=static_cast<const MostProducedNode*>(it);
  const MostProducedTemplateView *type=entry->type;
  if(type && mask->test(type->flags)) {
   int count=entry->count;
   if(((type->flags[2]&0x04000000) || (type->flags[0]&0x80) || (type->flags[0]&0xC00) ||
       (type->flags[3]&0x2000) || (type->flags[5]&0x80000000)) && count>bestCount) {
    bestCount=count;
    *out=type->name;
   }
  }
 }
 for(_STL::_Rb_tree_node_base *it=otherMap.header->left;it!=otherMap.header;it=_STL::_Rb_global<bool>::_M_increment(it)) {
  const MostProducedNode *entry=static_cast<const MostProducedNode*>(it);
  const MostProducedTemplateView *type=entry->type;
  if(type && mask->test(type->flags) && entry->count>bestCount) {
   bestCount=entry->count;
   *out=type->name;
  }
 }
}

void Rva0039BDB8::rva0039BE95(const BitFlags<69>*mask,UnicodeString*out) {
 rva0039BDB8(mask,out,&builtMap);
}

void Rva0039BDB8::rva0039BEAC(const BitFlags<69>*mask,UnicodeString*out) {
 rva0039BDB8(mask,out,&destroyedMap);
}
