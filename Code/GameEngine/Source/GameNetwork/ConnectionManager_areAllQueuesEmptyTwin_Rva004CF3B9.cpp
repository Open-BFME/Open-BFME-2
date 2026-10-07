// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
//
// readable body of ?areAllQueuesEmpty@ConnectionManager@@QAE_NXZ: game/GameEngine/Source/GameNetwork/ConnectionManager.cpp
// Open-BFME: ConnectionManager::areAllQueuesEmpty, retail 0x00662DF0. This is
// the near-miss twin of the landed GameResultsQueue::areThreadsRunning
// (0x0063FD10, GameResultsThread.cpp): same loop-and-early-return shape, but
// over 8 connection slots at ConnectionManager+0x04 (per targets/game/reverse/symbols.csv:
// "conMgr 0x00662DF0 = ZH ConnectionManager::canILeave... loops the 8
// connections at conMgr+0x04 calling isQueueEmpty@Connection"), calling a
// direct (non-virtual) Connection::isQueueEmpty(). Independent TU: does not
// touch the landed native_connection_timing.cpp ConnectionManager class.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
#define TRUE 1
#define FALSE 0

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

class Connection
{
public:
	Bool isQueueEmpty();
};

class ConnectionManager
{
public:
	Bool areAllQueuesEmpty( void );
	Bool rva004CF3E1( void );

private:
	char m_unknown00[4];
	Connection *m_connections[8];
	char m_pad[0x12130 - 0x24];
	UnsignedInt m_12130;
};

// ?areAllQueuesEmpty@ConnectionManager@@QAE_NXZ
Bool ConnectionManager::areAllQueuesEmpty( void )
{
	for ( Int i = 0; i < 8; ++i )
	{
		if ( m_connections[i] != 0 )
		{
			if ( m_connections[i]->isQueueEmpty() == FALSE )
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

// ?rva004CF3E1@ConnectionManager@@QAE_NXZ @0x004CF3E1 37B
// Returns false when the timestamp at +0x12130 is clear else whether 10s elapsed since it.
// Evidence: abuts prev 0x004CF3B9; caller 0x0025E8B0 in 0x0025E75F; IAT timeGetTime; honest address method on ConnectionManager.
Bool ConnectionManager::rva004CF3E1( void )
{
	if ( m_12130 == 0 )
	{
		return FALSE;
	}

	return 0x2710 < timeGetTime() - m_12130;
}
