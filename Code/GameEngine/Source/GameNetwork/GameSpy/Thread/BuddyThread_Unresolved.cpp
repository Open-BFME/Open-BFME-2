// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/buddythread /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Split from BuddyThread.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
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

// BFME 2's WWLib thread base (as in PersistentStorageThread.cpp), not ZH's
// 0x58-byte one: BuddyThreadClass's members start at +0x50 in retail
// (errorCallback 0x005513E9 writes m_lastErrorCode at +0x58).
#define THREAD_H
class ThreadClass
{
public:
	ThreadClass(const char *name);
	void Stop();
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function() = 0;
private:
	char m_name[0x40]; // +0x04
	unsigned int m_threadId; // +0x44
	void *m_handle; // +0x48
	int m_priority; // +0x4C
};
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"

#include "Common/StackDump.h"

#include "mutex.h"
#include "thread.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
namespace _STL { template <> _Deque_base<BuddyResponse, allocator<BuddyResponse> >::~_Deque_base(); }
namespace _STL { template <> void _Deque_base<BuddyRequest, allocator<BuddyRequest> >::_M_create_nodes(BuddyRequest **, BuddyRequest **); }
namespace _STL { template <> void _Deque_base<BuddyResponse, allocator<BuddyResponse> >::_M_destroy_nodes(BuddyResponse **, BuddyResponse **); }
namespace _STL { template <> void _Deque_base<BuddyRequest, allocator<BuddyRequest> >::_M_initialize_map(unsigned int); }
namespace _STL { template <> void deque<BuddyRequest, allocator<BuddyRequest> >::_M_pop_front_aux(); }
namespace _STL { template <> void deque<BuddyRequest, allocator<BuddyRequest> >::_M_push_back_aux_v(BuddyRequest const &); }
namespace _STL { template <> void deque<BuddyRequest, allocator<BuddyRequest> >::_M_reallocate_map(unsigned int, bool); }
namespace _STL { template <> BuddyRequest * allocator<BuddyRequest>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_destroy_nodes@?$_Deque_base@VBuddyRequest@@V?$allocator@VBuddyRequest@@@_STL@@@_STL@@I:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class BuddyRequest;
namespace _STL { template <> void _Deque_base<BuddyRequest,allocator<BuddyRequest> >::_M_destroy_nodes(BuddyRequest * *,BuddyRequest * *); }
// Suppress this TU's non-retail copy of ??1?$_Deque_base@VBuddyRequest@@V?$allocator@VBuddyRequest@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class BuddyRequest;
namespace _STL { template <> _Deque_base<BuddyRequest,allocator<BuddyRequest> >::~_Deque_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@VBuddyRequest@@@_STL@@QBEXPAVBuddyRequest@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class BuddyRequest;
namespace _STL { template <> void allocator<BuddyRequest>::deallocate(BuddyRequest *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PAVBuddyRequest@@@_STL@@QBEXPAPAVBuddyRequest@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class BuddyRequest;
namespace _STL { template <> void allocator<BuddyRequest *>::deallocate(BuddyRequest * *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@VBuddyResponse@@@_STL@@QBEXPAVBuddyResponse@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class BuddyResponse;
namespace _STL { template <> void allocator<BuddyResponse>::deallocate(BuddyResponse *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PAVBuddyResponse@@@_STL@@QBEXPAPAVBuddyResponse@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class BuddyResponse;
namespace _STL { template <> void allocator<BuddyResponse *>::deallocate(BuddyResponse * *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??$max@I@_STL@@YAABIABI0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &); }

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------

typedef std::queue<BuddyRequest> RequestQueue;
typedef std::queue<BuddyResponse> ResponseQueue;
// Native551988 calls the separately verified response deque cleanup.
// Declaration-only here preserves its exception boundary under home flags.
namespace _STL {template<> deque<BuddyResponse>::~deque();}
class BuddyThreadClass;
// Retail shutdown550B4C and cleanup9990D prove the owning lock at +70.
class Rva0009990D
{
public:
	void clear();
	~Rva0009990D(){clear();}
	void set(void *p);
	MutexClass::LockClass *m_ptr; // +0x00
};
class Rva00550B4C
{
public:
	void rva00550B4C();
	char m_pad00[0x64];
private:
	ThreadClass *thread; // +0x64
	char m_pad68[0x8];
	Rva0009990D lockOwner; // +0x70
};

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
	Rva0009990D m_bfme_lock70;
};


extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
#define MESSAGE_QUEUE ((GameSpyBuddyMessageQueue *)TheGameSpyBuddyMessageQueue)

//-------------------------------------------------------------------------

class BuddyThreadClass : public ThreadClass
{

public:
	BuddyThreadClass() : ThreadClass(0) { m_isNewAccount = m_isdeleting = m_isConnecting = m_isConnected = false; m_profileID = 0; m_lastErrorCode = 0; }

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

void callbackWrapper( GPConnection *con, void *arg, void *param );


//-------------------------------------------------------------------------

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameSpyBuddyMessageQueueCtorThunk.cpp
GameSpyBuddyMessageQueue::GameSpyBuddyMessageQueue()
{
	m_bfme_lock70.m_ptr = 0;
	m_thread = NULL;
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

//-------------------------------------------------------------------------

// Zero Hour's BuddyThreadClass::errorCallback; native [5513E9,55182E),1093B
// (callbackWrapper case 1). The GameSpy SDK's GPErrorArg and BFME2's error
// response are read through local views: the sweep shim's GP.h orders
// GPErrorArg differently, and BFME2's BuddyResponse error arm keeps the
// GPResult Zero Hour commented out, putting errorCode at +0x10. The error
// codes are the SDK's values (GP.h's enum here is not). BFME2 also skips the
// bad-nick/bad-email login errors, reports a forced disconnect as response
// type 6, and copies the error code's name over the SDK error string.
struct GPErrorArgSDK
{
	GPResult result;
	GPErrorCode errorCode;
	char *errorString;
	GPEnum fatal;
};
struct BuddyErrorResponseArm
{
	GPResult result;
	GPErrorCode errorCode;
	char errorString[MAX_BUDDY_CHAT_LEN];
	GPEnum fatal;
};
struct BfmeOpaqueOwnedRecord492
{
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
	Int peerRequestType;
	unsigned char m_04[492 - 4];
};


// Native551988..551A06 follows PeerThread cleanup order; target member
// offsets and the already recovered shutdown distinguish the Buddy owner.
GameSpyBuddyMessageQueue::~GameSpyBuddyMessageQueue(){
 ((Rva00550B4C*)this)->rva00550B4C();
}
