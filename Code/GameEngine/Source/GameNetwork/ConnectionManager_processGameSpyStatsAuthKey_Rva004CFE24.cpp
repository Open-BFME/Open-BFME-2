// cl: -Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc
//
// ?processGameSpyStatsAuthKeyCommand@BFMEConnectionManager@@QAEXPAX@Z
// retail 0x004CFE24, 149 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/ConnectionManager_processGameSpyStatsAuthKey.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /Os it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here.

#include "ascii_string.h"

typedef unsigned int UnsignedInt;

class GameSpyGameSlot;

// Call-only views of the existing getter/setter owners. These declarations
// preserve the retail calls without assigning a second name to each body.
class Rva004CFB6DAsciiField
{
public:
	AsciiString get() const;
	void rva004CFB8B(AsciiString value);
};

class Rva004CFBC2AsciiField
{
public:
	void rva004CFBC2(AsciiString value);
};

class Rva002D9BC1AsciiField
{
public:
	AsciiString get() const;
};

// Retail folds the +0x1C getter with CDDrive::getPath (0x002D9BA6).
class CDDrive
{
public:
	virtual AsciiString getPath();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom
{
public:
	GameSpyGameSlot *getGameSpySlot( int index );
};

extern GameSpyStagingRoom *TheGameSpyGame;

class BFMENetGameSpyStatsAuthKeyCommandMsg
{
public:
	UnsignedInt getPlayerID() const { return m_playerID; }

private:
	char m_unmodelled_00[ 0x0C ];
	UnsignedInt m_playerID;
};

class BFMEConnectionManager
{
public:
	void processGameSpyStatsAuthKeyCommand( void *command );
};

void BFMEConnectionManager::processGameSpyStatsAuthKeyCommand( void *command )
{
	BFMENetGameSpyStatsAuthKeyCommandMsg *message =
		(BFMENetGameSpyStatsAuthKeyCommandMsg *)command;

	if( message->getPlayerID() < 8 )
	{
		GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot( message->getPlayerID() );
		if( slot && ((Rva004CFB6DAsciiField *)slot)->get().getLength() == 0 )
		{
			((Rva004CFB6DAsciiField *)slot)->rva004CFB8B(
				((CDDrive *)message)->CDDrive::getPath());
			((Rva004CFBC2AsciiField *)slot)->rva004CFBC2(
				((Rva002D9BC1AsciiField *)message)->get());
		}
	}
}
