// cl: -O1 -arch:SSE -G7 -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Ireference/shims/bfmealloc_alloconly
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
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UEvaMessageInfo@@@_STL@@QBEXPAUEvaMessageInfo@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct EvaMessageInfo;
namespace _STL { template <> void allocator<EvaMessageInfo>::deallocate(EvaMessageInfo *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// The rows retail's _M_fill_insert reaches for its elements: its destructor call at +0xD7 and fill's assignment.
struct BfmeStringRecord00111ACF { ~BfmeStringRecord00111ACF(); };
struct BfmeAssignRecord28 { BfmeAssignRecord28 &operator=( const BfmeAssignRecord28 & ); };

struct EvaMessageInfo
{
	char m_unported[ 28 ];
	EvaMessageInfo();
	EvaMessageInfo( const EvaMessageInfo & );
	__declspec(noinline) ~EvaMessageInfo() { ( (BfmeStringRecord00111ACF *)this )->~BfmeStringRecord00111ACF(); }
	__declspec(noinline) EvaMessageInfo &operator=( const EvaMessageInfo &other )
	{
		( (BfmeAssignRecord28 *)this )->operator=( *(const BfmeAssignRecord28 *)&other );
		return *this;
	}
};

// Only the two placed members are instantiated; the donor's whole-class
// instantiation emitted every other member as a private copy.
template void _STL::vector<EvaMessageInfo>::_M_fill_insert(
	EvaMessageInfo *, _STL::vector<EvaMessageInfo>::size_type, const EvaMessageInfo & );
template _STL::vector<EvaMessageInfo> &
	_STL::vector<EvaMessageInfo>::operator=( const _STL::vector<EvaMessageInfo> & );

// Native 0x00784015 is the complete 14-byte placement-new exception action
// of _Construct at 0x003F62C8. The whole parent and EH graph bind it to
// the existing empty placement delete at 0x0069E440; element fields stay opaque.

// STLport4.5.3 _vector.h public count-insertion adaptor; complete native tail to owned _M_fill_insert.
template void _STL::vector<EvaMessageInfo, _STL::allocator<EvaMessageInfo> >::insert(EvaMessageInfo *, unsigned int, const EvaMessageInfo &);
