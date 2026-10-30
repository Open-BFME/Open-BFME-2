// cl: /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
//
// ?updateBuddyStatus@@YAXW4GameSpyBuddyStatus@@HV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z, retail 0x003896e7, 347 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport46
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

#include <stdlib.h>
// Retail's inlined string cleanup reaches the GameMemory wrapper at 0x00030830.
// Keep that existing provider distinct from the CRT's imported free declaration.
namespace _STL { void __cdecl free(void *); }
#define free _STL::free

#define Matrix4x4 Matrix4
#include "Lib/BaseType.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include "GameNetwork/GameSpy/BuddyThread.h"
// Keep _String_base<char>::~_String_base inline-only: no call here leaves it out
// of line, and this TU's frameless COMDAT copy is not retail's 0x0000B3C0 body.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_String_base<char, allocator<char> >::~_String_base() { _M_deallocate_block(); }
}
#undef free
// Same seven donor enum values, without unrelated PeerDefs inline bodies.
enum GameSpyBuddyStatus { BUDDY_OFFLINE, BUDDY_ONLINE, BUDDY_LOBBY,
    BUDDY_STAGING, BUDDY_LOADING, BUDDY_PLAYING, BUDDY_MATCHING, BUDDY_MAX };
#define DEBUG_LOG(m) ((void)0)

// Ghidra extent and seven native status literals establish this identity.
// Retail queue copies 0xAE dwords, establishing the 0x2B8 request extent.
// Status writes independently establish these changed GP enum values.
// The body is byte-exact but the emitted STL helpers conflict with the
// current canonical string allocator/destructor copies at link time.
enum { BFME_GP_STAGING = 3, BFME_GP_CHATTING = 4 };
void updateBuddyStatus( GameSpyBuddyStatus status, Int groupRoom = 0, std::string gameName = "" )
{
	// BFME's BuddyRequest is 0x2B8 bytes, not the shared header's 0x208
	// (GameSpyBuddyMessageQueue::getRequest copies 0xAE dwords vs our 0x82).
	// Keep the tail local so this body reserves retail's 0x2B8 frame without
	// changing the shared donor header for other translation units.
	struct Bfme2BuddyStatusRequest : BuddyRequest
	{
		char m_bfme2Tail[0xB0];
	};

	if (!TheGameSpyBuddyMessageQueue)
		return;

	Bfme2BuddyStatusRequest req;
	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_SETSTATUS;
	switch(status)
	{
		case BUDDY_OFFLINE:
			req.arg.status.status = GP_OFFLINE;
			strcpy(req.arg.status.statusString, "Offline");
			strcpy(req.arg.status.locationString, "");
			break;
		case BUDDY_ONLINE:
			req.arg.status.status = GP_ONLINE;
			strcpy(req.arg.status.statusString, "Online");
			strcpy(req.arg.status.locationString, "");
			break;
		case BUDDY_LOBBY:
			req.arg.status.status = BFME_GP_CHATTING;
			strcpy(req.arg.status.statusString, "Chatting");
			sprintf(req.arg.status.locationString, "%d", groupRoom);
			break;
		case BUDDY_STAGING:
			req.arg.status.status = BFME_GP_STAGING;
			strcpy(req.arg.status.statusString, "Staging");
			sprintf(req.arg.status.locationString, "%s", gameName.c_str());
			break;
		case BUDDY_LOADING:
			req.arg.status.status = GP_PLAYING;
			strcpy(req.arg.status.statusString, "Loading");
			sprintf(req.arg.status.locationString, "%s", gameName.c_str());
			break;
		case BUDDY_PLAYING:
			req.arg.status.status = GP_PLAYING;
			strcpy(req.arg.status.statusString, "Playing");
			sprintf(req.arg.status.locationString, "%s", gameName.c_str());
			break;
		case BUDDY_MATCHING:
			req.arg.status.status = GP_ONLINE;
			strcpy(req.arg.status.statusString, "Matching");
			strcpy(req.arg.status.locationString, "");
			break;
	}
	DEBUG_LOG(("updateBuddyStatus %d:%s\n", req.arg.status.status, req.arg.status.statusString));
	TheGameSpyBuddyMessageQueue->addRequest(req);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?TheGameSpyBuddyMessageQueue@@3PAVGameSpyBuddyMessageQueueInterface@@A=?g_rva00627AA0@@3PAURva00627AA0Obj@@A")
