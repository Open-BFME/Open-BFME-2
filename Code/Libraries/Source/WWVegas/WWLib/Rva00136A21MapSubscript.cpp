// cl: /O1 /Ob2 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii
// stlport
// Native136A21..136AA5 uses unsigned keys (JAE), one narrow string per
// mapped value and the existing136642 hint worker. Shape guide:4650A0.
// Targetctor523DB7 copies the same key bits; signedness is irrelevant there.
#include <map>
#include "ascii_string.h"
struct TreeKey00242F5E { unsigned int m_id; char _pad[4]; };
struct RvaNode1364F7 { int _c0; RvaNode1364F7 *_parent,*_left,*_right; TreeKey00242F5E _key; };
// Native stack-value construction requires a nontrivial four-byte iterator
// copy. It preserves exactly the node pointer used by the existing hint worker.
struct Rva001364F7Iter { RvaNode1364F7 *m_node; Rva001364F7Iter(RvaNode1364F7 *node):m_node(node){} Rva001364F7Iter(const Rva001364F7Iter &o):m_node(o.m_node){} };
struct Rva001364F7 { Rva001364F7Iter rva00136642(Rva001364F7Iter,const TreeKey00242F5E &); };
class Rva00523DB7 {
public: Rva00523DB7(const int *,const StringBase<char> &);
 int m_00; AsciiString m_04;
};
typedef _STL::_Rb_tree<unsigned int,_STL::pair<const unsigned int,void *>,_STL::_Select1st<_STL::pair<const unsigned int,void *> >,_STL::less<unsigned int>,_STL::allocator<_STL::pair<const unsigned int,void *> > > LowerTree;
namespace _STL { template<> LowerTree::_Link_type LowerTree::_M_lower_bound(const unsigned int &) const; }
class Rva00136A21 {
public:
 AsciiString &rva00136A21(const unsigned int &);
 __declspec(noinline) Rva001364F7Iter rva00136777(Rva001364F7Iter,const Rva00523DB7 &);
private: RvaNode1364F7 *m_head;
};
Rva001364F7Iter Rva00136A21::rva00136777(Rva001364F7Iter hint,const Rva00523DB7 &value) {
 return reinterpret_cast<Rva001364F7 *>(this)->rva00136642(hint,reinterpret_cast<const TreeKey00242F5E &>(value));
}
AsciiString &Rva00136A21::rva00136A21(const unsigned int &key) {
 RvaNode1364F7 *node=reinterpret_cast<RvaNode1364F7 *>(reinterpret_cast<LowerTree *>(this)->lower_bound(key)._M_node);
 if (node==m_head || key<node->_key.m_id) {
  AsciiString empty;
  node=rva00136777(Rva001364F7Iter(node),Rva00523DB7(reinterpret_cast<const int *>(&key),reinterpret_cast<const StringBase<char> &>(empty))).m_node;
 }
 return *reinterpret_cast<AsciiString *>((char *)node+0x14);
}
