// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/buddythread /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// GameSpyBuddyMessageQueue::GameSpyBuddyMessageQueue 0x00551A94 (110B),
// GameSpyBuddyMessageQueue::getRequest 0x0055106D (102B),
// GameSpyBuddyMessageQueue::getResponse 0x005510D3 (102B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
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

// FILE: BuddyThread.cpp //////////////////////////////////////////////////////
// GameSpy Presence & Messaging (Buddy) thread
// This thread communicates with GameSpy's buddy server
// and talks through a message queue with the rest of
// the game.
// Author: Matthew D. Campbell, June 2002

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"

#include "Common/StackDump.h"

#include "mutex.h"
#include "thread.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------

typedef std::queue<BuddyRequest> RequestQueue;
typedef std::queue<BuddyResponse> ResponseQueue;
class BuddyThreadClass;

class GameSpyBuddyMessageQueue : public GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueue();
	GameSpyBuddyMessageQueue();
	virtual void startThread( void );
	virtual void endThread( void );
	virtual Bool isThreadRunning( void );
	virtual Bool isConnected( void );
	virtual Bool isConnecting( void );

	virtual void addRequest( const BuddyRequest& req );
	virtual Bool getRequest( BuddyRequest& req );

	virtual void addResponse( const BuddyResponse& resp );
	virtual Bool getResponse( BuddyResponse& resp );

	virtual GPProfile getLocalProfileID( void );

	BuddyThreadClass* getThread( void ) { return m_thread; }

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	RequestQueue m_requests;
	ResponseQueue m_responses;
	BuddyThreadClass *m_thread;
	MutexClass m_bfme_rva0063e080_mutex68;
	Int m_bfme_rva0063e080_word70;
};


extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
#define MESSAGE_QUEUE ((GameSpyBuddyMessageQueue *)TheGameSpyBuddyMessageQueue)

//-------------------------------------------------------------------------

class BuddyThreadClass : public ThreadClass
{

public:
	BuddyThreadClass() : ThreadClass() { m_isNewAccount = m_isdeleting = m_isConnecting = m_isConnected = false; m_profileID = 0; m_lastErrorCode = 0; }

	void Thread_Function();

	void errorCallback( GPConnection *con, GPErrorArg *arg );
	void messageCallback( GPConnection *con, GPRecvBuddyMessageArg *arg );
	void connectCallback( GPConnection *con, GPConnectResponseArg *arg );
	void requestCallback( GPConnection *con, GPRecvBuddyRequestArg *arg );
	void statusCallback( GPConnection *con, GPRecvBuddyStatusArg *arg );
	void rva00550720( GPConnection *con, GPRecvBuddyRequestArg *arg );

	Bool isConnecting( void ) { return m_isConnecting; }
	Bool isConnected( void ) { return m_isConnected; }

	GPProfile getLocalProfileID( void ) { return m_profileID; }

private:
	Bool m_isNewAccount;
	Bool m_isConnecting;
	Bool m_isConnected;
	GPProfile m_profileID;
	Int m_lastErrorCode;
	Bool m_isdeleting;
	std::string m_nick, m_email, m_pass;
};

static enum CallbackType
{
	CALLBACK_CONNECT,
	CALLBACK_ERROR,
	CALLBACK_RECVMESSAGE,
	CALLBACK_RECVREQUEST,
	CALLBACK_RECVSTATUS,
	CALLBACK_MAX
};

// Retail 0x00551FB3..0x00552027, 116B, immediately follows addResponse.
// BFME1 34f59164f BuddyThread.cpp supplies callbackWrapper's purpose and
// cases 0..4. Target calls identify those arms independently; case 5 calls
// the existing address-named rva00550720 callback, whose purpose is opaque.
// The target reads the queue's thread at +0x64, checks it once, then forwards
// con and arg through the six-way dispatcher; every arm ends in a cdecl ret.
void callbackWrapper( GPConnection *con, void *arg, void *param )
{
	BuddyThreadClass *thread = MESSAGE_QUEUE->getThread();
	if (!thread)
		return;
	switch ((Int)param)
	{
	case 0: thread->connectCallback(con, (GPConnectResponseArg *)arg); break;
	case 1: thread->errorCallback(con, (GPErrorArg *)arg); break;
	case 2: thread->messageCallback(con, (GPRecvBuddyMessageArg *)arg); break;
	case 3: thread->requestCallback(con, (GPRecvBuddyRequestArg *)arg); break;
	case 4: thread->statusCallback(con, (GPRecvBuddyStatusArg *)arg); break;
	case 5: thread->rva00550720(con, (GPRecvBuddyRequestArg *)arg); break;
	}
}


//-------------------------------------------------------------------------

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameSpyBuddyMessageQueueCtorThunk.cpp
GameSpyBuddyMessageQueue::GameSpyBuddyMessageQueue()
{
	m_bfme_rva0063e080_word70 = 0;
	m_thread = NULL;
}


Bool GameSpyBuddyMessageQueue::getRequest( BuddyRequest& req )
{
	MutexClass::LockClass m(m_requestMutex, 0);
	if (m.Failed())
		return false;

	if (m_requests.empty())
		return false;
	req = m_requests.front();
	m_requests.pop();
	return true;
}

void GameSpyBuddyMessageQueue::addRequest( const BuddyRequest& req )
{
	MutexClass::LockClass m(m_requestMutex);
	if (m.Failed())
		return;

	m_requests.push(req);
}


// Retail 0x00551BA7, 77 bytes: vtable 0x00C6B020 slot 5, between addRequest
// (slot 3) and getResponse (slot 6); the response mutex and queue push.
void GameSpyBuddyMessageQueue::addResponse( const BuddyResponse& resp )
{
	MutexClass::LockClass m(m_responseMutex);
	if (m.Failed())
		return;

	m_responses.push(resp);
}

Bool GameSpyBuddyMessageQueue::getResponse( BuddyResponse& resp )
{
	MutexClass::LockClass m(m_responseMutex, 0);
	if (m.Failed())
		return false;

	if (m_responses.empty())
		return false;
	resp = m_responses.front();
	m_responses.pop();
	return true;
}


//-------------------------------------------------------------------------
