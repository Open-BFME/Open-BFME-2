// Zero Hour internal.h for BFME2's profile library. BFME2 dropped
// ProfileFastCS: the high-level profiler locks with WWLib's
// FastCriticalSectionClass (mutex.h).

#ifndef INTERNAL_H
#define INTERNAL_H

#include "../debug/debug.h"
#include "../WWVegas/WWLib/mutex.h"
#include "profile.h"
#include "internal_funclevel.h"
#include "internal_highlevel.h"
#include "internal_cmd.h"
#include "internal_result.h"

void *ProfileAllocMemory(unsigned numBytes);
void *ProfileReAllocMemory(void *oldPtr, unsigned newSize);
void ProfileFreeMemory(void *ptr);

__forceinline void ProfileGetTime(__int64 &t)
{
	_asm
	{
		mov ecx,[t]
		push eax
		push edx
		rdtsc
		mov [ecx],eax
		mov [ecx+4],edx
		pop edx
		pop eax
	};
}

#endif // INTERNAL_H
