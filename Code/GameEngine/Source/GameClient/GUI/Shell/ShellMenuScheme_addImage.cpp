// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?addImage@ShellMenuScheme@@QAEXPAVShellMenuSchemeImage@@@Z retail
// 0x002007BE (23B), pinned. Zero Hour's ShellMenuScheme::addImage: a null
// image is ignored, otherwise it is appended to the image list at +0x04
// through the folded list<int>::push_back (row 0x0005548F).
#include <list>

// LINK: single-node insert binds the verified native STLport owner at RVA
// 0x005925E2; keep the out-of-line call without emitting a competing copy.
namespace _STL {
template <> list<int>::iterator list<int>::insert(iterator position, const int &x);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

class ShellMenuSchemeImage;

class ShellMenuScheme
{
public:
	void addImage( ShellMenuSchemeImage *schemeImage );
private:
	int m_00;
	_STL::list<ShellMenuSchemeImage *> m_imageList; // +0x04
};

void ShellMenuScheme::addImage( ShellMenuSchemeImage *schemeImage )
{
	if( !schemeImage )
		return;
	reinterpret_cast<_STL::list<int> &>(m_imageList).push_back( *(int *)&schemeImage );
}
