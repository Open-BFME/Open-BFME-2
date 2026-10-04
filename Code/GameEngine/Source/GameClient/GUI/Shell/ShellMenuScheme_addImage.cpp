// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?addImage@ShellMenuScheme@@QAEXPAVShellMenuSchemeImage@@@Z retail
// 0x002007BE (23B), pinned. Zero Hour's ShellMenuScheme::addImage: a null
// image is ignored, otherwise it is appended to the image list at +0x04
// through the folded list<int>::push_back (row 0x0005548F).
#include <list>

class ShellMenuSchemeImage;

class ShellMenuScheme
{
public:
	void addImage( ShellMenuSchemeImage *schemeImage );
private:
	int m_00;
	_STL::list<int> m_imageList; // +0x04
};

void ShellMenuScheme::addImage( ShellMenuSchemeImage *schemeImage )
{
	if( !schemeImage )
		return;
	m_imageList.push_back( *(int *)&schemeImage );
}
