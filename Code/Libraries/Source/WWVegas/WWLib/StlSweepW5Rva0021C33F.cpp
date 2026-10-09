// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Native assignment21C33F calls copy21C2CC -> clone53444F -> node382B7F
// -> construct60C9D9, which copies a full DWORD key and DWORD value.
// Correct the old16-bit structural view to32-bit. Original key identity and
// its signed ordering remain inference. The115B assignment stays byte-exact.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

struct Rva0021C33FElement { int words[1]; bool operator<(const Rva0021C33FElement&b)const { return words[0]<b.words[0]; } bool operator==(const Rva0021C33FElement&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree<Rva0021C33FElement, _STL::pair<Rva0021C33FElement const, int>, _STL::_Select1st<_STL::pair<Rva0021C33FElement const, int> >, _STL::less<Rva0021C33FElement>, _STL::allocator<_STL::pair<Rva0021C33FElement const, int> > > & _STL::_Rb_tree<Rva0021C33FElement, _STL::pair<Rva0021C33FElement const, int>, _STL::_Select1st<_STL::pair<Rva0021C33FElement const, int> >, _STL::less<Rva0021C33FElement>, _STL::allocator<_STL::pair<Rva0021C33FElement const, int> > >::operator=(_STL::_Rb_tree<Rva0021C33FElement, _STL::pair<Rva0021C33FElement const, int>, _STL::_Select1st<_STL::pair<Rva0021C33FElement const, int> >, _STL::less<Rva0021C33FElement>, _STL::allocator<_STL::pair<Rva0021C33FElement const, int> > > const &);
