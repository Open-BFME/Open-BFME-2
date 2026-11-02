// cl: /DNDEBUG /MD
//
// BFME2's map file transfer screen Apt query bound as
// "FileTransfer:PlayerColor:%d" for each slot index by the screen's
// registration (0x0058343A); that binding is its only reference. The class
// is named for the string's prefix (the screen whose destructor is the
// rowed ??1Rva00582FC1).

// Retail calls _mbscpy through the import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#include <stdio.h>

#include "../../../../../Include/GameNetwork/GameInfo.h"


#include "../../../../../Include/GameNetwork/MultiplayerColorDefinition.h"

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int which);
};

extern MultiplayerSettings *TheMultiplayerSettings;

class FileTransfer
{
public:
	void PlayerColor(int slot, char *result, bool skip);

private:
	unsigned char m_pad00[0x58];
	GameInfo *m_game; // +0x58
};

// Retail 0x00583034, 94 bytes: "FileTransfer:PlayerColor:%d", an Apt query
// answering the slot's apparent color ("0" when out of range).
void FileTransfer::PlayerColor(int slot, char *result, bool skip)
{
	if (skip)
		return;
	_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>("0"));
	if (slot >= 0 && slot < 8)
	{
		const GameSlot *gameSlot = m_game->getConstSlot(slot);
		sprintf(result, "%d", TheMultiplayerSettings->getColor(gameSlot->getApparentColor())->m_color);
	}
}
