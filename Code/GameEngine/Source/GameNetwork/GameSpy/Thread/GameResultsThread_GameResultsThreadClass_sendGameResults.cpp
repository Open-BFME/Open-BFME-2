// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?sendGameResults@GameResultsThreadClass@@AAEHIGABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z
// retail 0x0041A047, 197 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsThread.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <queue>		// BFME uses STLport's node allocator for the results queues; parse it
						// before PreRTS.h enables the plain-new allocator.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include <winsock.h>	// This one has to be here. Prevents collisions with winsock2.h

#include "GameNetwork/GameSpy/GameResultsThread.h"
#include "mutex.h"
#include "thread.h"

#include "Common/StackDump.h"
#include "Common/SubsystemInterface.h"

namespace _STL
{
template <>
void deque<GameResultsResponse, allocator<GameResultsResponse> >::_M_push_back_aux_v(
	const GameResultsResponse &response);

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsRequestDestroyThunk.cpp
}

//-------------------------------------------------------------------------

static const Int NumWorkerThreads = 1;

typedef std::queue<GameResultsRequest> RequestQueue;
typedef std::queue<GameResultsResponse> ResponseQueue;
class GameResultsThreadClass;

class GameResultsQueue : public GameResultsInterface
{
public:
	virtual ~GameResultsQueue();
	GameResultsQueue();

	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

	virtual void startThreads( void );
	virtual void endThreads( void );
	virtual Bool areThreadsRunning( void );

	virtual void addRequest( const GameResultsRequest& req );
	virtual Bool getRequest( GameResultsRequest& resp );

	virtual void addResponse( const GameResultsResponse& resp );
	virtual Bool getResponse( GameResultsResponse& resp );

	virtual Bool areGameResultsBeingSent( void );

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	RequestQueue m_requests;
	ResponseQueue m_responses;
	Int m_requestCount;
	Int m_responseCount;

	GameResultsThreadClass *m_workerThreads[NumWorkerThreads];
};
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
struct Rva00641F2EQueueSlots
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
	virtual Bool slot34(GameResultsRequest &req);
};

//-------------------------------------------------------------------------

#ifdef DEBUG_LOGGING
#define CASE(x) case (x): return #x;

static const char *getWSAErrorString( Int error )
{
	switch (error)
	{
		CASE(WSABASEERR)
		CASE(WSAEINTR)
		CASE(WSAEBADF)
		CASE(WSAEACCES)
		CASE(WSAEFAULT)
		CASE(WSAEINVAL)
		CASE(WSAEMFILE)
		CASE(WSAEWOULDBLOCK)
		CASE(WSAEINPROGRESS)
		CASE(WSAEALREADY)
		CASE(WSAENOTSOCK)
		CASE(WSAEDESTADDRREQ)
		CASE(WSAEMSGSIZE)
		CASE(WSAEPROTOTYPE)
		CASE(WSAENOPROTOOPT)
		CASE(WSAEPROTONOSUPPORT)
		CASE(WSAESOCKTNOSUPPORT)
		CASE(WSAEOPNOTSUPP)
		CASE(WSAEPFNOSUPPORT)
		CASE(WSAEAFNOSUPPORT)
		CASE(WSAEADDRINUSE)
		CASE(WSAEADDRNOTAVAIL)
		CASE(WSAENETDOWN)
		CASE(WSAENETUNREACH)
		CASE(WSAENETRESET)
		CASE(WSAECONNABORTED)
		CASE(WSAECONNRESET)
		CASE(WSAENOBUFS)
		CASE(WSAEISCONN)
		CASE(WSAENOTCONN)
		CASE(WSAESHUTDOWN)
		CASE(WSAETOOMANYREFS)
		CASE(WSAETIMEDOUT)
		CASE(WSAECONNREFUSED)
		CASE(WSAELOOP)
		CASE(WSAENAMETOOLONG)
		CASE(WSAEHOSTDOWN)
		CASE(WSAEHOSTUNREACH)
		CASE(WSAENOTEMPTY)
		CASE(WSAEPROCLIM)
		CASE(WSAEUSERS)
		CASE(WSAEDQUOT)
		CASE(WSAESTALE)
		CASE(WSAEREMOTE)
		CASE(WSAEDISCON)
		CASE(WSASYSNOTREADY)
		CASE(WSAVERNOTSUPPORTED)
		CASE(WSANOTINITIALISED)
		CASE(WSAHOST_NOT_FOUND)
		CASE(WSATRY_AGAIN)
		CASE(WSANO_RECOVERY)
		CASE(WSANO_DATA)
		default:
			return "Not a Winsock error";
	}
}

#undef CASE

#endif
//-------------------------------------------------------------------------

Int GameResultsThreadClass::sendGameResults( UnsignedInt IP, UnsignedShort port, const std::string& results )
{
	int error = 0;

	// create the socket
	Int sock = socket( AF_INET, SOCK_STREAM, 0 );
	if (sock < 0)
	{
		DEBUG_LOG(("GameResultsThreadClass::sendGameResults() - socket() returned %d(%s)\n", sock, getWSAErrorString(sock)));
		return sock;
	}

	// fill in address info
	struct sockaddr_in sockAddr;
	memset( &sockAddr, 0, sizeof( sockAddr ) );
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = IP;
	sockAddr.sin_port = htons(port);

	// Start the connection process....
	if( connect( sock, (struct sockaddr *)&sockAddr, sizeof( sockAddr ) ) == -1 )
	{
		error = WSAGetLastError();
		DEBUG_LOG(("GameResultsThreadClass::sendGameResults() - connect() returned %d(%s)\n", error, getWSAErrorString(error)));
		if( ( error == WSAEWOULDBLOCK ) || ( error == WSAEINVAL ) || ( error == WSAEALREADY ) )
		{
			return( -1 );
		}

		if( error != WSAEISCONN )
		{
			closesocket( sock );
			return( -1 );
		}
	}

	if (send( sock, results.c_str(), results.length(), 0 ) == SOCKET_ERROR)
	{
		error = WSAGetLastError();
		DEBUG_LOG(("GameResultsThreadClass::sendGameResults() - send() returned %d(%s)\n", error, getWSAErrorString(error)));
		closesocket(sock);
		return WSAGetLastError();
	}

	closesocket(sock);

	return results.length();
}

//-------------------------------------------------------------------------

#pragma optimize("gty", on)
namespace _STL
{
template <>
void deque<GameResultsResponse, allocator<GameResultsResponse> >::_M_push_back_aux_v(
	const GameResultsResponse &response)
{
	GameResultsResponse responseCopy = response;
	_M_reserve_map_at_back();
	*(this->_M_finish._M_node + 1) = this->_M_map_size.allocate(this->buffer_size());
	_Construct(this->_M_finish._M_cur, responseCopy);
	this->_M_finish._M_set_node(this->_M_finish._M_node + 1);
	this->_M_finish._M_cur = this->_M_finish._M_first;
}
}
