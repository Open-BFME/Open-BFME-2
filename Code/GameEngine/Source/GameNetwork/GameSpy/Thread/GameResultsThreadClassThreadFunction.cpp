// cl: /O1 /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?Thread_Function@GameResultsThreadClass@@UAEXXZ, retail 0x0041A843 (292 bytes, EH). Own TU: the
// result-worker loop wants /O1 (the __EH_prolog form) while sendGameResults (0x0041A047) lives in
// GameResultsThread_GameResultsThreadClass_sendGameResults.cpp. Ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsThread.cpp (reference/open-bfme-1 @ 6d943426):
// the try/catch around the Winsock worker loop is kept (retail saves ESP for it), the request comes
// from queue slot 0x48 (BFME 1: 0x34), and the bfmealloc allocator frees through the game wrapper.
// stlport
// readable body of ?createNewMessageQueue@GameSpyBuddyMessageQueueInterface@@SAPAV1@XZ: game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp
#define Matrix4x4 Matrix4  // BFME renamed it
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: PingThread.cpp //////////////////////////////////////////////////////
// Ping thread
// Author: Matthew D. Campbell, August 2002

#define __PLACEMENT_VEC_NEW_INLINE
// This worker's temporary strings free through the game wrapper at 0x00030830.
// Bind that call in the string proxy below, independently of STL include order.
#include <stdlib.h>
void __cdecl Rva00030830GameFree(void *);
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <cstddef>
#include <winsock.h>	// This one has to be here. Prevents collisions with winsock2.h

#include "GameNetwork/GameSpy/GameResultsThread.h"
#include "mutex.h"
#include "thread.h"

#include "Common/StackDump.h"
#include "Common/SubsystemInterface.h"
#include "BfmeNarrowRecord0041A5D2.h"
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ if (__p != 0) Rva00030830GameFree(__p); }
}
// Keep _String_base<char>::~_String_base inline-only: no call here leaves it out
// of line, and this TU's frameless COMDAT copy is not retail's 0x0000B3C0 body.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_String_base<char, allocator<char> >::~_String_base() { _M_deallocate_block(); }
}
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end

class GameResultsThreadClass;
extern GameResultsInterface *TheGameResultsQueue;

//-------------------------------------------------------------------------

// BFME's ThreadClass is 0x50 bytes wide: Thread_Function reads its worker lock
// pointer at this+0x50 (0x00641ED3), and the reference thread.h lays the base
// out 8 bytes wider, so the base is redeclared here to keep that offset.
class GameResultsThreadBase
{
public:
	virtual ~GameResultsThreadBase();
	void Execute();
	bool Is_Running();

protected:
	virtual void Thread_Function() = 0;
	char m_threadName[0x40];
	void *m_auxHandle;
	void *m_liveHandle;
	int m_threadPriority;
};

class GameResultsThreadClass : public GameResultsThreadBase
{

public:
	GameResultsThreadClass() : GameResultsThreadBase() {}

	void Thread_Function();

private:
	MutexClass *m_lock;
	Int sendGameResults( UnsignedInt IP, UnsignedShort port, const std::string& results );
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

// Retail asks the queue for a request through vtable slot 0x34 (0x00641F2E):
// the Generals header reaches getRequest at 0x28, so BFME's
// SubsystemInterface carries three more virtuals than the reference one. The
// slots are named by index because nothing in the image names them; the shape
// is fixed by the call site and by GameResultsQueue::getRequest (0x00642440)
// which pops a request and returns the bool the caller tests.
// BFME 2's Thread_Function asks the queue for a request through vtable slot 0x48
// (0x0041A8D4; BFME 1's was 0x34), so its SubsystemInterface carries more virtuals.
struct Rva0041A843QueueSlots
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual Bool slot48(BfmeNarrowRecord0041A5D2 &req);
};

//-------------------------------------------------------------------------

// sendGameResults (0x0041A047) is rowed in GameResultsThread_GameResultsThreadClass_sendGameResults.cpp.

// ?Thread_Function@GameResultsThreadClass@@UAEXXZ, retail 0x0041A843 (292 bytes, EH):
// the worker loop of the donor's GameResultsThreadClass::Thread_Function (Open-BFME-1
// GameResultsThread.cpp): start Winsock, then until the worker lock (this+0x50) is free for
// us to take, fetch a request from the queue (slot 0x48), resolve its host (dotted quad or
// gethostbyname), send the results and build the response; WSACleanup on exit.
void GameResultsThreadClass::Thread_Function()
{
	try {
	BfmeNarrowRecord0041A5D2 req;

	WSADATA wsaData;

	// Fire up winsock (prob already done, but doesn't matter)
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSAStartup( wVersionRequested, &wsaData );

	// The worker lock is held by whoever tears the thread down, so once we can
	// take it ourselves the loop is over.
	while (true)
	{
		MutexClass::LockClass lock(*m_lock, 1);
		if (!lock.Failed())
			break;

		// deal with requests
		if (TheGameResultsQueue && ((Rva0041A843QueueSlots *)TheGameResultsQueue)->slot48(req))
		{
			// resolve the hostname
			const char *hostnameBuffer = req.text0.c_str();
			UnsignedInt IP = 0xFFFFFFFF;
			if (isdigit(hostnameBuffer[0]))
			{
				IP = inet_addr(hostnameBuffer);
			}
			else
			{
				HOSTENT *hostStruct;
				in_addr *hostNode;
				hostStruct = gethostbyname(hostnameBuffer);
				hostNode = (in_addr *) hostStruct->h_addr;
				IP = hostNode->s_addr;
			}

			Int result = sendGameResults( IP, req.short0, req.text1 );
			GameResultsResponse resp;
			resp.hostname.assign(req.text0);
			resp.port = req.short0;
			resp.sentOk = (result == req.text1.length());
		}
	}

	WSACleanup();
	} catch ( ... ) {
	}
}
