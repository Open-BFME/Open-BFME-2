// ?resize@?$hashtable@URva0002C7FDPayload@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@URva0002C7FDPayload@@@_STL@@U?$equal_to@VAsciiString@@@4@V?$Rva0002C7FDAllocator@URva0002C7FDPayload@@@6@@_STL@@QAEXI@Z
// partial score=0.99 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /D_CRTIMP= /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Ghidra [2C7FD,2C8D3),214B RET4: STLport hashtable resize algorithm.
// Original container/payload identity remains unknown. Target node.next is
// at0 and its key prefix at4 is consumed by full89B AsciiString hash2BF8C.
// The prefix-only payload below asserts no unconsumed application fields.
// Native buckets are the three pointers at receiver+4; full34B allocator
// getter23B50 full106B vector ctor26A40 full107Bswap26B60 full48Bnextsize
// 5571B and full17Bgame free30830 establish the complete consumed ABI.
// STLport4.5.3 is the semantic guide. Scoped names avoid asserting the
// structurally served BuildableStatus payload and avoid common COMDATs.
// This emits214B with every nonREL byte exact. Helpers emitted by this
// unit are optimized7B/44B instead of native34B/106B: they must be bound
// to the full providers before landing. Declaration-only specializations
// instead produce219B frame20 versus1C and a5B loop-register difference.
// freeStorage throw(...) retains native unwind-state store and directcall;
// ordinary CRT free dropped that state and emitted210/211B. No pins landed.
#include "ascii_string.h"
#define allocator Rva0002C7FDAllocator
#define __malloc_alloc Rva0002C7FDMalloc
#include <stl/_alloc.h>
namespace _STL {
 void freeStorageRva0002C7FD(void*) throw(...);
 template<> inline void Rva0002C7FDMalloc<0>::deallocate(void *p,size_t) {freeStorageRva0002C7FD(p);}
}
#include <hash_map>


#undef allocator
#undef __malloc_alloc

#include "ascii_string.h"

struct Rva0002C7FDPayload { typedef AsciiString first_type; AsciiString first; };

namespace rts
{
	template <class T> struct hash
	{
		size_t operator()(const T &value) const;
	};

	template <class T> struct equal_to
	{
		bool operator()(const T &left, const T &right) const;
	};
}

typedef _STL::hashtable<Rva0002C7FDPayload, AsciiString, rts::hash<AsciiString>,
 _STL::_Select1st<Rva0002C7FDPayload>, rts::equal_to<AsciiString>,
 _STL::Rva0002C7FDAllocator<Rva0002C7FDPayload> > Rva0002C7FDTable;
template void Rva0002C7FDTable::resize(unsigned int);
