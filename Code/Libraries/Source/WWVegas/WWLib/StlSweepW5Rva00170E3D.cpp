// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <memory>
#include <string>

struct Rva00170E3DElement { unsigned words[1];bool operator<(const Rva00170E3DElement& b)const{return words[0]<b.words[0];}bool operator==(const Rva00170E3DElement& b)const{return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<unsigned int const, Rva00170E3DElement>, _STL::_Nonconst_traits<_STL::pair<unsigned int const, Rva00170E3DElement> > > _STL::_Rb_tree<unsigned int, _STL::pair<unsigned int const, Rva00170E3DElement>, _STL::_Select1st<_STL::pair<unsigned int const, Rva00170E3DElement> >, _STL::less<unsigned int>, _STL::allocator<_STL::pair<unsigned int const, Rva00170E3DElement> > >::insert_equal(_STL::pair<unsigned int const, Rva00170E3DElement> const &);

class Rva00170B19
{
public:
	~Rva00170B19();
};

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
	((Rva00170B19 *)this)->~Rva00170B19();
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

