// cl: -GX-
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/PAVectorEraseRangeFamily003AF.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// vector<Elem003AF9E0>::erase 0x00538DEA (56B), vector<Elem003B2540>::erase
// 0x003F3578 (56B), vector<Elem003AF8C0>::push_back 0x004EE9B1 (56B),
// vector<Elem003AF9E0>::push_back 0x005663DF (56B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// Open-BFME5: more PA-style vector::erase(first,last) 77B siblings on
// d_003ad560. Unique strides plus same-size 0x20 twins (distinct __copy callees).

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#define BFME_PA_ERASE_ELEM( NAME, SIZE ) \
	struct NAME                          \
	{                                    \
		virtual ~NAME();                 \
		char m_body[ (SIZE) - 4 ];       \
		NAME();                          \
		NAME( const NAME & );            \
		NAME &operator=( const NAME & ); \
	}

BFME_PA_ERASE_ELEM( Elem003AF8C0, 0x0C );
BFME_PA_ERASE_ELEM( Elem003AF9E0, 0x10 );
BFME_PA_ERASE_ELEM( Elem003B2540, 0x18 );

// Only the placed members are instantiated; the donor instantiated nine
// whole vector<T> classes, whose other members came out as private copies.
template _STL::vector<Elem003AF9E0>::iterator
	_STL::vector<Elem003AF9E0>::erase( _STL::vector<Elem003AF9E0>::iterator );
template _STL::vector<Elem003B2540>::iterator
	_STL::vector<Elem003B2540>::erase( _STL::vector<Elem003B2540>::iterator );
// The4EE9B1 push_back moved to its verified growth provider, Rva004EE6D0Insert.cpp.
template void _STL::vector<Elem003AF9E0>::push_back( const Elem003AF9E0 & );
