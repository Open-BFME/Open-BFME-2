// ?rva002A8306@PlayerList@@QAEX_N@Z
// partial score=0.7 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// ?rva002A8306@PlayerList@@QAEX_N@Z retail 0x002A8306..0x002A851D 535 B.
// Observer cycling: callers AptPalantir::OnBttnObserveNextPlayer 0x002D3100
// (true) and ObservePriorPlayer 0x002D3108 (false) on ThePlayerList.
// WorldBuilder twin 0x00D24BE0 (unnamed; strings GUI:PlayerObservingAll and
// GUI:PlayerObservingSpecificHuman). When the list owner's local player is an
// observer (0x002A7DD0) and the game mode passes GameLogic::rva0042219 it
// steps the player index by +1 or -1 with wraparound from the observed player
// (0x002A7E14) skipping players with +0x5C set and inactive players other than
// the first inactive observer slot; then it stores the chosen player in
// TheControlBar+0x210 and posts the observing message through TheInGameUI
// slot 0x4C before re-registering the shroud / taint callbacks and the
// 0x002A7E42 refresh. Offsets and callees are target evidence.
#include "unicode_string.h"
#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

class PlayerTemplate
{
public:
	UnicodeString getDisplayName() const;
};

class Player
{
public:
	bool isPlayerActive() const;
	char pad00[0x34];
	PlayerTemplate *m_playerTemplate;
	UnicodeString m_playerDisplayName;
	char pad3C[0x54 - 0x3c];
	int m_playerIndex;
	char pad58[4];
	int m_5C;
};

class BfmeMemberRV;
class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};

class Rva002A7DD0
{
public:
	bool rva002A7DD0();
};

class Rva002A7E42
{
public:
	void rva002A7E42(Player *player);
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);
	void rva002A8306(bool forward);
	char pad00[0x14];
	int m_playerCount;
};
extern PlayerList *ThePlayerList;

extern GameLogic *TheGameLogic;

class ControlBar
{
public:
	char pad000[0x210];
	Player *m_observedPlayer;
};
extern ControlBar *TheControlBar;

class GameTextInterface
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
#undef V
	virtual const UnicodeString &fetchRef(const char *label, bool *exists = 0);	// +0x44
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18)
#undef V
	virtual void message(UnicodeString message, ...);	// +0x4C
};
extern InGameUI *TheInGameUI;

class PartitionManager;
extern PartitionManager *TheShroudManager;
class BfmeTaintManager;
extern BfmeTaintManager *TheTaintManager;

class PointGroupClass
{
public:
	enum PointModeEnum
	{
		TRIS = 0
	};
};
class Rva00739730 { public: void rva00739730(int playerIndex, int callback); };
class Rva006C0800 { public: void rva006C0800(PointGroupClass::PointModeEnum callback); };
void rva002D7AE0(int a, int b, int c);
void rva002D7B18(int a, int b, int c);

void PlayerList::rva002A8306(bool forward)
{
	if (!reinterpret_cast<Rva002A7DD0 *>(this)->rva002A7DD0())
		return;
	Player *player = reinterpret_cast<Player *>(reinterpret_cast<BfmeThingRV *>(ThePlayerList)->bfmePickRV());
	if (!player)
		return;
	if (!TheGameLogic->rva0042219())
		return;

	int index = player->m_playerIndex;
	int step = forward ? 1 : -1;
	int observer = !player->isPlayerActive() ? player->m_playerIndex : -1;
	for (int i = 0; i < ThePlayerList->m_playerCount; ++i) {
		Player *p = ThePlayerList->getNthPlayer(i);
		if (observer == -1 && p && !p->isPlayerActive() && p->m_5C == 0)
			observer = i;
	}

	int start = index;
	for (;;) {
		index += step;
		if (index >= ThePlayerList->m_playerCount)
			index = 0;
		else if (index < 0)
			index = ThePlayerList->m_playerCount;
		if (index == start)
			break;
		Player *p = ThePlayerList->getNthPlayer(index);
		if (p && p->m_5C == 0) {
			if (p->isPlayerActive() || index == observer)
				break;
		}
	}

	player = ThePlayerList->getNthPlayer(index);
	TheControlBar->m_observedPlayer = player;

	UnicodeString message;
	UnicodeString unused;
	if (!player->isPlayerActive()) {
		message.format(&TheGameText->fetchRef("GUI:PlayerObservingAll"));
	} else {
		message.format(&TheGameText->fetchRef("GUI:PlayerObservingSpecificHuman"),
			player->m_playerDisplayName.str(), player->m_playerTemplate->getDisplayName().str());
	}
	TheInGameUI->message(message);

	if (TheShroudManager)
		reinterpret_cast<Rva00739730 *>(TheShroudManager)->rva00739730(player->m_playerIndex, (int)&rva002D7AE0);
	if (TheTaintManager)
		reinterpret_cast<Rva006C0800 *>(TheTaintManager)->rva006C0800((PointGroupClass::PointModeEnum)(int)&rva002D7B18);
	reinterpret_cast<Rva002A7E42 *>(this)->rva002A7E42(player);
}
