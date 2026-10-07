// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 002236B9..002236F2 calls the already verified AsciiString-to-
// AsciiString hashtable clear at 002234FE, then frees the bucket vector at+4.
// Instantiate that same STLport type using INIMacroTable.cpp's declarations.
#include "ascii_string.h"
namespace rts {
template <class T> struct hash {};
template <> struct hash<AsciiString> {
    unsigned int operator()(const AsciiString &) const;
};
}
#include <hash_map>
typedef _STL::pair<const AsciiString, AsciiString> MacroPair;
typedef _STL::hashtable<MacroPair, AsciiString, rts::hash<AsciiString>,
    _STL::_Select1st<MacroPair>, _STL::equal_to<AsciiString>,
    _STL::allocator<MacroPair> > MacroTable;
// The target allocator calls the game free wrapper with a throwing C++
// declaration, which retains the native EH state transition. Specialize only
// this table's bucket allocator; the node allocator and other TUs stay intact.
void __cdecl freeMacroBucketStorage(void *);
#pragma comment(linker, "/alternatename:?freeMacroBucketStorage@@YAXPAX@Z=_free")
// ?deallocate@allocator<void*> present-unmatched
template <> inline void _STL::allocator<void *>::deallocate(void **p, unsigned int) const
{
    if (p)
        freeMacroBucketStorage(p);
}
template MacroTable::~hashtable();

class Rva002238E1
{
public:
	void rva002238E1();
};

void Rva002238E1::rva002238E1()
{
	((MacroTable *)this)->~hashtable();
}

class Rva0022366C
{
public:
	~Rva0022366C();
};

class Rva002239AD
{
public:
	void rva002239AD();
};

void Rva002239AD::rva002239AD()
{
	((Rva0022366C *)this)->~Rva0022366C();
}
