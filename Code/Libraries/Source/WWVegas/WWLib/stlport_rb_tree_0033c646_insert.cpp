// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?insert_unique@?$_Rb_tree@URva0033C646Key@@...@QAE?AU?$_Rb_tree_iterator@...@2@U32@ABURva0033C646Key@@@Z
// retail 0x0033C646 449B: the hinted insert_unique of a second tree.
// Evidence: byte-identical to the rowed Rva00568FE4 tree's hinted insert in
// stlport_rb_tree_10byte_key_568fe4_insert.cpp except its calls. Its eight
// comparator calls read 0x0033AD5C, the rowed
// SparseMatchFinder<WeaponTemplateSet,BitFlags<17>>::MapHelper::operator(),
// its _M_insert call reads 0x0033C0E1 and its unhinted insert_unique reads
// 0x0033C176, next to it rather than near 0x00568FE4. So the tree is likely
// that match finder's map; the key, comparator and tree names here are
// generated and reuse the 568FE4 view only for its code shape.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
struct Rva0033C646Key { float x; float y; unsigned short w; unsigned short pad; };
struct Rva0033C646Less {
  bool operator()(const Rva0033C646Key &a, const Rva0033C646Key &b) const {
    if (a.x < b.x) return false;
    if (a.x > b.x) return true;
    if (a.y < b.y) return false;
    if (a.y > b.y) return true;
    return a.w < b.w;
  }
};
typedef _STL::_Rb_tree<Rva0033C646Key, Rva0033C646Key, _STL::_Identity<Rva0033C646Key>, Rva0033C646Less, _STL::allocator<Rva0033C646Key> > Rva0033C646Tree;
template Rva0033C646Tree::iterator Rva0033C646Tree::insert_unique(Rva0033C646Tree::iterator, const Rva0033C646Tree::value_type &);
