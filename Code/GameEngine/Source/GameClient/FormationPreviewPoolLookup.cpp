// ?rva002A3E5A@InGameUI@@QAEPAVFormationPreviewPoolObject@1@PAVThingTemplate@@@Z
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc 
// stlport
// WB00DC4300 and native002A3E5A..002A3F56 establish the pool lookup,
// 12-byte drawable/decal/assigned payload and the two template descriptors.
// Keep STLport's lookup and multimap wrapper visible: the former makes the
// argument's lifetime visible, the latter copies the returned iterator.
#include <map>
// Keep typed iterator comparisons local; this unit's incidental tree-base
// comparison COMDAT differs from the selected library provider.
namespace _STL {
template <class Value, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<Value, LeftTraits> &a,
                              const _Rb_tree_iterator<Value, RightTraits> &b)
{ return a._M_node != b._M_node; }
// The unsigned comparator is fully inlined here. Retain its definition for
// code generation without emitting another nonretail external copy.
template <> __declspec(dllimport) __forceinline
bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const
{ return a < b; }
}
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class ThingTemplate;
class InGameUI {
public: class FormationPreviewPoolObject; class FormationPreviewDecal;
 FormationPreviewPoolObject *rva002A3E5A(ThingTemplate *type);
private:
 char unknown[0x590];
 struct TreeView { _STL::_Rb_tree_node_base *head; unsigned count; } tree;
};
class InGameUI::FormationPreviewPoolObject {
 void *drawable; void *decal; bool assigned;
public: void assign();
};
extern bool BfmeFormationPreviewUseDecals;
struct Source0029E159
{
public:
	AsciiString m_name; // +0x00
	float m_x; // +0x04
	float m_y; // +0x08
};
class InGameUI::FormationPreviewDecal {
public: FormationPreviewDecal(const Source0029E159&);
private: int m_handle;
};
struct Rva002A147EElement { void *drawable,*decal; bool assigned; };
typedef _STL::pair<const unsigned,Rva002A147EElement> PreviewPair;
typedef _STL::pair<const unsigned,void*> LowerPair;
typedef _STL::_Rb_tree<unsigned,LowerPair,_STL::_Select1st<LowerPair>,_STL::less<unsigned>,_STL::allocator<LowerPair> > PreviewLowerTree;
typedef _STL::_Rb_tree<unsigned,PreviewPair,_STL::_Select1st<PreviewPair>,_STL::less<unsigned>,_STL::allocator<PreviewPair> > PreviewInsertTree;


InGameUI::FormationPreviewPoolObject *InGameUI::rva002A3E5A(ThingTemplate *type) {
 PreviewLowerTree &lookup=reinterpret_cast<PreviewLowerTree&>(tree);
 _STL::multimap<unsigned,Rva002A147EElement> &pool=reinterpret_cast<_STL::multimap<unsigned,Rva002A147EElement>&>(tree);
 PreviewInsertTree::iterator cursor(reinterpret_cast<_STL::_Rb_tree_node<PreviewPair>*>(lookup.lower_bound(reinterpret_cast<const unsigned&>(type))._M_node));
 ThingTemplate *key=type;
 for(;cursor!=pool.end() && cursor->first==reinterpret_cast<unsigned>(key);++cursor) {
  if(!cursor->second.assigned) break;
 }
 if(cursor==pool.end() || cursor->first!=reinterpret_cast<unsigned>(key)) {
  InGameUI::FormationPreviewDecal *decal=0;
  if(BfmeFormationPreviewUseDecals && !reinterpret_cast<const StringBase<char>*>(reinterpret_cast<char*>(key)+0x20)->isEmpty())
   decal=new InGameUI::FormationPreviewDecal(*reinterpret_cast<const Source0029E159*>(reinterpret_cast<char*>(key)+0x20));
  else if(!reinterpret_cast<const StringBase<char>*>(reinterpret_cast<char*>(key)+0x14)->isEmpty())
   decal=new InGameUI::FormationPreviewDecal(*reinterpret_cast<const Source0029E159*>(reinterpret_cast<char*>(key)+0x14));
  Rva002A147EElement element={0,decal,false};
  PreviewPair pair(reinterpret_cast<const unsigned&>(key),element);
  cursor=pool.insert(pair);
 }
 InGameUI::FormationPreviewPoolObject *value=reinterpret_cast<InGameUI::FormationPreviewPoolObject*>(&cursor->second);
 value->assign();
 return value;
}
