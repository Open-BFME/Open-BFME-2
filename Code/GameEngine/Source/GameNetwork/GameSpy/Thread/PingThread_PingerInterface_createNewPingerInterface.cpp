// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/shims/zhcanonascii /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork/GameSpy/Thread
//
// ?createNewPingerInterface@PingerInterface@@SAPAV1@XZ
// retail 0x005590FC, 53 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport
// stlport-range-errors: vendored (these rows match only with STLport's extern __stl_throw_* calls, which offset another shape difference; see inputs/reference/shims/stlport_bfme/stl/_range_errors.h)
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

#define _STLP_USE_STATIC_LIB
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include <winsock.h>	// This one has to be here. Prevents collisions with windsock2.h

#include "GameNetwork/GameSpy/PingThread.h"
#include "mutex.h"
#include "thread.h"

#include "Common/StackDump.h"
#include "Common/SubsystemInterface.h"

//-------------------------------------------------------------------------

static const Int NumWorkerThreads = 10;

typedef std::queue<PingRequest> RequestQueue;
typedef std::queue<PingResponse> ResponseQueue;
class PingThreadClass;

class Pinger : public PingerInterface
{
public:
	virtual ~Pinger();
	Pinger();
	virtual void startThreads( void );
	virtual void endThreads( void );
	virtual Bool areThreadsRunning( void );

	virtual void addRequest( const PingRequest& req );
	virtual Bool getRequest( PingRequest& resp );

	virtual void addResponse( const PingResponse& resp );
	virtual Bool getResponse( PingResponse& resp );

	virtual Bool arePingsInProgress( void );
	virtual Int getPing( AsciiString hostname );

	virtual void clearPingMap( void );
	virtual AsciiString getPingString( Int timeout );

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	MutexClass m_pingMapMutex;
	RequestQueue m_requests;
	ResponseQueue m_responses;
	Int m_requestCount;
	Int m_responseCount;

	std::map<std::string, Int> m_pingMap;

	PingThreadClass *m_workerThreads[NumWorkerThreads];
};

PingerInterface* PingerInterface::createNewPingerInterface( void )
{
	return NEW Pinger;
}
extern PingerInterface *ThePinger;

//-------------------------------------------------------------------------

class PingThreadClass : public ThreadClass
{

public:
	PingThreadClass() : ThreadClass() {}

	void Thread_Function();

private:
	Int doPing( UnsignedInt IP, Int timeout );
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
