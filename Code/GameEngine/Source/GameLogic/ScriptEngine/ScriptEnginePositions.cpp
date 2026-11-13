// cl: /O1 /G7 /arch:SSE  /Ireference/shims/bfmelist /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /MD /EHsc
// stlport
// Native 0035818E..00358211: CRC-keyed records in ScriptEngine+0x1A498.
// ScriptPositionRecord is a structural name: retail compares the first word
// and copies three coordinates at +4. The default constructor initializes
// the key only; the empty destructor and visible STL erase preserve the
// native outgoing iterator argument lifetime and stack-home store.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include <list>

// Compare the typed nodes locally; the shared base wrapper is not called by retail.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits> &a,
                              const _List_iterator<T, RightTraits> &b)
{ return a._M_node != b._M_node; }
}

unsigned long Rva003ECA13Get(const AsciiString &);
struct ScriptPositionRecord {
 ScriptPositionRecord();
 ~ScriptPositionRecord() {}
 unsigned long key;
 Coord3D position;
};
#include "../../../Include/GameLogic/BfmeFloat4Record00469C61.h"
#include "../../../Include/GameLogic/Rva00357E14.h"
typedef _STL::list<ScriptPositionRecord> ScriptPositionList;
namespace _STL {
template<> inline list<ScriptPositionRecord>::iterator list<ScriptPositionRecord>::erase(iterator pos){
 _List_node_base *next=pos._M_node->_M_next;
 _List_node_base *prev=pos._M_node->_M_prev;
 _Node *node=(_Node *)pos._M_node;
 prev->_M_next=next;next->_M_prev=prev;
 _Destroy(&node->_M_data);
 this->_M_node.deallocate(node,1);
 return iterator((_Node *)next);
}
}
class ScriptEngine {
public:
 void rva0035818E(const AsciiString &,Coord3D *);
 char pad[0x1a498];
 ScriptPositionList positions;
};
void ScriptEngine::rva0035818E(const AsciiString &name,Coord3D *position)
{
 if(name.isEmpty())return;
 unsigned long key=Rva003ECA13Get(name);
 for(ScriptPositionList::iterator it=positions.begin();it!=positions.end();++it){
  if(it->key==key){
   if(position)it->position=*position;
   else positions.erase(it);
   return;
  }
 }
 ScriptPositionRecord record;
 record.key=key;
 record.position=*position;
 ((Rva00357E14 *)&positions)->rva00357E14((const BfmeFloat4Record00469C61 &)record);
}

