// cl: /DNDEBUG /MD /EHsc
// platformsdk
//
// ?findPlayerWithNameKey@PlayerList@@QAEPAVPlayer@@W4NameKeyType@@@Z,
// retail 0x002A7A41, 46 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/RTS/PlayerList.cpp,
// PlayerList::findPlayerWithNameKey): linear scan of the player array for a
// matching name key. The retail count sits at +0x14 over an inline player
// pointer array at +0x18, and the name key reads at +0x50. Resolves the
// 0x2A7A41 pin (kept alongside this row until the pin is retired).

typedef int Int;

#include <windows.h>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#include "../../../Include/Common/Player.h"

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);

private:
	unsigned char m_pad[0x14];
	Int m_playerCount; // +0x14
	Player *m_players[1]; // +0x18
};

// ?findPlayerWithNameKey@PlayerList@@QAEPAVPlayer@@W4NameKeyType@@@Z
Player *PlayerList::findPlayerWithNameKey(NameKeyType key)
{
	for (Int i = 0; i < m_playerCount; i++)
	{
		if (m_players[i]->getPlayerNameKey() == key)
		{
			return m_players[i];
		}
	}
	return NULL;
}
