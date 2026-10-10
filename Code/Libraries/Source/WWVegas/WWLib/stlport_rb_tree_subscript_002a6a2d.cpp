// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /Ob2 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
// BFME2 STLport subscript: AsciiString key and an opaque four-byte list view.
// Native 0x002A6A2D..0x002A6AC2; primary twin is list-map subscript0x005CAC49.
// The node allocates 24 bytes and constructs its 8-byte value at node+16.
// _Construct 0x2A1EC8 calls pair copy 0x2A1538: AsciiString copy 0x365F0,
// then the mapped object copy constructor 0x2A1383 on the second pair field.
// Comparison reaches the established AsciiString operator< at 0x5598C.
// Semantic donor: BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree.
#include <utility>
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#include <list>
#include <map>


#include "ascii_string.h"

bool operator<(const AsciiString &, const AsciiString &);
// The 4-byte mapped field's copy at 0x2A1383 is the matched STLport
// list<int> copy constructor. Keep the address-derived tree type spelling,
// but let its implicit copy delegate to that verified list operation.
// Native default/copy/destroy calls prove the four-byte list operations;
// the application element identity remains opaque. Real list inheritance
// avoids placement-new EH states absent from native149. /O1 is required;
// existing hint providers retain their library /O2 in the home unit.
struct TreeHintOpaque002A484A : public _STL::list<int> {
    __forceinline TreeHintOpaque002A484A() : _STL::list<int>() {}
    __forceinline TreeHintOpaque002A484A(const TreeHintOpaque002A484A &v)
        : _STL::list<int>(v) {}
    __forceinline ~TreeHintOpaque002A484A() {}
};

typedef _STL::pair<const AsciiString, TreeHintOpaque002A484A> TreeHintPair002A484A;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair002A484A, _STL::_Select1st<TreeHintPair002A484A>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair002A484A> > TreeHint002A484A;
typedef _STL::map<AsciiString,TreeHintOpaque002A484A,_STL::less<AsciiString>,_STL::allocator<TreeHintPair002A484A> > MapInsert002a5895;
// The native subscript calls these complete providers from the existing hint TU.
template <> TreeHintPair002A484A::pair(const AsciiString &,const TreeHintOpaque002A484A &);
template <> MapInsert002a5895::iterator MapInsert002a5895::insert(MapInsert002a5895::iterator,const TreeHintPair002A484A &);

// Native 0x002A6A2D: same four-byte list-mapped tree subscript.
template TreeHintOpaque002A484A &MapInsert002a5895::operator[](const AsciiString &);
