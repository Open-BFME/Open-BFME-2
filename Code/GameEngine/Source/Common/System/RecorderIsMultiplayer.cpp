// cl: /DNDEBUG /MD /EHsc

// ?isMultiplayer@RecorderClass@@QAE_NXZ @0x37B18C (110B):
// RecorderClass::isMultiplayer. BFME1 Recorder_isMultiplayer.cpp shape with
// BFME2 layout (m_mode at +0x1C, gameInfo at +0x24, GameLogic mode at +0x110)
// and a BFME2 rewrite of the mode-gate tail: modes 0 and 6 reject, the
// 0x85124 predicate (mode 4/7) rejects, +0x114 != 3 accepts, otherwise the
// Network/Skirmish globals decide.

typedef int Int;
typedef bool Bool;

enum { MAX_SLOTS = 8 };

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD = 0,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class GameSlot
{
public:
	Bool isOccupied(void) const;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slotNum);
};

class GameLogic
{
public:
	Bool rva00085124(void);
	char m_pad[0x110];
	Int m_gameMode;
	Int m_unk114;
};

extern GameLogic *TheGameLogic;

class NetworkInterface;
extern NetworkInterface *TheNetwork;

extern GameInfo *TheSkirmishGameInfo;
// TheSkirmishGameInfo: matched references place it at VA 0xe02ef0 (zero-filled .bss).
GameInfo * TheSkirmishGameInfo;

class RecorderClass
{
public:
	Bool isMultiplayer(void);
private:
	char m_pad[0x1C];
	Int m_mode;
	char m_pad2[0x24 - 0x20];
	GameInfo m_gameInfo;
};

// ?isMultiplayer@RecorderClass@@QAE_NXZ
Bool RecorderClass::isMultiplayer(void)
{
	if (m_mode == RECORDERMODETYPE_PLAYBACK)
	{
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			GameSlot *slot = m_gameInfo.getSlot(i);
			if (slot && slot->isOccupied())
				return true;
		}
	}
	GameLogic *game = TheGameLogic;
	Int mode = game->m_gameMode;
	if (mode == 0 || mode == 6)
		return false;
	if (game->rva00085124())
		return false;
	if (game->m_unk114 != 3)
		return true;
	if (TheNetwork || TheSkirmishGameInfo)
		return true;
	return false;
}
