// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert@?$_Rb_tree@URva00568FE4Key@@U1@U?$_Identity@URva00568FE4Key@@@_STL@@URva00568FE4Less@@V?$allocator@URva00568FE4Key@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@URva00568FE4Key@@U?$_Nonconst_traits@URva00568FE4Key@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABURva00568FE4Key@@0@Z
// retail 0x00568FE4 149B. _Rb_tree 10-byte key set _M_insert (hinted insert worker).
// Shape matches sibling AsciiString _M_insert 0x002A484A 148B; the 1B delta is the
// member comparator call (lea ecx,[edi+8]) vs the sibling's inlined free operator<
// (2x pop). Calls the rowed _Rebalance 0x00025490; the comparator (71B) and
// create-node (34B) are TU-local members byte-identical to the rowed free helpers
// 0x0056866A/0x00568D95 (same float/word compare and 0x1c alloc plus 10-byte copy
// via rowed 0x00568A9D), landed as ICF twins in the same commit. Evidence: caller
// is the 74B find-or-insert at 0x00569295; prev/next rows are the 20-byte
// StringRecord vector workers 0x00568FBF/0x00569079 in the neighbour TU sharing
// these flags (plus /arch:SSE for the movss/comiss compare); node key at +0x10
// and count at +4 match the 10-byte family (2 floats + word at +8).
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
struct Rva00568FE4Key { float x; float y; unsigned short w; unsigned short pad; };
void __cdecl Rva00568A9DCopy(void *dest, const void *src);
struct Rva00568FE4Less {
  bool operator()(const Rva00568FE4Key &a, const Rva00568FE4Key &b) const {
    if (a.x < b.x) return false;
    if (a.x > b.x) return true;
    if (a.y < b.y) return false;
    if (a.y > b.y) return true;
    return a.w < b.w;
  }
};
typedef _STL::_Rb_tree<Rva00568FE4Key, Rva00568FE4Key, _STL::_Identity<Rva00568FE4Key>, Rva00568FE4Less, _STL::allocator<Rva00568FE4Key> > Rva00568FE4Tree;
template <>
Rva00568FE4Tree::_Link_type Rva00568FE4Tree::_M_create_node(const Rva00568FE4Tree::value_type &value) {
  char *node = _STL::allocator<char>::allocate(0x1c, 0);
  Rva00568A9DCopy(node + 0x10, &value);
  return (Rva00568FE4Tree::_Link_type)node;
}
template Rva00568FE4Tree::iterator Rva00568FE4Tree::insert_unique(Rva00568FE4Tree::iterator, const Rva00568FE4Tree::value_type &);
template Rva00568FE4Tree::iterator Rva00568FE4Tree::insert_equal(const Rva00568FE4Tree::value_type &);
typedef _STL::multiset<Rva00568FE4Key, Rva00568FE4Less, _STL::allocator<Rva00568FE4Key> > Rva00568FE4Multi;
template Rva00568FE4Multi::iterator Rva00568FE4Multi::insert(const Rva00568FE4Multi::value_type &);

// ??$_M_find@URva00568FE4Key@@@?$_Rb_tree@... @0x00568A41 92B (key search
// with the two out-of-line comparator calls), ?_M_erase@... @0x00568F2E 45B,
// ?clear@... @0x0056926C 41B and ??1?$_Rb_tree@... @0x005693D4 56B (clear,
// then free the header): the lookup and teardown members of the same tree,
// each placed uniquely by masked search in 0x568000-0x56A400. The 20B find
// wrapper at 0x00568F7E is not rowed: const find, non-const find and the
// bound wrappers are byte-identical there.
template Rva00568FE4Tree::iterator Rva00568FE4Tree::find(const Rva00568FE4Key &);
template void Rva00568FE4Tree::clear();
template Rva00568FE4Tree::~_Rb_tree();
