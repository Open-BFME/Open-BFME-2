// cl: /DNDEBUG /MD /EHs-
//
// BFME2's in-game player status screen Apt callback
// "AptPlayerStatus::InitGadgets", 0x004E40C7, bound by that name as a
// member pointer by the screen's registration; that binding is its only
// reference. The class is named for the string's prefix.
//
// Built /G7 (the bool goes out as mov al without the P6 xor) and without
// EH (the static's guard carries no frame), as retail.

// Retail calls _mbscpy through the import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// The players' colors at +0x27C (a vector).
struct AptPlayerStatusColors
{
	bool empty() const { return m_begin == m_end; }
	unsigned int size() const { return m_end - m_begin; }
	int operator[](unsigned int index) const { return m_begin[index]; }

	int *m_begin;
	int *m_end;
};

#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

void GadgetCheckBoxSetChecked(GameWindow *checkBox, bool checked);

#include "../../../../../Include/GameNetwork/GameInfo.h"


// The game being played (LANAPIRemoveGame.cpp's g_Rva00E02EEC).
struct LANGameInfo;
extern class GameInfo *TheGameInfo;

// The objectives (Rva0039B95FCount.cpp's TheMissionObjectiveTracker; its +0x10 list is
// Rva0051C0E7Ctor.cpp's Rva004266A1, whose rowed 0x004268F6 and 0x004269F7
// answer two flags of an objective).
struct Rva0039B95FHolder;
extern Rva0039B95FHolder *TheMissionObjectiveTracker;

class Rva004266A1
{
public:
	unsigned char rva004268F6(int index);
	unsigned char rva004269F7(int index);
};

struct AptPlayerStatusObjectives
{
	unsigned char m_pad00[0x10];
	Rva004266A1 *m_list; // +0x10
};

// Unrowed 0x004E43F2 (84 bytes; cdecl) maps a shown row to its objective,
// pinned by address.
int __cdecl GetNthVisibleObjectiveIndex(int row);

class AptPlayerStatus
{
public:
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	// Bound as "AptPlayerStatus::OnInitialized" and
	// "AptObjectivesMenu::OnInitialized": one body or two folded, so it
	// keeps its address.
	void rva004E4A34(const char *unused);
	void PlayerColor(int slot, char *result, bool set);
	void Objective(int row, char *result, bool skip);

	// Unrowed 0x004E476C (refreshes the player rows; it checks +0x288
	// again itself), pinned by address.
	void rva004E476C();

private:
	unsigned char m_pad000[0x27C];
	AptPlayerStatusColors m_colors; // +0x27C
	unsigned char m_pad284[0x288 - 0x284];
	int m_state; // +0x288
	GameWindow *m_mute[8]; // +0x28C
	signed char m_slot[8]; // +0x2AC
};

// Retail 0x004E40C7, 178 bytes: "AptPlayerStatus::InitGadgets" keeps each
// "PlayerStatus::Mute<n>" check box, shown checked by the slot's mute flag
// for a human player and hidden otherwise.
void AptPlayerStatus::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	static int prefixLength = strlen("PlayerStatus::Mute");
	if (strncmp(name, "PlayerStatus::Mute", prefixLength) != 0)
		return;
	name += prefixLength;
	int index = atoi(name);
	if (index < 0 || index >= 8)
		return;
	m_mute[index] = window;
	window->winHide(true);
	signed char slot = m_slot[index];
	if (slot < 0)
		return;
	const GameSlot *gameSlot = ((GameInfo *)(*(LANGameInfo **)&TheGameInfo))->getConstSlot(slot);
	if (gameSlot && !gameSlot->isAI())
	{
		window->winHide(false);
		GadgetCheckBoxSetChecked(window, gameSlot->m_isMuted);
	}
}

// Retail 0x004E4A34, 17 bytes: bound as "AptPlayerStatus::OnInitialized"
// and "AptObjectivesMenu::OnInitialized".
void AptPlayerStatus::rva004E4A34(const char *unused)
{
	if (m_state == 1)
		rva004E476C();
}

// Retail 0x004E45FA, 89 bytes: "ScoreScreen:PlayerColor:%d" for each slot,
// an Apt query answering the slot's color once the rows are up ("0"
// otherwise).
void AptPlayerStatus::PlayerColor(int slot, char *result, bool set)
{
	_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>("0"));
	if (!set && m_state == 1)
	{
		if (!m_colors.empty() && (unsigned int)slot < m_colors.size())
			sprintf(result, "%d", m_colors[slot]);
	}
}

// Retail 0x004E4446, 131 bytes: "Objective%d" for each of the twelve rows,
// an Apt query answering the row's objective's two flags as two digits
// ("00" otherwise).
void AptPlayerStatus::Objective(int row, char *result, bool skip)
{
	_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>("00"));
	if (m_state == 0 && row >= 0 && row < 12 && !skip && TheMissionObjectiveTracker)
	{
		int index = GetNthVisibleObjectiveIndex(row);
		Rva004266A1 *list = ((AptPlayerStatusObjectives *)TheMissionObjectiveTracker)->m_list;
		if (index >= 0 && list)
		{
			result[0] = '0' + (list->rva004268F6(index) != 0);
			result[1] = '0' + (list->rva004269F7(index) != 0);
			result[2] = 0;
		}
	}
}
