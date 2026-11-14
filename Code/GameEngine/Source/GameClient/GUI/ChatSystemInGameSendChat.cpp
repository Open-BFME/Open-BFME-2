// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// stlport
//
// In-game chat send, retail 0x0038190F..0x00381AC7 (440 B, cdecl, two
// arguments).  The WorldBuilder twin 0x00F8D7D0 is ChatSystem::InGame::
// SendMessageA in GameNetwork/ChatSystem.cpp (asserts at lines 146..179 name
// TheNetwork, localPlayer, slot and player); the A suffix is windows.h's
// SendMessage macro.  The original scope (namespace or nested class) is not
// established, so the body keeps an address-derived name.  The only caller,
// ChatWindowsInGame vslot 0x005AFA0E, forwards its (text, selected IDs)
// arguments and returns the result.
//
// Behaviour (target bytes and the WB twin): no network or game mode 3 (+0x110
// of TheGameLogic) or no local player (+0x10 of ThePlayerList) fails.  A local
// player that is not active (bfmeAskRV false) speaks as an observer.  The
// selected slot list is copied; when empty it gathers every human slot of the
// eight.  Each listed slot whose player resolves by name key adds its bit to
// the mask, except that an observer only reaches inactive players.  The text
// is formatted with APT:ObserverChat, APT:GlobalChat (nothing selected) or
// APT:PrivateChat and sent through TheNetwork's vslot 0x64.
//
// Selected IDs use the chat windows' scalar vector view (ChatWindowsInGame.cpp
// SelectionIDs; copy 0x002CFAB9, push_back 0x004DFCB0 by pin).  The
// push_back is left to STLport (its pin binds the folded body), and
// __copy_trivial is declared non-throwing as retail's STLport had it (the
// copy ctor 0x002CFAB9 carries no EH frame): with both, cl knows the id copy
// is not escaped across the copy and the push_back loop, so the empty test
// loads begin into edi and threads the non-empty branch straight into the
// walk's body as retail; with either missing begin goes through eax and the
// walk re-tests at its head.
#include <vector>
namespace _STL {
void *__copy_trivial(const void *__first, const void *__last, void *__result) throw();
}
#include "ascii_string.h"
#include "unicode_string.h"
#include "GameLogicObjectLookupView.h"
// The id vector's _Construct and max inline into push_back/_M_insert_overflow as in the
// retail/first-linked copies; dllimport keeps cl from emitting unreferenced copies of them.
// fill_n stays an out-of-line call there, declaration-only (rowed elsewhere).
// bfme link decl-only begin
namespace _STL { template <> int * fill_n<int *, unsigned int, int>(int *, unsigned int, int const &); }
// bfme link decl-only end
namespace _STL { template <> __declspec(dllimport) __forceinline void _Construct<int,int>(int *p,int const &v) { new (p) int(v); } }
namespace _STL { template <> __declspec(dllimport) __forceinline const unsigned int &max<unsigned int>(const unsigned int &a,const unsigned int &b) { return a < b ? b : a; } }

template <class T> class Rva002444BEAllocator : public _STL::allocator<T> {};
typedef _STL::vector<int, Rva002444BEAllocator<int> > SelectionIDs;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};

#include "../../../Include/Common/BfmeMemberRV.h"

class Player;

#include "../../../Include/Common/PlayerList.h"

#include "../../../Include/Common/NameKeyGenerator.h"

#include "../../../Include/GameNetwork/GameInfo.h"


#include "../../../Include/GameClient/GameText.h"

#include "../../../Include/GameNetwork/NetworkInterfaceClass.h"

extern NetworkInterface *TheNetwork;
extern GameLogic *TheGameLogic;
extern GameInfo *TheGameInfo;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameTextInterface *TheGameText;

bool Rva0038190FSendChat(const UnicodeString &text, const SelectionIDs &selected)
{
	if (TheNetwork == 0)
		return false;
	if (TheGameLogic->m_110 == 3)
		return false;
	BfmeMemberRV *localPlayer = (BfmeMemberRV *)ThePlayerList->m_local;
	if (localPlayer == 0)
		return false;
	bool observer = !localPlayer->bfmeAskRV();
	int playerMask = 0;
	SelectionIDs ids(selected);
	if (ids.empty())
	{
		for (int i = 0; i < 8; ++i)
		{
			GameSlot *slot = TheGameInfo->getSlot(i);
			if (slot && slot->isHuman())
				ids.push_back(i);
		}
	}
	for (SelectionIDs::iterator it = ids.begin(); it != ids.end(); ++it)
	{
		int id = *it;
		GameSlot *slot = TheGameInfo->getSlot(id);
		if (slot == 0)
			continue;
		Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(slot->m_field34));
		if (player == 0)
			continue;
		if (observer && ((BfmeMemberRV *)player)->bfmeAskRV())
			continue;
		playerMask |= 1 << id;
	}
	UnicodeString message;
	if (observer)
		message.format(TheGameText->fetchPtr("APT:ObserverChat"), text.str());
	else if (selected.empty())
		message.format(TheGameText->fetchPtr("APT:GlobalChat"), text.str());
	else
		message.format(TheGameText->fetchPtr("APT:PrivateChat"), text.str());
	TheNetwork->sendChat(message, playerMask);
	return true;
}
