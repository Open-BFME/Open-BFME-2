// cl: /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BFME1 revision6583b3c1 supplies nickname retry purpose/control flow.
// Native38BBF0/384 identifies login-name string54 and the GameSpy retry API.
// The class declaration supplies the method ABI; the field view is partial.
// /GX retains the native unwind-state store around local string cleanup.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <ctype.h>
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include "PreRTS.h"
#include "PeerThreadRetail.h"
namespace _STL { template <> string &string::append(const char *); }
extern "C" void peerRetryWithNickA(PEER, const char *);
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
struct BfmePeerLoginName { unsigned char unknown[0x54]; std::string name; };
class PeerThreadClass { public: void nickErrorCallback(PEER, Int, const char *); };
void PeerThreadClass::nickErrorCallback( PEER peer, Int type, const char *nick )
{
	if(type == PEER_IN_USE)
	{
		Int len = strlen(nick);
		std::string nickStr = nick;
		Int newVal = 0;
		if (nick[len-1] == '}' && nick[len-3] == '{' && isdigit(nick[len-2]))
		{
			newVal = nick[len-2] - '0' + 1;
			nickStr.erase(len-3, 3);
		}

		DEBUG_LOG(("Nickname taken: was %s, new val = %d, new nick = %s\n", nick, newVal, nickStr.c_str()));

		if (newVal < 10)
		{
			nickStr.append("{");
			char tmp[2];
			tmp[0] = '0'+newVal;
			tmp[1] = '\0';
			nickStr.append(tmp);
			nickStr.append("}");
			// Retry the connect with a similar nick.
			reinterpret_cast<BfmePeerLoginName *>(this)->name = nickStr;
			peerRetryWithNickA(peer, nickStr.c_str());
		}
		else
		{
			PeerResponse resp;
			resp.peerResponseType = PeerResponse::PEERRESPONSE_DISCONNECT;
			resp.discon.reason = DISCONNECT_NICKTAKEN;
			TheGameSpyPeerMessageQueue->addResponse(resp);

			// Cancel the connect.
			peerRetryWithNickA(peer, NULL);
		}
	}
	else
	{
		PeerResponse resp;
		resp.peerResponseType = PeerResponse::PEERRESPONSE_DISCONNECT;
		resp.discon.reason = DISCONNECT_BADNICK;
		TheGameSpyPeerMessageQueue->addResponse(resp);

		// Cancel the connect.
		peerRetryWithNickA(peer, NULL);
	}
}
