// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Reference STLport4.5.3 two-AsciiString map cleanup. Copy5224E3 uses
// clone522272 and the verified24B node202B4A. Assignment52274D calls
// clear2E44F2 then this same copy chain; clear reaches erase2E44BD.
// Pair copy2C574 constructs temporary ebp-2C at2D4D6; dtor2C0C0
// destroys exactly that temporary at2D4F8. No width-only type inference.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
typedef _STL::pair<const AsciiString,AsciiString> StringPair;
typedef _STL::_Rb_tree<AsciiString,StringPair,_STL::_Select1st<StringPair>,_STL::less<AsciiString>,_STL::allocator<StringPair> > StringPairTree;
template StringPairTree::~_Rb_tree();
template void StringPairTree::erase(StringPairTree::iterator);
template void StringPairTree::erase(StringPairTree::iterator, StringPairTree::iterator);
template StringPairTree::size_type StringPairTree::erase(const AsciiString &);

// ImageCollection's map<unsigned, Image *> tree dtor (retail 0x002D922A),
// called from the ImageCollection dtor at 0x002D92D7 after it deletes each
// node's Image; its clear is the rowed 0x002D9186.
class Image;
typedef _STL::pair<const unsigned, Image *> ImagePair;
typedef _STL::_Rb_tree<unsigned,ImagePair,_STL::_Select1st<ImagePair>,_STL::less<unsigned>,_STL::allocator<ImagePair> > ImageTree;
template ImageTree::~_Rb_tree();

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?erase@?$_Rb_tree@HU?$pair@$$CBHUGen_t_00196d30_p8cd@@@_STL@@U?$_Select1st@U?$pair@$$CBHUGen_t_00196d30_p8cd@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUGen_t_00196d30_p8cd@@@_STL@@@2@@_STL@@QAEXU?$_Rb_tree_iterator@U?$pair@$$CBHUGen_t_00196d30_p8cd@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUGen_t_00196d30_p8cd@@@_STL@@@2@@2@@Z=?erase@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@V1@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@QAEXU?$_Rb_tree_iterator@U?$pair@$$CBVAsciiString@@V1@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@V1@@_STL@@@2@@2@@Z")
