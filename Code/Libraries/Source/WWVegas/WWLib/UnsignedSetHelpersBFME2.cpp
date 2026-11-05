// cl: /O1 /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME 2 set operations61F910/61FAA0 prove one unsigned four-byte key and
// a temporary vector<unsigned int>. These are full byte-and-relocation twins
// of the 140B overflow2DFCF6 and45B subtree release692F5 owners. Key spelling
// is address-derived; no application identity is claimed. Recursion692F5 and
// deallocation30830 are target facts. Source guide: STLport4.5.3 and BFME1
// 575ba2b04 Rva009EC5B0Set/Rva009EC770Set, not their guessed wrapper names.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <cstdlib>
extern void __cdecl Rva00030830FreeAllocation(void *);
#include <set>
#include <vector>
// Preserve the placement construction in signed push_back without emitting
// an /O1 copy over the rowed /Od helper at 0x00620140.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Construct<int, int>(int *p, const int &value) {
    _STLP_PLACEMENT_NEW (p) int(value);
}
}
// Keep the header's three inline stores, without emitting an optimized
// out-of-line copy of the /Od provider at retail 0x00023C80.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void vector<unsigned int>::_M_set(unsigned int *s, unsigned int *f, unsigned int *e) {
    this->_M_start = s;
    this->_M_finish = f;
    this->_M_end_of_storage._M_data = e;
}
}
struct Rva0061F910Key {unsigned int a;};
inline bool operator<(const Rva0061F910Key&a,const Rva0061F910Key&b){return a.a<b.a;}
// Both releases call the GameMemory free wrapper (0x00030830) directly.
namespace _STL {
template<> inline void allocator<unsigned int>::deallocate(unsigned int *__p, size_type) const
{
	if (__p != 0) Rva00030830FreeAllocation((void *)__p);
}
template<> inline void allocator<int>::deallocate(int *__p, size_type) const
{
	if (__p != 0) Rva00030830FreeAllocation((void *)__p);
}
template<> inline void allocator<_Rb_tree_node<Rva0061F910Key> >::deallocate(_Rb_tree_node<Rva0061F910Key> *__p, size_type) const
{
	if (__p != 0) Rva00030830FreeAllocation((void *)__p);
}
}
typedef _STL::_Rb_tree<Rva0061F910Key,Rva0061F910Key,_STL::_Identity<Rva0061F910Key>,_STL::less<Rva0061F910Key>,_STL::allocator<Rva0061F910Key> > NativeTree;
template void _STL::vector<unsigned int>::_M_insert_overflow(unsigned int *,const unsigned int &,const _STL::__true_type &,unsigned int,bool);
template void NativeTree::_M_erase(_STL::_Rb_tree_node<Rva0061F910Key> *);
// MeshGeometry GetEdges 0x0016E450 grows a signed vector<int> through the same folded
// bodies: push_back 0x004DFCB0 (call at 0x0016E5FB), overflow 0x002DFCF6 (0x0016E5B8),
// whose fill_n call goes to 0x0007E48F. This unit's /O1 /G7 copies are those bodies.
template void _STL::vector<int, _STL::allocator<int> >::push_back(const int &);
