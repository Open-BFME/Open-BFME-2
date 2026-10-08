// cl: /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BFME1 donor6583b3c1 supplies MBOT parsing purpose. Native38C05E/795
// is the callback-table entry in Thread_Function38EE; target has six arrays
// of eight tokens and normalizes unknown sixth token -1 to --. The recovered
// handler38B6C1 proves its nine-argument ABI; sixth numeric purpose is unknown.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <ctype.h>
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include "PreRTS.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "strtok_r.h"
#include "PeerThreadRetail.h"
namespace AtoiIAT { extern "C" __declspec(dllimport) int __cdecl atoi(const char *); }
struct BfmePeerQMState { unsigned char unknown[0x294]; QMStatus status; };
class PeerThreadClass { public:
 QMStatus getQMStatus() { return reinterpret_cast<BfmePeerQMState *>(this)->status; }
 void handleQMMatch(PEER, Int, Int, char *names[MAX_SLOTS], char *ips[MAX_SLOTS], char *sides[MAX_SLOTS], char *colors[MAX_SLOTS], char *nats[MAX_SLOTS], char *unknown[MAX_SLOTS]);
};
extern Int matchbotProfileID;
void playerMessageCallback(PEER peer, const char * nick, const char * message, MessageType messageType, void * param)
{
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_MESSAGE;
	resp.nick = nick;
	resp.text = MultiByteToWideCharSingleLine(message);
	resp.message.isPrivate = TRUE;
	resp.message.isAction = (messageType == ActionMessage);
	UnsignedInt IP;
	peerGetPlayerInfoNoWait(peer, nick, &IP, &resp.message.profileID);
	TheGameSpyPeerMessageQueue->addResponse(resp);


	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (t && (t->getQMStatus() != QM_IDLE && t->getQMStatus() != QM_STOPPED))
	{
		if (resp.message.isPrivate && resp.message.profileID == matchbotProfileID)
		{
			char *lastStr = NULL;
			char *cmd = strtok_r((char *)message, " ", &lastStr);
			if ( cmd && strcmp(cmd, "MBOT:MATCHED") == 0 )
			{
				char *mapNumStr = strtok_r(NULL, " ", &lastStr);
				char *seedStr = strtok_r(NULL, " ", &lastStr);
				char *playerStr[MAX_SLOTS];
				char *playerIPStr[MAX_SLOTS];
				char *playerSideStr[MAX_SLOTS];
				char *playerColorStr[MAX_SLOTS];
				char *playerNATStr[MAX_SLOTS];
				char *playerUnknownStr[MAX_SLOTS];
				Int numPlayers = 0;
				for (Int i=0; i<MAX_SLOTS; ++i)
				{
					playerStr[i] = strtok_r(NULL, " ", &lastStr);
					playerIPStr[i] = strtok_r(NULL, " ", &lastStr);
					playerSideStr[i] = strtok_r(NULL, " ", &lastStr);
					playerColorStr[i] = strtok_r(NULL, " ", &lastStr);
					char *nat = strtok_r(NULL, " ", &lastStr);
					playerNATStr[i] = nat;
					playerUnknownStr[i] = strtok_r(NULL, " ", &lastStr);
					if (playerUnknownStr[i] && strcmp(playerUnknownStr[i], "-1") == 0)
						playerUnknownStr[i] = "--";
					if (nat)
					{
						++numPlayers;
					}
					else
					{
						playerStr[i] = NULL;
						playerIPStr[i] = NULL;
						playerSideStr[i] = NULL;
						playerColorStr[i] = NULL;
						playerNATStr[i] = NULL;
						playerUnknownStr[i] = NULL;
					}
				}

				if (numPlayers > 1)
				{
					// woohoo!  got everything needed for a match!
					DEBUG_LOG(("Saw %d-player QM match: map index = %s, seed = %s\n", numPlayers, mapNumStr, seedStr));
					t->handleQMMatch(peer, AtoiIAT::atoi(mapNumStr), AtoiIAT::atoi(seedStr), playerStr, playerIPStr, playerSideStr, playerColorStr, playerNATStr, playerUnknownStr);
				}
			}
			else if ( cmd && strcmp(cmd, "MBOT:WORKING") == 0 )
			{
				Int poolSize = 0;
				char *poolStr = strtok_r(NULL, " ", &lastStr);
				if (poolStr)
					poolSize = AtoiIAT::atoi(poolStr);
				PeerResponse resp;
				resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
				resp.qmStatus.status = QM_WORKING;
				resp.qmStatus.poolSize = poolSize;
				TheGameSpyPeerMessageQueue->addResponse(resp);
			}
			else if ( cmd && strcmp(cmd, "MBOT:WIDENINGSEARCH") == 0 )
			{
				PeerResponse resp;
				resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
				resp.qmStatus.status = QM_WIDENINGSEARCH;
				TheGameSpyPeerMessageQueue->addResponse(resp);
			}
		}
	}
}





