// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/EvaMessageVectorAssign.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// vector<EvaMessageInfo>::_M_fill_insert 0x003F6BDB (258B),
// ??4?$vector@UEvaMessageInfo@@V?$allocato 0x001020BA (206B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.

// Open-BFME5: the out-of-line assignment used by Eva's message table.
// Retail 0x004263D0 is entered through ILT 0x00031DBD, which the matched
// Eva::init and Eva::reset bodies use for message-table assignment.  The body
// proves a 0x1C value stride and STLport vector assignment control flow.
// EvaInit.cpp already owns the TU-local EvaMessageVector ABI declaration; this
// file owns only the concrete STLport template instantiation that supplies the
// retail body.  The 28-byte element remains opaque because the retail bytes
// expose only its width and its out-of-line helper calls.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct EvaMessageInfo
{
	char m_unported[ 28 ];
	EvaMessageInfo();
	EvaMessageInfo( const EvaMessageInfo & );
	~EvaMessageInfo();
	EvaMessageInfo &operator=( const EvaMessageInfo & );
};

// Only the two placed members are instantiated; the donor's whole-class
// instantiation emitted every other member as a private copy.
template void _STL::vector<EvaMessageInfo>::_M_fill_insert(
	EvaMessageInfo *, _STL::vector<EvaMessageInfo>::size_type, const EvaMessageInfo & );
template _STL::vector<EvaMessageInfo> &
	_STL::vector<EvaMessageInfo>::operator=( const _STL::vector<EvaMessageInfo> & );
