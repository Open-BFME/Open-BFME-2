// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/shims/zhcanonascii /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
//
// ?getRequest@Pinger@@UAE_NAAVPingRequest@@@Z
// retail 0x005503E6, 98 bytes. Dedicated TU ported from the Open-BFME-1
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

Bool Pinger::getRequest( PingRequest& req )
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

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

HANDLE WINAPI IcmpCreateFile(VOID); /* INVALID_HANDLE_VALUE on error */
BOOL WINAPI IcmpCloseHandle(HANDLE IcmpHandle); /* FALSE on error */

/* Note 2: For the most part, you can refer to RFC 791 for detials
 * on how to fill in values for the IP option information structure. 
 */
typedef struct ip_option_information
{
   UnsignedByte Ttl;         /* Time To Live (used for traceroute) */
   UnsignedByte Tos;         /* Type Of Service (usually 0) */
   UnsignedByte Flags;       /* IP header flags (usually 0) */
   UnsignedByte OptionsSize; /* Size of options data (usually 0, max 40) */
   UnsignedByte FAR *OptionsData;   /* Options data buffer */
}
IPINFO, *PIPINFO, FAR *LPIPINFO;

/* Note 1: The Reply Buffer will have an array of ICMP_ECHO_REPLY
 * structures, followed by options and the data in ICMP echo reply
 * datagram received. You must have room for at least one ICMP
 * echo reply structure, plus 8 bytes for an ICMP header. 
 */
typedef struct icmp_echo_reply
{
   UnsignedInt Address;     /* source address */
   ////////UnsignedInt Status;      /* IP status value (see below) */
   UnsignedInt RTTime;      /* Round Trip Time in milliseconds */
   UnsignedShort DataSize;   /* reply data size */
   UnsignedShort Reserved;   /* */
   void FAR *Data;     /* reply data buffer */
   struct ip_option_information Options; /* reply options */
}
ICMPECHO, *PICMPECHO, FAR *LPICMPECHO;

DWORD WINAPI IcmpSendEcho(
   HANDLE IcmpHandle,   /* handle returned from IcmpCreateFile() */
   UnsignedInt DestAddress,  /* destination IP address (in network order) */
   LPVOID RequestData,  /* pointer to buffer to send */
   WORD RequestSize,    /* length of data in buffer */
   LPIPINFO RequestOptns,   /* see Note 2 */
   LPVOID ReplyBuffer,  /* see Note 1 */
   DWORD ReplySize,     /* length of reply (must allow at least 1 reply) */
   DWORD Timeout       /* time in milliseconds to wait for reply */
);

#define IP_STATUS_BASE 11000
#define IP_SUCCESS 0
#define IP_BUF_TOO_SMALL (IP_STATUS_BASE + 1)
#define IP_DEST_NET_UNREACHABLE (IP_STATUS_BASE + 2)
#define IP_DEST_HOST_UNREACHABLE (IP_STATUS_BASE + 3)
#define IP_DEST_PROT_UNREACHABLE (IP_STATUS_BASE + 4)
#define IP_DEST_PORT_UNREACHABLE (IP_STATUS_BASE + 5)
#define IP_NO_RESOURCES (IP_STATUS_BASE + 6)
#define IP_BAD_OPTION (IP_STATUS_BASE + 7)
#define IP_HW_ERROR (IP_STATUS_BASE + 8)
#define IP_PACKET_TOO_BIG (IP_STATUS_BASE + 9)
#define IP_REQ_TIMED_OUT (IP_STATUS_BASE + 10)
#define IP_BAD_REQ (IP_STATUS_BASE + 11)
#define IP_BAD_ROUTE (IP_STATUS_BASE + 12)
#define IP_TTL_EXPIRED_TRANSIT (IP_STATUS_BASE + 13)
#define IP_TTL_EXPIRED_REASSEM (IP_STATUS_BASE + 14)
#define IP_PARAM_PROBLEM (IP_STATUS_BASE + 15)
#define IP_SOURCE_QUENCH (IP_STATUS_BASE + 16)
#define IP_OPTION_TOO_BIG (IP_STATUS_BASE + 17)
#define IP_BAD_DESTINATION (IP_STATUS_BASE + 18)
#define IP_ADDR_DELETED (IP_STATUS_BASE + 19)
#define IP_SPEC_MTU_CHANGE (IP_STATUS_BASE + 20)
#define IP_MTU_CHANGE (IP_STATUS_BASE + 21)
#define IP_UNLOAD (IP_STATUS_BASE + 22)
#define IP_GENERAL_FAILURE (IP_STATUS_BASE + 50)
#define MAX_IP_STATUS IP_GENERAL_FAILURE
#define IP_PENDING (IP_STATUS_BASE + 255)

#define BUFSIZE     8192
#define DEFAULT_LEN 32
#define LOOPLIMIT   4
#define DEFAULT_TTL 64

//-------------------------------------------------------------------------
