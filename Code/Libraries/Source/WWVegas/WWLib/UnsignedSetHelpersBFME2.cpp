// cl: /O1 /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME 2 set operations61F910/61FAA0 prove one unsigned four-byte key and
// a temporary vector<unsigned int>. These are full byte-and-relocation twins
// of the 140B overflow2DFCF6 and45B subtree release692F5 owners. Key spelling
// is address-derived; no application identity is claimed. Recursion692F5 and
// deallocation30830 are target facts. Source guide: STLport4.5.3 and BFME1
// 575ba2b04 Rva009EC5B0Set/Rva009EC770Set, not their guessed wrapper names.
#include <cstdlib>
extern void __cdecl Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <set>
#include <vector>
struct Rva0061F910Key {unsigned int a;};
inline bool operator<(const Rva0061F910Key&a,const Rva0061F910Key&b){return a.a<b.a;}
typedef _STL::_Rb_tree<Rva0061F910Key,Rva0061F910Key,_STL::_Identity<Rva0061F910Key>,_STL::less<Rva0061F910Key>,_STL::allocator<Rva0061F910Key> > NativeTree;
template void _STL::vector<unsigned int>::_M_insert_overflow(unsigned int *,const unsigned int &,const _STL::__true_type &,unsigned int,bool);
template void NativeTree::_M_erase(_STL::_Rb_tree_node<Rva0061F910Key> *);
