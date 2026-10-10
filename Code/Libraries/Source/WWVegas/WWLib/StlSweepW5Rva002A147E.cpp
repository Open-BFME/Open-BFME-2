// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>

// Preserve the native inline unsigned comparison and its verified external owner at 0x00758C50.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<unsigned int>::operator()(const unsigned int &left, const unsigned int &right) const
{ return left < right; }
}
#include <memory>
#include <string>

struct Rva002A147EElement { unsigned words[1];bool operator<(const Rva002A147EElement& b)const{return words[0]<b.words[0];}bool operator==(const Rva002A147EElement& b)const{return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<unsigned int const, Rva002A147EElement>, _STL::_Nonconst_traits<_STL::pair<unsigned int const, Rva002A147EElement> > > _STL::_Rb_tree<unsigned int, _STL::pair<unsigned int const, Rva002A147EElement>, _STL::_Select1st<_STL::pair<unsigned int const, Rva002A147EElement> >, _STL::less<unsigned int>, _STL::allocator<_STL::pair<unsigned int const, Rva002A147EElement> > >::insert_equal(_STL::pair<unsigned int const, Rva002A147EElement> const &);
