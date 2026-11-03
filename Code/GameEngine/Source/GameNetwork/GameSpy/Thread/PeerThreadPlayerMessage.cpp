// cl: /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BFME1 donor6583b3c1 supplies MBOT parsing purpose. Native38C05E/795
// is the callback-table entry in Thread_Function38EE; target has six arrays
// of eight tokens and normalizes unknown sixth token -1 to --. The recovered
// handler38B6C1 proves its nine-argument ABI; sixth numeric purpose is unknown.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <ctype.h>
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include "PreRTS.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "strtok_r.h"
#include "PeerThreadRetail.h"
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(char const *); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > & basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::operator=(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_construct_null(unsigned short *); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_construct_null_aux(unsigned short *, __true_type const &); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void __char_traits_base<unsigned short, unsigned short>::assign(unsigned short &, unsigned short const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<char *, char, allocator<char> >::deallocate(char *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> unsigned short * basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::erase(unsigned short *, unsigned short *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> unsigned short * __char_traits_base<unsigned short, unsigned short>::move(unsigned short *, unsigned short const *, unsigned int); }
// bfme link decl-only end
// _String_base<unsigned short>'s destructor is inlined into every caller here; retail's
// copy is the 63-byte EH body folded at 0x0000B3C0, so this unit emits none of its own.
namespace _STL { template <> __declspec(dllimport) __declspec(nothrow) __forceinline _String_base<unsigned short, allocator<unsigned short> >::~_String_base() { _M_deallocate_block(); } }
namespace AtoiIAT { extern "C" __declspec(dllimport) int __cdecl atoi(const char *); }
struct BfmePeerQMState { unsigned char unknown[0x294]; QMStatus status; };
#include "../../../../Include/GameNetwork/GameSpy/PeerThreadClass.h"
// The SDK is C and, with GSI_UNICODE off, its string-taking entry points are the
// ANSI ones (rowed as _peerGetPlayerInfoNoWaitA in peer/peerMainBlockingOperations.c).
extern "C" PEERBool peerGetPlayerInfoNoWaitA(PEER peer, const char *nick, unsigned int *IP, int *profileID);
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
	peerGetPlayerInfoNoWaitA(peer, nick, &IP, &resp.message.profileID);
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





