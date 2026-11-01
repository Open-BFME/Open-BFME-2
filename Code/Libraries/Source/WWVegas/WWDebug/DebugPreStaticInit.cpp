// cl: /DNDEBUG /MD /EHa /Oy-
//
// Debug::PreStaticInit, retail 0x000385F0 (114 bytes).
//
// Zero Hour initialises a static Debug Instance member by member here.
// BFME2 (like BFME 1, b1 0x00889500, same bytes but for sizeof(Debug))
// creates the singleton on first use instead, placement-constructed in a
// DebugAllocMemory block (0x9F68 bytes), the constructor at
// 0x00038440 does the member setup, and every call bumps the reference
// count at +0x9C7C before returning the pointer kept in theDebug
// (0x00DE0880).

// Keep the standard placement operations visible for construction and unwind,
// while suppressing the unused competing external placement-new copy.
#define __PLACEMENT_NEW_INLINE
#include <new>
__declspec(dllimport) __forceinline void *__cdecl operator new(size_t, void *memory) throw()
{
	return memory;
}
inline void __cdecl operator delete(void *, void *) throw()
{
}

void *DebugAllocMemory(size_t numBytes);

#include "../../../../GameEngine/Source/Common/debug.h"

// theDebug: retail .bss 0x00DE0880, the one definition (the other units declare it extern).
Debug *theDebug;

// ?PreStaticInit@Debug@@CAPAV1@XZ
Debug *Debug::PreStaticInit()
{
	if (!theDebug)
		theDebug = new (DebugAllocMemory(sizeof(Debug))) Debug;
	++theDebug->refCount;
	return theDebug;
}
