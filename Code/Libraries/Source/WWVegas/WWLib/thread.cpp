// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _WIN32_WINNT 0x0400

#include "thread.h"
#include "except.h"
#include "wwdebug.h"
#include <process.h>
#include <windows.h>
#pragma warning ( push )
#pragma warning ( disable : 4201 )
#include "systimer.h"
#pragma warning ( pop )


// ??0ThreadClass@@ defined in ThreadClassCtor.cpp (kept copy for link).

// ??1ThreadClass@@ defined in ThreadClassLifecycle.cpp (kept copy for link).

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WWLib/ThreadClassLifecycle.cpp
// ThreadClass::Set_Priority: defined in ThreadClassLifecycle.cpp (its row's unit).

void ThreadClass::Stop(unsigned ms)
{
	#ifdef _UNIX
		// assert(0);
		return;
	#else
		// BFME's ThreadClass predates the ZH running/exception-handler fields:
		// its native handle is at +0x48.  Keep the canonical method while using
		// the retail layout locally so the shared ZH-compatible header stays put.
		volatile unsigned long &bfmeHandle =
			*(volatile unsigned long *)((char *)this + 0x48);
		unsigned time=TIMEGETTIME();
		while (bfmeHandle) {
			if ((TIMEGETTIME()-time)>ms) {
				int res=TerminateThread((HANDLE)bfmeHandle,0);
				res;	// just to silence compiler warnings
				WWASSERT(res);	// Thread still not killed!
				bfmeHandle=0;
			}
			Sleep(0);
		}
	#endif
}

// ?Sleep_Ms@ThreadClass@@ present-unmatched
void ThreadClass::Sleep_Ms(unsigned ms)
{
	Sleep(ms);
}

#ifndef _UNIX
HANDLE test_event = ::CreateEvent (NULL, FALSE, FALSE, "");
#endif

// ?Switch_Thread@ThreadClass@@ present-unmatched
void ThreadClass::Switch_Thread()
{
	#ifdef _UNIX
		return;
	#else
		//	::SwitchToThread ();
		::WaitForSingleObject (test_event, 1);
		//	Sleep(1);	// Note! Parameter can not be 0 (or the thread switch doesn't occur)
	#endif
}

// Return calling thread's unique thread id. At 0x006105D0 it compiles to a
// lone tail jump through the GetCurrentThreadId import, between Stop and
// Is_Running as in ZH's thread.cpp order.
unsigned ThreadClass::_Get_Current_Thread_ID()
{
	#ifdef _UNIX
		return 0;
	#else
		return GetCurrentThreadId();
	#endif
}

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WWLib/ThreadClassLifecycle.cpp
// ThreadClass::Is_Running: defined in ThreadClassLifecycle.cpp (its row's unit).
