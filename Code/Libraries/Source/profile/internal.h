// Zero Hour internal.h for BFME2's profile library, with Zero Hour's own
// ProfileFastCS lock (GeneralsMD Libraries/Source/profile/internal.h).
// Target evidence for ProfileFastCS over WWLib's FastCriticalSectionClass:
// retail's profile spin 0x006C5EF0 is ThreadSafeSetFlag's body (this spilled
// to [ebp-8], the m_Flag reference to [ebp-4], lock bts, and the contention
// yield `if (testEvent) WaitForSingleObject(testEvent, 1)`), where WWLib's
// spin 0x0006577F yields through Switch_Thread (0x006105C0) and is what
// StringClass::Get_String/Free_String (0x00610B00/0x00610A40) call. The
// .data handle it reads (0x00E0C774) follows profile_funclevel.cpp's hooks
// (0x00E0C768/0x00E0C76C) and is set by the startup initializer 0x007B6720,
// CreateEventA(NULL, FALSE, FALSE, ""): Zero Hour profile_funclevel.cpp's
// `HANDLE ProfileFastCS::testEvent=::CreateEvent(NULL,FALSE,FALSE,"")`.
// Retail also holds two different 20-byte lock ctors (0x000657BC calling
// the WWLib spin, 0x006C5F40 calling this one), which one inline name could
// not produce: 0x006C5F40 is Lock::Lock below, 0x006C5EF0 ThreadSafeSetFlag.
// Users include <windows.h> first (HANDLE, WaitForSingleObject). WWLib's
// mutex.h stays included although nothing here uses it: without it, the
// added ProfileFastCS declarations swap two loads in profile.cpp's
// Profile::StopRange (verified with build.sh).

#ifndef INTERNAL_H
#define INTERNAL_H

#include "../debug/debug.h"
#include "../WWVegas/WWLib/mutex.h"
#include "profile.h"
#include "internal_funclevel.h"
#include "internal_highlevel.h"
#include "internal_cmd.h"
#include "internal_result.h"

class ProfileFastCS
{
  ProfileFastCS(const ProfileFastCS&);
  ProfileFastCS& operator=(const ProfileFastCS&);

	volatile unsigned m_Flag;
  static HANDLE testEvent;

	void ThreadSafeSetFlag()
	{
		volatile unsigned& nFlag=m_Flag;

		// DASSERT(((unsigned)&nFlag % 4) == 0); (release build: empty)

		__asm mov ebx, [nFlag]
		__asm lock bts dword ptr [ebx], 0
		__asm jc The_Bit_Was_Previously_Set_So_Try_Again
		return;

	The_Bit_Was_Previously_Set_So_Try_Again:
    // can't use SwitchToThread() here because Win9X doesn't have it!
    if (testEvent)
		  ::WaitForSingleObject(testEvent,1);
		__asm mov ebx, [nFlag]
		__asm lock bts dword ptr [ebx], 0
		__asm jc  The_Bit_Was_Previously_Set_So_Try_Again
	}

	void ThreadSafeClearFlag()
	{
		m_Flag=0;
	}

public:
	ProfileFastCS(void):
    m_Flag(0) 
  {
  }

	class Lock
	{
    Lock(const Lock&);
    Lock& operator=(const Lock&);

		ProfileFastCS& CriticalSection;

	public:
		Lock(ProfileFastCS& cs): 
      CriticalSection(cs)
		{
			CriticalSection.ThreadSafeSetFlag();
		}

		~Lock()
		{
			CriticalSection.ThreadSafeClearFlag();
		}
	};

	friend class Lock;
};

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
