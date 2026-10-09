// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common
// stlport
//
// ?rva0052A53B@Rva0052A53BOwner@@QAEXXZ, retail 0x0052A53B (165 bytes). Debug-build twin
// 0x013C68C0 (AptInGameSideCommandBar.cpp, unnamed); the owner is unproven so the class
// keeps its address token.
//
// Re-point the cached local player (+0x28) when the game is in a mode that allows
// it and the selection is not locked: take the local player if it is active, and
// when it changed look up the command set named by that player's controlled object
// (+0x2C) and mark all 32 per-button flags (+0x30..+0x4F) true. Otherwise forget both.

#include <algorithm>
#include "GameLogicObjectLookupView.h"

class AsciiString;
class Object;
class Player;

extern GameLogic *TheGameLogic;

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};
extern BfmeSelectionState *TheLivingWorldLogic;

class BfmeMemberRV
{
public:
	bool bfmeAskRV();
};

class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};

class PlayerList;
extern PlayerList *ThePlayerList;

class Player
{
public:
	Object *rva002AC629();
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
};

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
};
extern Rva0031D5F8 *TheControlBar;

class Rva0052A53BOwner
{
public:
	void rva0052A53B();
private:
	char m_pad00[0x28];
	Player *m_player;		// +0x28
	void *m_commandSet;		// +0x2C
	bool m_flags[0x20];		// +0x30
};

void Rva0052A53BOwner::rva0052A53B()
{
	if (TheGameLogic->rva0042219() && !(TheLivingWorldLogic && TheLivingWorldLogic->isSelectionLocked())) {
		BfmeMemberRV *pick = ((BfmeThingRV *)ThePlayerList)->bfmePickRV();
		Player *player = (Player *)pick;
		if (player && !pick->bfmeAskRV())
			player = 0;
		if (player != m_player) {
			m_commandSet = 0;
			m_player = player;
			if (player) {
				Object *object = player->rva002AC629();
				if (object) {
					m_commandSet = TheControlBar->rva0031D5F8(object->rva00290E67());
					_STL::fill(m_flags, m_flags + 0x20, true);
				}
			}
		}
	} else {
		m_player = 0;
		m_commandSet = 0;
	}
}
