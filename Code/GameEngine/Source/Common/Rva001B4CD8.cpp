// cl: /DBFME_ASCII_DTOR_DECL /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/stlp_nodealloc
// stlport
// ?rva001B4CD8@Rva001B4CD8@@QAEXXZ RVA 0x001B4CD8 23B
// Evidence: leaf lane; calls pinned 0x001B4C7A Rva001B4C7ATarget::rva001B4C7A
//   on this, then frees the pointer at +0 via rowed 0x00030830 free if non-null;
//   callers 0x001B4D45 and jmp 0x001B4D09.

// Retail calls free directly (the game allocator), not through the CRT
// import: /D_CRTIMP= reads <stdlib.h> without dllimport.
#include <stdlib.h>
#include <list>
#include <vector>
#include "ascii_string.h"

// The callee is the rowed STLport _List_base<BfmeVectorRecord001B4A39>::clear.
struct BfmeVectorRecord001B4A39 {
	AsciiString text0;
	_STL::vector<AsciiString> names0, names1, names2, names3, names4;
	unsigned int word40;
	AsciiString text1;
	~BfmeVectorRecord001B4A39();
};

class Rva001B4CD8
{
public:
	void rva001B4CD8();

private:
	void *m_ptr; // +0 freed if non-null
};

void Rva001B4CD8::rva001B4CD8()
{
	((_STL::_List_base<BfmeVectorRecord001B4A39, _STL::allocator<BfmeVectorRecord001B4A39> > *)this)->clear();
	void *p = m_ptr;
	if (p != 0)
		free(p);
}
