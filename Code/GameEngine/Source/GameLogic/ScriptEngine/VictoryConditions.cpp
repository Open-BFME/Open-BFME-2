// cl: /O1 /EHsc /MD /arch:SSE /Ireference/shims/bfme2_ascii
// VictoryConditions.cpp -- VictoryConditions members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function (vtable pairing); retail supplies the bytes. The body is Zero
// Hour's (GameLogic/ScriptEngine/VictoryConditions.cpp) with BFME2's observer
// branch, which also requires a positive count at +0x88, and a range check on
// the local slot.
//
// Layout (target evidence): m_players[20] at +0x18, m_localSlotNum at +0x68,
// m_singleAllianceRemaining at +0x85, m_isObserver at +0x86, an int at +0x88.
// hasBeenDefeated is vtable slot 15 (+0x3C).

#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../Common/PartitionRangeQueryCallView.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class PlayerTemplate;
class Team;
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
#include <string.h>

// The 28-byte by-value kind filter retail copies through the rowed copy
// constructor 0x0004543D; a one-bit filter is built in place (memset, then
// the bit's byte).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
	__forceinline explicit BfmeFixedStorage0004543D(Int bit)
	{
		memset(w, 0, sizeof(w));
		((unsigned char *)w)[bit / 8] |= 1 << (bit % 8);
	}
	unsigned int w[7];
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
class BfmeTab1026;
#include "../../../Include/Common/Rva002AA22AByteField.h"

class Player {
public:
 Bool isLocalPlayer() const;
 bool isPlayerObserver() const;	// 0x002AA223
 Bool rva002AB295(BfmeFixedStorage0004543D mask, Bool flag) const;
 Bool rva002AB2D9(BfmeTab1026 *tab, Bool flag) const;
 Bool rva002AB341(BfmeFixedStorage0004543D mask, BfmeFixedStorage0004543D exclude) const;
 Bool rva002AB390(BfmeTab1026 *tab) const;
 Bool hasAnyObjects(Bool flag) const;
 Relationship getRelationship(const Player *that) const;
 Bool isSkirmishAIPlayer();
 Relationship getRelationship(const Team *that) const;
 Team *getDefaultTeam() const { return defaultTeam; }
 char prefix[0x34]; const PlayerTemplate *playerTemplate;
 const unsigned short *m_displayName;	// +0x38, the display UnicodeString's buffer
 char pad3C[0x50 - 0x3C]; Int m_playerNameKey;	// +0x50
 Int m_playerIndex;			// +0x54
 char pad58[0x2EC - 0x58]; Team *defaultTeam; // +0x2EC
 char pad2F0[0x3AC - 0x2F0]; Int m_id;	// +0x3AC
 char pad3B0[0x4AC - 0x3B0]; UnsignedInt m_defeatFrame;	// +0x4AC
 const unsigned short *getDisplayNameStr() const { return m_displayName ? m_displayName + 4 : L""; }
};
class Rva0023D229 {public:void rva0023D24C(Int slot);void Set(Int slot);};
class GameLogic;
extern GameLogic *TheGameLogic;
// Fields testDefeat reads: TheGameLogic +0x110 (game mode, 9 refuses any
// defeat) and +0x114 (3 skips the selection lock); TheWritableGlobalData
// +0xEBC/+0xEC0 (the two template tables the structure conditions test).
struct VictoryGameLogicView { char m_pad[0x110]; Int m_mode; Int m_network; };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct VictoryGlobalDataView { char m_pad[0xEBC]; unsigned int m_buildingTable; unsigned int m_unitTable; };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

// ?isSelectionLocked@BfmeSelectionState@@QBE_NXZ, rowed 0x0004253A (20 bytes,
// InGameUI_isSelectionLocked.cpp): a visible noinline copy of the same body,
// so cl knows the call leaves TheGameLogic alone and keeps it in ESI across it.
class BfmeSelectionState
{
public:
	__declspec(noinline) bool isSelectionLocked() const { return m_first != 0 && m_second != 0; }
private:
	unsigned char m_pad[0xB4];
	unsigned char m_first;
	unsigned char m_second;
};
#include "../../../Include/Common/PlayerList.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class PlayerTemplateStore {public:const PlayerTemplate *findPlayerTemplate(NameKeyType)const;};
extern PlayerTemplateStore *ThePlayerTemplateStore;


enum { MAX_PLAYER_COUNT = 20 };

class VictoryConditions
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void update(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual Bool hasAchievedVictory(Player *player);	// +0x38
	virtual Bool hasBeenDefeated(Player *player);		// +0x3C
	virtual Bool hasSinglePlayerBeenDefeated(Player *player);	// +0x40
 virtual void slot17();virtual void slot18();
	virtual Bool isLocalAlliedDefeat();			// +0x4C
 virtual void slot20();virtual void slot21();virtual void slot22();
 virtual void showEndGame(const AsciiString &apt, Bool flag, const AsciiString &gui, const AsciiString &extra);virtual void slot24();virtual void slot25();
 virtual Bool rva00420017(Player *player);
 virtual void slot27(); virtual void slot28();
	virtual Bool slot29();					// +0x74 (rowed byte getter +0x90)
	virtual void slot30();
	virtual void updateEndGame();				// +0x7C

	Bool testDefeat(Player *player);			// 0x004207D4


private:
	unsigned char m_pad04[0x0C - 4];
	Int m_victoryCondition;				// +0x0C (testDefeat's switch)
	unsigned char m_pad10[0x18 - 0x10];
	Player *m_players[MAX_PLAYER_COUNT];		// +0x18
	Int m_localSlotNum;				// +0x68
	UnsignedInt m_endFrame;				// +0x6C
	Bool m_isDefeated[MAX_PLAYER_COUNT];		// +0x70
	unsigned char m_pad84[0x85 - 0x84];
	Bool m_singleAllianceRemaining;			// +0x85
	Bool m_isObserver;				// +0x86
	Int m_field88;					// +0x88
 Int m_cachedPlayerCount; // +0x8C
};

// Zero Hour's file-static areAllies, retail 0x0041FE35 (46 bytes): kept out
// of line, cl 7.1 passes its two players in EDI and ESI.
#pragma auto_inline(off)
static Bool areAllies(const Player *player, const Player *p2)
{
	if (player != p2 &&
		player->getRelationship(p2->getDefaultTeam()) == ALLIES &&
		p2->getRelationship(player->getDefaultTeam()) == ALLIES)
		return true;
	return false;
}
#pragma auto_inline(on)

// A player that may win: present and not flagged by 0x002AA223.
static __forceinline Bool isEligiblePlayer(Player *player)
{
	return player && !player->isPlayerObserver();
}

// VictoryConditions::hasAchievedVictory, retail 0x0041FEEB (131 bytes),
// vtable slot 14: Zero Hour's body, which BFME2 also refuses for the player
// flagged by 0x002AA223, gates on a positive +0x88 count and reports the
// winning slot to TheGameLogic (0x0023D24C). Retail saves EBX/EDI only after
// the early return: the opening test is an inlined helper and the rest its
// else scope (a plain early return saves them at entry).
Bool VictoryConditions::hasAchievedVictory(Player *player)
{
	if (!isEligiblePlayer(player))
		return false;
	else
	{
		if (m_singleAllianceRemaining && m_field88 > 0)
		{
			for (Int i=0; i<MAX_PLAYER_COUNT; ++i)
			{
				if (m_players[i] && !hasSinglePlayerBeenDefeated(m_players[i]) && (player == m_players[i] || areAllies(m_players[i], player)))
				{
					((Rva0023D229 *)TheGameLogic)->rva0023D24C(i);
					return true;
				}
			}
		}

		return false;
	}
}

// VictoryConditions::hasBeenDefeated, retail 0x0041FF6E (63 bytes), vtable slot 15.
Bool VictoryConditions::hasBeenDefeated(Player *player)
{
	if (!isEligiblePlayer(player))
		return false;

	if (m_singleAllianceRemaining && m_field88 > 0 && !hasAchievedVictory(player))
		return true;

	return false;
}


struct VictoryUpdateGameLogicView { char m_pad[0x40]; UnsignedInt m_frame; char pad44[0x98 - 0x44]; Bool m_isScoringEnabled; char pad99[0x110 - 0x99]; Int m_mode; Int m_network; };
struct Rva00420388GlobalData { char pad[0x110C]; float m_110C; };
extern int BfmeLogicFramesPerSecond;
#include "../../../Include/Common/RecorderClass.h"
extern RecorderClass *TheRecorder;
#include "../../../Include/Common/Rva0023C6A4.h"
#include "../../../Include/Common/Rva0023C666.h"
#include "../../../Include/GameNetwork/Rva00210C66CmpBoolField.h"
class PlayerTemplate { public: char pad[0x1BC]; Bool m_1bc; };
#include "../../../Include/GameNetwork/GameInfo.h"
extern GameInfo *TheGameInfo;
#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;
struct Coord3D;
enum EvaEventID { EVA_EVENT_0 = 0 };
#include "../../../Include/GameClient/Eva.h"
extern Eva *TheEva;
class BfmeAptWindowManager; extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern PartitionManager *TheShroudManager;
class Rva002E2903Player { public: char pad[0x3C4]; Bool m_3c4; };
#include "../../../Include/Common/Rva002AB5C7Player.h"
#include "../../../Include/GameLogic/Rva002BA8F1Logic.h"
inline __declspec(noinline) bool GameLogic::isInMultiplayerGame() { int m = ((VictoryUpdateGameLogicView *)this)->m_mode; return m == 1 || m == 5; }
void VictoryConditions::update()
{
	Int scan;
	UnsignedInt frame = ((VictoryUpdateGameLogicView *)TheGameLogic)->m_frame;
	updateEndGame();
	UnsignedInt delay = (UnsignedInt)(TheWritableGlobalData
		? ((Rva00420388GlobalData *)TheWritableGlobalData)->m_110C * BfmeLogicFramesPerSecond
		: 25.0f);
	if (!TheRecorder->isMultiplayer())
		return;
	if (m_localSlotNum == -1 && !m_isObserver)
		return;
	if (frame < delay)
		return;

	// Check for a single winning alliance
	if (!m_singleAllianceRemaining)
	{
		Bool multipleAlliances = false;
		Player *alive = NULL;
		Player *player;
		for (scan = 0; scan < MAX_PLAYER_COUNT; ++scan)
		{
			player = m_players[scan];
			if (player && !hasSinglePlayerBeenDefeated(player))
			{
				if (alive)
				{
					// check to verify they are on the same team
					if (!areAllies(alive, player))
					{
						multipleAlliances = true;
						break;
					}
				}
				else
					alive = player; // save this pointer to check against
			}
		}
		if (!multipleAlliances)
		{
			m_singleAllianceRemaining = true; // don't check again
			m_endFrame = frame;
			if (!TheGameInfo->isSandbox())
				((VictoryUpdateGameLogicView *)TheGameLogic)->m_isScoringEnabled = false;
		}
	}

	// check for player eliminations
	for (Int i = 0; i < MAX_PLAYER_COUNT; ++i)
	{
		Player *p = m_players[i];
		if (!p || m_isDefeated[i] || !hasSinglePlayerBeenDefeated(p))
			continue;
		m_isDefeated[i] = true;
		((Rva0023D229 *)TheGameLogic)->Set(i);
		p->m_defeatFrame = frame;
		if (frame > 1)
		{
			TheShroudManager->revealMapForPlayerPermanently(p->m_playerIndex);
			if ((((Rva0023C6A4 *)TheGameLogic)->rva00200084() || ((VictoryUpdateGameLogicView *)TheGameLogic)->m_network == 0)
				&& p->isLocalPlayer())
				TheInGameUI->rva0029E656(AsciiString("GUI:YouHaveBeenDefeated"));
			else if (!((Rva0023C666 *)TheGameLogic)->rva0023C666() && ((VictoryUpdateGameLogicView *)TheGameLogic)->m_network != 0)
				TheInGameUI->message(AsciiString("GUI:PlayerHasBeenDefeated"), p->getDisplayNameStr());

			if ((TheGameLogic->isInMultiplayerGame() || ((VictoryUpdateGameLogicView *)TheGameLogic)->m_mode == 2)
				&& ThePlayerList && TheEva && p->getDefaultTeam())
			{
				Player *local = ThePlayerList->m_local;
				if (local->getRelationship(p->getDefaultTeam()) == ALLIES)
				{
					if (local != p)
						TheEva->reportEvaEvent((EvaEventID)6, NULL, NULL);
					else if (g_bfmeAptWindowManager)
					{
						Player *localPlayer = ThePlayerList->m_local;
						if (localPlayer)
						{
							AsciiString gui("Gui_DefeatScreen");
							AsciiString apt("APT:EndDefeat");
							showEndGame(apt, localPlayer->playerTemplate ? localPlayer->playerTemplate->m_1bc : false,
								gui, AsciiString::TheEmptyString);
						}
					}
				}
				else
					TheEva->reportEvaEvent((EvaEventID)7, NULL, NULL);
			}

			if (((Rva00210C66CmpBoolField *)TheGameLogic)->get() && !p->isSkirmishAIPlayer())
			{
				Bool anyAlive = false;
				Bool anyOther = false;
				for (scan = 0; scan < MAX_PLAYER_COUNT; ++scan)
				{
					if (scan == i || !m_players[scan] || m_players[scan]->isSkirmishAIPlayer())
						continue;
					Int id = m_players[scan]->m_id;
					Rva002E2903Player *record = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(id, 0);
					if (m_players[scan]->getRelationship(p) == ENEMIES && !record->m_3c4)
						anyOther = true;
					if (!m_isDefeated[scan])
						anyAlive = true;
				}
				if (anyOther && !anyAlive)
				{
					for (scan = 0; scan < MAX_PLAYER_COUNT; ++scan)
					{
						if (m_players[scan] && m_players[scan]->isSkirmishAIPlayer() && !m_isDefeated[scan])
							((Rva002AB5C7Player *)m_players[scan])->rva002AB44A();
					}
				}
			}
		}

		for (scan = 0; scan < 8; ++scan)
		{
			AsciiString name;
			Int key = p->m_playerNameKey;
			if (key == TheNameKeyGenerator->nameToKey(name))
			{
				GameSlot *slot = TheGameInfo ? TheGameInfo->getSlot(scan) : NULL;
				if (slot && slot->isAI())
				{
					name = slot->m_field34;
					slot->m_lastFrameInGame = frame;
				}
			}
		}
		// destroy any remaining units (infantry if its a short game, for example)
		((Rva002AB5C7Player *)p)->rva002AB44A();
	}
}

// VictoryConditions::testDefeat, retail 0x004207D4 (312 bytes), named by its
// own assert string in WB 0x01115160 (same flow, BFME2's offsets): a player
// flagged by 0x002AA22A is defeated; a selection lock outside game type 3, or
// game mode 9, defeats nobody; otherwise the +0x0C condition picks the test:
// 0 no object of kind 177 (0x002AB295), 1 no objects at all, 2 neither a
// building of the +0xEBC table nor an object of kind 14 (0x002AB341 against
// KINDOFMASK_NONE), 3 neither a +0xEBC building nor a +0xEC0 unit. WB keeps
// the value 3 test (0x002AB390) before value 2's in the source, which gives
// retail's shared negate tail in value 2's block.
Bool VictoryConditions::testDefeat(Player *player)
{
	if (((const Rva002AA22AByteField *)player)->get())
		return true;
	if (((VictoryGameLogicView *)TheGameLogic)->m_network != 3 && TheLivingWorldLogic
		&& ((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())
		return false;
	if (((VictoryGameLogicView *)TheGameLogic)->m_mode == 9)
		return false;

	switch (m_victoryCondition)
	{
	case 0:
	{
		BfmeFixedStorage0004543D mask(177);
		if (!player->rva002AB295(mask, false))
			return true;
		break;
	}
	case 1:
		if (!player->hasAnyObjects(false))
			return true;
		break;
	case 3:
		if (player->rva002AB2D9((BfmeTab1026 *)&((VictoryGlobalDataView *)TheWritableGlobalData)->m_buildingTable, false))
			return false;
		return player->rva002AB390((BfmeTab1026 *)&((VictoryGlobalDataView *)TheWritableGlobalData)->m_unitTable) ? false : true;
	case 2:
	{
		if (player->rva002AB2D9((BfmeTab1026 *)&((VictoryGlobalDataView *)TheWritableGlobalData)->m_buildingTable, false))
			return false;
		BfmeFixedStorage0004543D mask(14);
		return player->rva002AB341(mask, *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE) ? false : true;
	}
	}
	return false;
}

// VictoryConditions::hasSinglePlayerBeenDefeated, retail 0x0042090C (65 bytes),
// vtable slot 16 (+0x40, after hasAchievedVictory and hasBeenDefeated as in
// Zero Hour's VictoryConditionsInterface). WB 0x011154F0 has the same flow:
// refuse a missing or 0x002AA223-flagged player, answer true when the slot 29
// byte is set, else ask testDefeat (0x004207D4, named by its own WB assert
// string) and count each defeat in +0x88.
Bool VictoryConditions::hasSinglePlayerBeenDefeated(Player *player)
{
	if (!isEligiblePlayer(player))
		return false;
	if (slot29())
		return true;
	Bool defeated = testDefeat(player);
	if (defeated)
		++m_field88;
	return defeated;
}

// VictoryConditions::isLocalAlliedDefeat, retail 0x004200CB.
Bool VictoryConditions::isLocalAlliedDefeat()
{
	if (m_isObserver)
	{
		if (m_field88 > 0)
			return m_singleAllianceRemaining;
		return false;
	}
	if (m_localSlotNum < 0 || m_localSlotNum >= sizeof(m_players) / sizeof(m_players[0]))
		return false;
	return hasBeenDefeated(m_players[m_localSlotNum]);
}

// Native420017..42008F RET4; WB11156D0 VictoryConditions.cpp cache-one flow.
// Same eligibility test as GeneralsMD cachePlayerPtrs; target extracts it into
// a bool helper and uses the member counter+8C. Original helper name unknown.
Bool VictoryConditions::rva00420017(Player *player)
{
 const PlayerTemplate *civilian = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionCivilian"));
 if (player && player != ThePlayerList->getNeutralPlayer() && player->playerTemplate && player->playerTemplate != civilian && !player->isPlayerObserver()) {
  m_players[m_cachedPlayerCount] = player;
  if (m_players[m_cachedPlayerCount]->isLocalPlayer()) m_localSlotNum=m_cachedPlayerCount;
  ++m_cachedPlayerCount;
  return true;
 }
 return false;
}
