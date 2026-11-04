// cl: /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define USE_BROADCAST_KEYS
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <ctype.h>
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include "PreRTS.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "PeerThreadRetail.h"
#include <map>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * _STL::_STLP_alloc_proxy<char *,char,_STL::allocator<char> >::allocate(unsigned int); }
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
#include "../../../../Include/GameNetwork/GameSpy/PeerThreadClass.h"
// Stats map view: only the independently witnessed maps at +0x98/+0xA4 are modeled.
struct BfmePeerRoomStats { unsigned char unknown[0x98]; std::map<std::string, int> group, staging; };
__declspec(noinline) inline void PeerThreadClass::clearPlayerStats(RoomType type) { BfmePeerRoomStats *stats = reinterpret_cast<BfmePeerRoomStats *>(this); switch (type) { case GroupRoom: stats->group.clear(); break; case StagingRoom: stats->staging.clear(); break; } }

void updateBuddyStatus(GameSpyBuddyStatus, Int groupRoom = 0, std::string gameName = "");
void stagingRoomPlayerEnum(PEER, PEERBool, RoomType, int, const char *, int, void *);
struct BfmePeerJoinState { unsigned char unknown[0x290]; Int localRoomID; unsigned char unknown294[0x484 - 0x294]; Bool roomJoined; unsigned char alignment[3]; Int qmGroupRoom; };
class DualIndexedDispatchThunk { public: void dispatch(void *); };
extern "C" void peerEnumPlayers(PEER, RoomType, void *, void *);
void joinRoomCallback(PEER peer, PEERBool success, PEERJoinResult result, RoomType roomType, void *param)
{
	DEBUG_LOG(("JoinRoomCallback: success==%d, result==%d\n", success, result));
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
		return;
	DEBUG_LOG(("Room id was %d from thread %X\n", reinterpret_cast<BfmePeerJoinState *>(t)->localRoomID, t));
	DEBUG_LOG(("Current staging server name is [%ls]\n", t->getLocalStagingServerName().c_str()));
	DEBUG_LOG(("Room type is %d (GroupRoom=%d, StagingRoom=%d, TitleRoom=%d)\n", roomType, GroupRoom, StagingRoom, TitleRoom));

#ifdef USE_BROADCAST_KEYS
	if (success)
	{
		t->pushStatsToRoom(peer);
		reinterpret_cast<DualIndexedDispatchThunk *>(t)->dispatch(peer);
		t->getStatsFromRoom(peer, roomType);
	}
#endif // USE_BROADCAST_KEYS

	switch (roomType)
	{
		case GroupRoom:
			{
#ifdef USE_BROADCAST_KEYS
				reinterpret_cast<BfmePeerRoomStats *>(t)->group.clear();
#endif // USE_BROADCAST_KEYS
				PeerResponse resp;
				resp.peerResponseType = PeerResponse::PEERRESPONSE_JOINGROUPROOM;
				resp.joinGroupRoom.id = reinterpret_cast<BfmePeerJoinState *>(t)->localRoomID;
				resp.joinGroupRoom.ok = success;
				TheGameSpyPeerMessageQueue->addResponse(resp);
				reinterpret_cast<BfmePeerJoinState *>(t)->roomJoined = success == PEERTrue;
				DEBUG_LOG(("Entered group room %d, qm is %d\n", reinterpret_cast<BfmePeerJoinState *>(t)->localRoomID, reinterpret_cast<BfmePeerJoinState *>(t)->qmGroupRoom));
				if ((!reinterpret_cast<BfmePeerJoinState *>(t)->qmGroupRoom) || (reinterpret_cast<BfmePeerJoinState *>(t)->qmGroupRoom != reinterpret_cast<BfmePeerJoinState *>(t)->localRoomID))
				{
					DEBUG_LOG(("Updating buddy status\n"));
					updateBuddyStatus( BUDDY_LOBBY, reinterpret_cast<BfmePeerJoinState *>(t)->localRoomID );
				}
			}
			break;
		case StagingRoom:
			{
#ifdef USE_BROADCAST_KEYS
				t->clearPlayerStats(StagingRoom);
#endif // USE_BROADCAST_KEYS
				PeerResponse resp;
				resp.peerResponseType = PeerResponse::PEERRESPONSE_JOINSTAGINGROOM;
				resp.joinStagingRoom.id = reinterpret_cast<BfmePeerJoinState *>(t)->localRoomID;
				resp.joinStagingRoom.ok = success;
				resp.joinStagingRoom.result = result;
				if (success)
				{
					DEBUG_LOG(("joinRoomCallback() - game name is now '%ls'\n", t->getLocalStagingServerName().c_str()));
					updateBuddyStatus( BUDDY_STAGING, 0, WideCharStringToMultiByte(t->getLocalStagingServerName().c_str()) );
				}

				resp.joinStagingRoom.isHostPresent = FALSE;
				DEBUG_LOG(("Enum of staging room players\n"));
				peerEnumPlayers(peer, StagingRoom, reinterpret_cast<void *>(stagingRoomPlayerEnum), &resp);
				DEBUG_LOG(("Host %s present\n", (resp.joinStagingRoom.isHostPresent)?"is":"is not"));

				TheGameSpyPeerMessageQueue->addResponse(resp);
			}
			break;
	}
}
