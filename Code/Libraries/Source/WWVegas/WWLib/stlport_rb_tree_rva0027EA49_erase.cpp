// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ?_M_erase@?$_Rb_tree@URva0027EA49@@U1@U?$_Identity@URva0027EA49@@@_STL@@U?$less@URva0027EA49@@@3@V?$allocator@URva0027EA49@@@3@@_STL@@AAEXPAU?$_Rb_tree_node@URva0027EA49@@@2@@Z, retail 0x005C6A40 53B.
// Rb_tree _M_erase for set of Rva0027EA49 holders (8B: int at +0 plus TargetRef pointer at +4).
// Evidence: recurse-right via [esi+0x0C] walk-left via [esi+0x08] destroy value at node+0x10 via rowed
// ??1Rva0027EA49@@QAE@XZ at 0x0027EA49 release node via GameMemory free 0x00030830 ret 4.
// Reached from rowed clear 0x005C6B83 pattern and vector destroy sharing same element dtor.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Rva0027EA49 {
	~Rva0027EA49();
	int m_00;
	TargetRef00217D4C *m_04;
};
bool operator<(const Rva0027EA49 &a, const Rva0027EA49 &b);
typedef _STL::_Rb_tree<Rva0027EA49, Rva0027EA49, _STL::_Identity<Rva0027EA49>, _STL::less<Rva0027EA49>, _STL::allocator<Rva0027EA49> > Rva0027EA49Tree;

template void Rva0027EA49Tree::_M_erase(Rva0027EA49Tree::_Link_type);

template void Rva0027EA49Tree::clear();

// Whole-class instantiation of this tree. It reproduces erase (retail 0x005C6BAC)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<Rva0027EA49,Rva0027EA49,_STL::_Identity<Rva0027EA49>,_STL::less<Rva0027EA49>,_STL::allocator<Rva0027EA49> >;
