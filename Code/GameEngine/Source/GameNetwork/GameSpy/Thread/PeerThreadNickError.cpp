// cl: /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BFME1 revision6583b3c1 supplies nickname retry purpose/control flow.
// Native38BBF0/384 identifies login-name string54 and the GameSpy retry API.
// The class declaration supplies the method ABI; the field view is partial.
// /GX retains the native unwind-state store around local string cleanup.
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
// codegen otherwise instantiates the min<unsigned> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
namespace _STL {
static inline const unsigned int &min(const unsigned int &a, const unsigned int &b)
{
    return b < a ? b : a;
}
}
#include <ctype.h>
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include "PreRTS.h"
#include "PeerThreadRetail.h"
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::erase(unsigned int, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * _STL::_STLP_alloc_proxy<char *,char,_STL::allocator<char> >::allocate(unsigned int); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
namespace _STL { template <> string &string::append(const char *); }
extern "C" void peerRetryWithNickA(PEER, const char *);
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
struct BfmePeerLoginName { unsigned char unknown[0x54]; std::string name; };
#include "../../../../Include/GameNetwork/GameSpy/PeerThreadClass.h"
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
