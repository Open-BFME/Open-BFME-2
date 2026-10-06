// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@VRva0022304A@@V1@@_STL@@YAXPAVRva0022304A@@ABV1@@Z @0x002238B4 45B
// STLport placement copy of the AsciiString-keyed pair Rva0022304A through its rowed copy
// ctor 0x002235B6, under the EH frame MSVC emits for a placement new-expression; cdecl ret.
// Evidence: sole caller 0x002241AC (the hash_map node allocator of the bfmeSetText chain
// 0x00225301) passes the node's value field and the pair.
#include <new>
#include <memory>
#include "ascii_string.h"

class Rva0022300F
{
public:
	Rva0022300F(const Rva0022300F &o);
	~Rva0022300F();
};

class Rva0022304A
{
public:
	Rva0022304A(const Rva0022304A &o);
private:
	AsciiString m_head;
	Rva0022300F m_item;
};

template void _STL::_Construct<Rva0022304A, Rva0022304A>(Rva0022304A *, const Rva0022304A &);
