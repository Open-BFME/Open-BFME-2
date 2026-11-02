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

struct Rva00170E3DElement { unsigned words[1];bool operator<(const Rva00170E3DElement& b)const{return words[0]<b.words[0];}bool operator==(const Rva00170E3DElement& b)const{return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<unsigned int const, Rva00170E3DElement>, _STL::_Nonconst_traits<_STL::pair<unsigned int const, Rva00170E3DElement> > > _STL::_Rb_tree<unsigned int, _STL::pair<unsigned int const, Rva00170E3DElement>, _STL::_Select1st<_STL::pair<unsigned int const, Rva00170E3DElement> >, _STL::less<unsigned int>, _STL::allocator<_STL::pair<unsigned int const, Rva00170E3DElement> > >::insert_equal(_STL::pair<unsigned int const, Rva00170E3DElement> const &);

// texturepacker.cpp's area multimap<unsigned,AssetReference> tree; its
// destructor is the rowed /EHs body at 0x00170D7F.
class TextureClass;
#include "../../../../GameEngine/Include/Common/AssetReference.h"
namespace _STL { template <> _Rb_tree<unsigned int, pair<const unsigned int, AssetReference>, _Select1st<pair<const unsigned int, AssetReference> >, less<unsigned int>, allocator<pair<const unsigned int, AssetReference> > >::~_Rb_tree(); }
typedef _STL::_Rb_tree<unsigned int, _STL::pair<const unsigned int, AssetReference>, _STL::_Select1st<_STL::pair<const unsigned int, AssetReference> >, _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, AssetReference> > > AreaTree;

class Rva00170AE4
{
public:
	~Rva00170AE4();
};

class Rva00170E78
{
public:
	void rva00170E78();
};

void Rva00170E78::rva00170E78()
{
	((AreaTree *)this)->~AreaTree();
}

class Rva00170E7D
{
public:
	void rva00170E7D();
};

void Rva00170E7D::rva00170E7D()
{
	((Rva00170AE4 *)this)->~Rva00170AE4();
}

// The outer multimap::insert at retail 0x00170EEA (20 bytes): forwards the
// result slot and the argument to the tree/table member of this unit.
typedef _STL::multimap<unsigned int, Rva00170E3DElement, _STL::less<unsigned int >, _STL::allocator<_STL::pair<const unsigned int, Rva00170E3DElement> > > MM_00170EEA;
template MM_00170EEA::iterator MM_00170EEA::insert(const MM_00170EEA::value_type &);
