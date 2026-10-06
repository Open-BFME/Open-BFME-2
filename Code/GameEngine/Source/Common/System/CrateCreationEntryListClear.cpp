// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?clear@?$_List_base@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@QAEXXZ, retail 0x002887EA, 50 bytes.
// List_base clear for crateCreationEntry via _free 0x00030830. Retail calls the
// element deleting dtor virtually (lea ecx,[ebx+8]; mov eax,[ecx]; push 0;
// call [eax]), so the element has a virtual dtor; a virtual ~crateCreationEntry
// reproduces the 50B shape byte-exact. Callee of ~_List_base<crateCreationEntry>
// at 0x002889A4 (retail REL32 at +0x04 targets this address).
#include <list>

#include "ascii_string.h"

struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
	virtual ~crateCreationEntry() {}
};

bool operator==(const crateCreationEntry &a, const crateCreationEntry &b);
bool operator<(const crateCreationEntry &a, const crateCreationEntry &b);

template class _STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> >;
