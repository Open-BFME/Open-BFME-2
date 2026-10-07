// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/shims/zhcanonascii /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
//
// ?getPing@Pinger@@UAEHVAsciiString@@@Z
// Retail 0x0054FDA4, 163 bytes. The Pinger vtable at 0x0086AB90 places this
// slot after the existing arePingsInProgress entry at 0x0054F990; the adjacent
// rowed request/response methods confirm the table's method order.
// Ported from reference/open-bfme-1/game/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp.
// stlport
// stlport-range-errors: vendored (see the range-error note in the sibling Pinger TUs)
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// (c) 2001-2003 Electronic Arts Inc.
#define Matrix4x4 Matrix

#define _STLP_USE_STATIC_LIB
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdlib.h>
#undef _CRTIMP
#define _CRTIMP
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include "PreRTS.h"
#include <winsock.h>
#include "GameNetwork/GameSpy/PingThread.h"
#include "mutex.h"
#include "thread.h"
#include "Common/StackDump.h"
#include "Common/SubsystemInterface.h"
#include <string>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#undef free
#pragma comment(linker, "/alternatename:?Rva00030830FreeAllocation@@YAXPAX@Z=_free")

static const Int NumWorkerThreads = 10;
typedef std::queue<PingRequest> RequestQueue;
typedef std::queue<PingResponse> ResponseQueue;

namespace _STL {
template <> bool operator< <char, char_traits<char>, allocator<char> >(const string &, const string &) throw();
}

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
	virtual Bool getRequest( PingRequest& req );
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

Int Pinger::getPing( AsciiString hostname )
{
	MutexClass::LockClass m(m_pingMapMutex, 0);
	if (m.Failed())
		return false;

	std::map<std::string, Int>::const_iterator it = m_pingMap.find(hostname.str());
	if (it != m_pingMap.end())
		return it->second;

	return -1;
}
